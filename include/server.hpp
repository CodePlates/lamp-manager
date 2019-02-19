#pragma once

#include <QString>

enum class ServerStatus {
	RUNNING, STOPPED, OTHER
};

QString run_command(const char* command);
ServerStatus check_status(QString& data);

ServerStatus mysql_status();
bool mysql_start();
bool mysql_stop();
bool mysql_restart();

ServerStatus apache_status();
bool apache_start();
bool apache_stop();
bool apache_restart();