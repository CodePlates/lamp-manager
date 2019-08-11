#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include "include/page_php.hpp"


PagePhp::PagePhp(QWidget *parent)
{
	QVBoxLayout *vbox = new QVBoxLayout;
	QHBoxLayout *a2Ver = new QHBoxLayout;
	QHBoxLayout *cliVer = new QHBoxLayout;
	QPushButton *a2changeVer = new QPushButton("Change");
	QPushButton *clichangeVer = new QPushButton("Change");
   a2changeVer->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
   clichangeVer->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);


	vbox->addWidget(new QLabel("PHP Apache"));
	vbox->addWidget(new HorizontalLine);
	vbox->addSpacing(8);
	a2Ver->addWidget(new QLabel("Current Version: "));
	a2Ver->addWidget(new QLabel("7.0"));
	a2Ver->addStretch(1);
	vbox->addLayout(a2Ver);
	vbox->addWidget(a2changeVer);

	
	vbox->addSpacing(60);
	
	vbox->addWidget(new QLabel("PHP Cli"));
	vbox->addWidget(new HorizontalLine);
	vbox->addSpacing(8);
	cliVer->addWidget(new QLabel("Current Version: "));
	cliVer->addWidget(new QLabel("7.0"));
	cliVer->addStretch(1);
	vbox->addLayout(cliVer);
	vbox->addWidget(clichangeVer);


	// vbox->addLayout(grid);
	vbox->addStretch(1);
	setLayout(vbox);

	
	// connect(toggleApache, &QPushButton::clicked, this, &PageCpanel::onToggleApacheClicked);
	// connect(toggleMysql, &QPushButton::clicked, this, &PageCpanel::onToggleMysqlClicked);

}

PagePhp::~PagePhp()
{
	
}