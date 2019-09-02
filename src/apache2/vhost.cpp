#include "vhost.hpp"
#include "apache_config.hpp"
#include "utilities.hpp"
#include "server.hpp"
#include <QFileInfo>
#include <QFile>
#include <QDebug>

VHost::VHost() {}

VHost::VHost(QString name, QString docRoot, QString conf)
{
	oldDetails.conf 		= conf;
	oldDetails.name 		= name;
	oldDetails.docRoot 	= docRoot;
	setDetails(name, docRoot, conf);
}

void VHost::setDetails(QString name, QString docRoot, QString conf)
{
	if (!conf.isEmpty()) details.conf = conf;

	details.name 		= name;
	details.docRoot 	= docRoot;
}

void VHost::setConf(QString& conf) { 
	oldDetails.conf = conf; 
	details.conf = conf; 
}

QString VHost::getConf() { return details.conf; }

QString VHost::getOldName() { return oldDetails.name; }

QString VHost::getOldDocRoot() { return oldDetails.docRoot; }

QString VHost::getName() { return details.name; }

QString VHost::getDocRoot() { return details.docRoot; }

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
				
	config.replace("%%domain%%", getName());
	config.replace("%%docRoot%%", getDocRoot());

	QString filename = getName() + ".conf";
	QString folder = A2Config::getAvailableSitesFolder();
	QString filepath = folder + "/" + filename;

	if (file_write(filepath, config)) {
    	setConf(filepath);
   }else 
   	return false;
   
   enable();
	
	QString host = "127.0.0.1\t" + getName();
	file_append("/etc/hosts", host);

   run_command("apachectl", {"-k", "graceful"}, true);
	return true;
}

bool VHost::update()
{
	disable();
	QFileInfo info(getConf());
	QMap<QString, QVariant> confPatterns;
	confPatterns.insert("^(\\s*ServerName\\s+).*\n", "\\1" + getName() + "\n");
	confPatterns.insert("^(\\s*ServerAlias\\s+).*\n", "\\1 www." + getName() + "\n");
	confPatterns.insert("^(\\s*DocumentRoot\\s+).*\n", "\\1" + getDocRoot() + "\n");
	file_replace(info.absoluteFilePath(), confPatterns);
	
	QString filename = getName() + ".conf";
	QString folder = A2Config::getAvailableSitesFolder();
	QString filepath = QString(folder).append("/").append(filename);
	
	if (file_rename(getConf(), filepath))
		setConf(filepath); 

	QMap<QString, QVariant> hostsPatterns;
	hostsPatterns.insert("^\\s*127.0.0.1\\s+" + getOldName() + "\\s*\n", "127.0.0.1\t" + getName() + "\n");
	file_replace("/etc/hosts", hostsPatterns);

	enable();
	return true;
}

bool VHost::enable()
{
	QFileInfo info(getConf());
	run_command("a2ensite", {info.fileName()}, true);

	apache_restart();
	return true;
}

bool VHost::disable()
{
	QFileInfo info(getConf());
   run_command("a2dissite", {info.fileName()}, true);
	return true;
}

bool VHost::destroy()
{
	disable();
	// QFile(conf).remove();

	run_command("apachectl", {"-k", "graceful"}, true);

	QMap<QString, QVariant> patterns;
	patterns.insert("^\\s*127.0.0.1\\s+" + getName() + "\\s*\n", "");
	file_replace("/etc/hosts", patterns);
	return true; 
}
