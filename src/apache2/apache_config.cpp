#include <cstdio>
#include <QDir>
#include "include/apache_config.hpp"
#include "include/apache_parser.hpp"
#include <QDebug>

QString A2Config::apacheConf = "";
QString A2Config::apacheRoot = "";

A2Config::A2Config()
{
	processConf();	
}

A2Config::~A2Config()
{
}

void A2Config::processConf()
{
	if (apacheConf.isEmpty())
		findConf();
	configs.append(apacheConf);
	configTree = A2Parser::parse(apacheConf);
}

void A2Config::findConf()
{
	QString data, conf;
	int i;
	char buffer[256];
	const char* cmd = "apachectl -V 2>&1";

	FILE* stream = popen(cmd, "r");
	if (stream) {
		while (!feof(stream)) {
			if (fgets(buffer, 256, stream) != NULL) 
				data.append(buffer);
		}
		pclose(stream);
	}

	i = data.indexOf("HTTPD_ROOT=");
	for (i = i+12; data.at(i) != '"'; i++)
		apacheRoot.append(data.at(i));

	i = data.indexOf("SERVER_CONFIG_FILE=");
	for (i = i+20; data.at(i) != '"'; i++)
		conf.append(data.at(i));

	apacheConf = apacheRoot;
	if (apacheConf.at(apacheConf.length() - 1) != '/') apacheConf.append('/');
	apacheConf.append(conf);

}

QString A2Config::getAvailableSitesFolder()
{
	return getA2Path("sites-available");
}

QString A2Config::getA2Path(QString folder)
{
	if (apacheRoot.isEmpty()) 
		findConf();

	QString path = apacheRoot;
	if (path.at(path.length() - 1) != '/') 
		path.append('/');

	if (folder == NULL)
		return path;

	if (QDir(path.append(folder)).exists()) {
		return path;
	}
	else 
		return QString::null;
}

QList<VHost*> A2Config::getVhosts()
{
	QString folder = A2Config::getAvailableSitesFolder().append('/');
	QList<VHost*> vhosts;
	QList<ConfNode*> vhost_nodes = configTree->getNodes("VirtualHost", NodeType::TAG);

	for(auto node: vhost_nodes) {
		TagNode* tag = (TagNode*) node;

		QFileInfo info(tag->parent->getFilepath());
		VHost* vhost = new VHost();
		vhost->name = tag->getValue("ServerName", "localhost");
		vhost->docRoot = tag->getValue("DocumentRoot");
		vhost->conf = folder + info.fileName();
		vhosts.append(vhost);
	}

	return vhosts;
}

