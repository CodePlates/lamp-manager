#include <QVBoxLayout>
#include <QHeaderView>
#include <QList>
#include "include/page_vhosts.hpp"
#include "include/conf_node.hpp"
#include "include/apache_config.hpp"
#include "include/vhost.hpp"

PageVhosts::PageVhosts(QWidget *parent)
{
	QVBoxLayout *vbox = new QVBoxLayout;
	model = new QStandardItemModel();

	A2Config a2config;
	QList<VHost> vhosts = a2config.getVhosts();

	model->setHorizontalHeaderLabels({"Domain", "Documnet Root"});
   
   for (int row = 0; row < vhosts.length(); row++) {
   	VHost vhost = vhosts[row];
      model->setItem(row, 0, new QStandardItem(vhost.name));
      model->setItem(row, 1, new QStandardItem(vhost.docRoot));
   }
 
 	table = new QTableView();
	table->setModel(model);
	table->horizontalHeader()->setStretchLastSection(true);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);
	table->resizeColumnsToContents();
	table->show();

   vbox->addWidget(table);
	setLayout(vbox);
}

PageVhosts::~PageVhosts()
{
	
}