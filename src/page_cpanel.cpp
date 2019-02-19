#include <QVBoxLayout>
#include <QGridLayout>
#include "include/page_cpanel.hpp"


PageCpanel::PageCpanel(QWidget *parent)
{
	QVBoxLayout *vbox = new QVBoxLayout;
	QGridLayout *grid = new QGridLayout;
	 
	toggleApache = new QPushButton();
	toggleMysql = new QPushButton();
	apacheStatusLabel = new QLabel();
	mysqlStatusLabel = new QLabel();

	loadStatusApache();
	loadStatusMysql();

	grid->addWidget(new QLabel("Apache2"), 0, 0);
	grid->addWidget(apacheStatusLabel, 0, 1);
	grid->addWidget(toggleApache, 0, 2);

	grid->addWidget(new QLabel("Mysql"), 1, 0);
	grid->addWidget(mysqlStatusLabel, 1, 1);
	grid->addWidget(toggleMysql, 1, 2);

	vbox->addLayout(grid);
	vbox->addStretch(1);
	setLayout(vbox);

	
	connect(toggleApache, &QPushButton::clicked, this, &PageCpanel::onToggleApacheClicked);
	connect(toggleMysql, &QPushButton::clicked, this, &PageCpanel::onToggleMysqlClicked);


}

PageCpanel::~PageCpanel()
{

}

void PageCpanel::loadStatusApache()
{
	apacheState = apache_status();
	if (apacheState == ServerStatus::RUNNING) {
		apacheStatusLabel->setText("Running");
		toggleApache->setText("Stop");
	} else if (apacheState == ServerStatus::STOPPED) {
		apacheStatusLabel->setText("Stopped");
		toggleApache->setText("Start");
	} else {
		apacheStatusLabel->setText("Unknown");
		toggleApache->setText("-");
	}
}

void PageCpanel::loadStatusMysql()
{
	mysqlState = mysql_status();
	if (mysqlState == ServerStatus::RUNNING) {
		mysqlStatusLabel->setText("Running");
		toggleMysql->setText("Stop");
	} else if (mysqlState == ServerStatus::STOPPED) {
		mysqlStatusLabel->setText("Stopped");
		toggleMysql->setText("Start");
	} else {
		mysqlStatusLabel->setText("Unknown");
		toggleMysql->setText("-");
	}
}

void PageCpanel::onToggleApacheClicked()
{
	if (apacheState == ServerStatus::RUNNING) {
		apache_stop();
	} else if (apacheState == ServerStatus::STOPPED) {
		apache_start();
	}

	loadStatusApache();
}

void PageCpanel::onToggleMysqlClicked()
{
	if (mysqlState == ServerStatus::RUNNING) {
		mysql_stop();
	} else if (mysqlState == ServerStatus::STOPPED) {
		mysql_start();
	}

	loadStatusMysql();
}
