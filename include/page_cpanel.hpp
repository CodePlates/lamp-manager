#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "server.hpp"

class PageCpanel: public QWidget {
private:
	ServerStatus apacheState;
	ServerStatus mysqlState;
	QPushButton* toggleApache;
	QPushButton* toggleMysql;
	QLabel* apacheStatusLabel;
	QLabel* mysqlStatusLabel;
public:
	PageCpanel(QWidget *parent = 0);
	~PageCpanel();	
	void onToggleApacheClicked();
	void onToggleMysqlClicked();
	void loadStatusApache();
	void loadStatusMysql();

};