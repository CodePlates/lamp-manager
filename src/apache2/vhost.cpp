#include "include/vhost.hpp"
#include "include/apache_config.hpp"
#include "utils.hpp"
#include <QFileInfo>

VHost::VHost()
{

}

// VHost::VHost(QString& conf, QString& name, QString& docRoot) :
// 	name(name), docRoot(docRoot), conf(conf)
// {

// }

VHost::~VHost()
{

}

bool VHost::save()
{
	// this was planned to be in its own stub file
	QString config =	"<VirtualHost *:80>\n"
						"	ServerAdmin webmaster@localhost\n"
						"	DocumentRoot %%docRoot%%\n"
						"\n"
						"	ServerName %%domain%%\n"
						"	ServerAlias www.%%domain%%\n"
						"\n"
						"	ErrorLog ${APACHE_LOG_DIR}/error.log\n"
						"	CustomLog ${APACHE_LOG_DIR}/access.log combined\n"
						"</VirtualHost>\n";
				
	config.replace("%%domain%%", name);
	config.replace("%%docRoot%%", docRoot);

	QString filename = QString(name).append(".conf");
	QString folder = A2Config::getAvailableSitesFolder();
	QString filepath = QString(folder).append("/").append(filename);


	QFile file(filepath);
	if (file.open(QIODevice::WriteOnly)) {
    	QTextStream outstream(&file);
    	outstream << config;
    	file.close();
    	conf = filepath;
   }else 
   	return false;

   
   enable();
	
	QFile hostsfile("/etc/hosts");
	if (hostsfile.open(QIODevice::ReadWrite | QIODevice::Append)) {
    	QTextStream outstream(&hostsfile);
    	outstream.seek(outstream.pos() - 1);
    	if (QString::compare(outstream.read(1), "\n") != 0){
    		outstream << "\n";
    	}
    	outstream << "127.0.0.1	" << name << "\n";
    	hostsfile.close();
   }

   popen("apachectl -k graceful", "r");
	return true;
}

bool VHost::update()
{
	disable();
	QFileInfo info(conf);
	PatternsList patterns;
	patterns.append({"^(\\s*ServerName\\s+).*\n", "\\1" + name + "\n"});
	patterns.append({"^(\\s*DocumentRoot\\s+).*\n", "\\1" + docRoot + "\n"});
	file_replace(info.absoluteFilePath(), patterns);

	enable();
	return true;
}

bool VHost::enable()
{
	char cmd[50];
	QFileInfo info(conf);
   sprintf(cmd, "a2ensite %s 2>&1", info.fileName().toStdString().c_str());

   FILE* stream = popen(cmd, "r");
	if (stream) {
		pclose(stream);
	}
	return true;
}

bool VHost::disable()
{
	char cmd[50];
	QFileInfo info(conf);
   sprintf(cmd, "a2dissite %s 2>&1", info.fileName().toStdString().c_str());

   popen(cmd, "r");
	return true;
}

bool VHost::destroy()
{
	disable();
	QFile(conf).remove();

	popen("apachectl -k graceful", "r");

	PatternsList patterns;
	patterns.append({"^\\s*127.0.0.1\\s+" + name + "\\s*\n", ""});
	file_replace("/etc/hosts", patterns);
	return true; 
}
