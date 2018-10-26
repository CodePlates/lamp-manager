#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include "include/page_cpanel.hpp"

PageCpanel::PageCpanel(QWidget *parent)
{
	QVBoxLayout *vbox = new QVBoxLayout;
	QGridLayout *grid = new QGridLayout;

	grid->addWidget(new QLabel("Apache2"), 0, 0);
	grid->addWidget(new QLabel("Running"), 0, 1);

	grid->addWidget(new QLabel("Mysql"), 1, 0);
	grid->addWidget(new QLabel("Stopped"), 1, 1);

	vbox->addLayout(grid);
	vbox->addStretch(1);
	setLayout(vbox);


}

PageCpanel::~PageCpanel()
{

}