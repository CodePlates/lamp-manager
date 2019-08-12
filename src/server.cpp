#include "server.hpp"
#include "utils.hpp"
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
	const char* command = "systemctl status mysql";
	QString data = run_command(command);
	return check_status(data);
}

bool mysql_start()
{
	const char* command = "systemctl start mysql";
	run_command(command);
	return true;
}

bool mysql_stop()
{
	const char* command = "systemctl stop mysql";
	run_command(command);
	return true;
}

bool mysql_restart()
{
	const char* command = "systemctl restart mysql";
	run_command(command);
	return true;
}


ServerStatus apache_status()
{
	const char* command = "systemctl status apache2";
	QString data = run_command(command);
	return check_status(data);
}

bool apache_start()
{
	const char* command = "systemctl start apache2";
	run_command(command);
	return true;
}

bool apache_stop()
{
	const char* command = "systemctl stop apache2";
	run_command(command);
	return true;
}

bool apache_restart()
{
	const char* command = "systemctl restart apache2";
	run_command(command);
	return true;
}
