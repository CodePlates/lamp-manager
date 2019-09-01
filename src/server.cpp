#include "server.hpp"
#include "utilities.hpp"
#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QDebug>

QRegularExpression re("^\\s*Active:\\s+(\\w+)", QRegularExpression::MultilineOption);


ServerStatus check_status(QString& data)
{
	QRegularExpressionMatch match = re.match(data);
	if (match.hasMatch()) {
    	QString matched = match.captured(1);
	   if (QString::compare(matched, "active") == 0) 
	   	return ServerStatus::RUNNING;
	   else if (QString::compare(matched, "inactive") == 0) 
	   	return ServerStatus::STOPPED;
	}else {
		qDebug() << "No Match";
	}
	return ServerStatus::OTHER;
}

ServerStatus mysql_status()
{	
	QString data = run_command("systemctl", {"status", "mysql"});
	return check_status(data);
}

bool mysql_start()
{
	run_command("systemctl", {"start", "mysql"});
	return true;
}

bool mysql_stop()
{
	run_command("systemctl", {"stop", "mysql"});
	return true;
}

bool mysql_restart()
{
	run_command("systemctl", {"restart", "mysql"});
	return true;
}


ServerStatus apache_status()
{
	QString data = run_command("systemctl", {"status", "apache2"});
	return check_status(data);
}

bool apache_start()
{
	run_command("systemctl", {"start", "apache2"});
	return true;
}

bool apache_stop()
{
	run_command("systemctl", {"stop", "apache2"});
	return true;
}

bool apache_restart()
{
	run_command("systemctl", {"restart", "apache2"});
	return true;
}
