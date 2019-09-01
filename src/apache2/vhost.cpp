#include "vhost.hpp"
#include "apache_config.hpp"
#include "utilities.hpp"
#include "server.hpp"
#include <QFileInfo>
#include <QFile>
#include <QDebug>

VHost::VHost()
{

}


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

	if (file_write(filepath, config)) {
    	conf = filepath;
   }else 
   	return false;
   
   enable();
	
	QString host = "127.0.0.1\t" + name;
	file_append("/etc/hosts", host);

   run_command("apachectl", {"-k", "graceful"}, true);
	return true;
}

bool VHost::update(QString oldname)
{
	disable();
	QFileInfo info(conf);
	QMap<QString, QVariant> confPatterns;
	confPatterns.insert("^(\\s*ServerName\\s+).*\n", "\\1" + name + "\n");
	confPatterns.insert("^(\\s*ServerAlias\\s+).*\n", "\\1 www." + name + "\n");
	confPatterns.insert("^(\\s*DocumentRoot\\s+).*\n", "\\1" + docRoot + "\n");
	file_replace(info.absoluteFilePath(), confPatterns);
	
	QString filename = QString(name).append(".conf");
	QString folder = A2Config::getAvailableSitesFolder();
	QString filepath = QString(folder).append("/").append(filename);
	
	if (file_rename(conf, filepath))
		conf = filepath; 

	QMap<QString, QVariant> hostsPatterns;
	hostsPatterns.insert("^\\s*127.0.0.1\\s+" + oldname + "\\s*\n", "127.0.0.1\t" + name + "\n");
	file_replace("/etc/hosts", hostsPatterns);

	enable();
	return true;
}

bool VHost::enable()
{
	
	QFileInfo info(conf);
	run_command("a2ensite", {info.fileName()}, true);

	apache_restart();
	return true;
}

bool VHost::disable()
{
	QFileInfo info(conf);
   run_command("a2dissite", {info.fileName()}, true);
	return true;
}

bool VHost::destroy()
{
	disable();
	// QFile(conf).remove();

	run_command("apachectl", {"-k", "graceful"}, true);

	QMap<QString, QVariant> patterns;
	patterns.insert("^\\s*127.0.0.1\\s+" + name + "\\s*\n", "");
	file_replace("/etc/hosts", patterns);
	return true; 
}
