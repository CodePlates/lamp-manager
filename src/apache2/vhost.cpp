#include "include/vhost.hpp"
#include "include/apache_config.hpp"

VHost::VHost()
{

}

VHost::VHost(QString name, QString docRoot) :
	name(name), docRoot(docRoot)
{

}

VHost::~VHost()
{

}

bool VHost::save()
{
	// this was planned to be in its own stub file
	QString conf =	"<VirtualHost *:80>\n"
						"	ServerAdmin webmaster@localhost\n"
						"	DocumentRoot %%docRoot%%\n"
						"\n"
						"	ServerName %%domain%%\n"
						"	ServerAlias www.%%domain%%\n"
						"\n"
						"	ErrorLog ${APACHE_LOG_DIR}/error.log\n"
						"	CustomLog ${APACHE_LOG_DIR}/access.log combined\n"
						"</VirtualHost>";
				
	conf.replace("%%domain%%", name);
	conf.replace("%%docRoot%%", docRoot);

	QString folder = A2Config::getAvailableSitesFolder();
	QString filename = QString(name).append(".conf");
	QString filepath = QString(folder).append("/").append(filename);

	QFile file(filepath);
	if (file.open(QIODevice::WriteOnly)) {
    	QTextStream outstream(&file);
    	outstream << conf;
    	file.close();
   }else 
   	return false;

   char cmd[50];
   sprintf(cmd, "a2ensite %s 2>&1", filename.toStdString().c_str());

	FILE* stream = popen(cmd, "r");
	if (stream) {
		pclose(stream);
	}

	QFile hostsfile("/etc/hosts");
	if (hostsfile.open(QIODevice::Append | QIODevice::Text)) {
    	QTextStream outstream(&hostsfile);
    	outstream << "127.0.0.1	" << name;
    	hostsfile.close();
   }

   popen("apachectl -k graceful", "r");
	return true;
}

bool VHost::update()
{
	return true;
}

bool VHost::disable()
{
	return true;
}

bool VHost::destroy()
{
	return true;
}
