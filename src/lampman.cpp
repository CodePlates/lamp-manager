#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QTabWidget>
#include "lampman.hpp"
#include "page_cpanel.hpp"
#include "page_vhosts.hpp"
#include "page_php.hpp"


Lampman::Lampman(QWidget *parent)
	: QWidget(parent) 
{
	QVBoxLayout *vbox = new QVBoxLayout;
	QTabWidget  *tabView = new QTabWidget();

	PageCpanel *pageCpanel = new PageCpanel();
	PageVhosts *pageVhosts = new PageVhosts();
	PagePhp    *pagePhp    = new PagePhp();

	tabView->addTab(pageCpanel, "Control Panel");
	tabView->addTab(pageVhosts, "Virtual Hosts");
	tabView->addTab(pagePhp, "PHP");

	vbox->addWidget(tabView);
	setLayout(vbox);

}

Lampman::~Lampman()
{
	
}

