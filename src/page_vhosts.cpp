#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QList>
#include "include/page_vhosts.hpp"
#include "include/conf_node.hpp"
#include "include/apache_config.hpp"
#include "include/vhost.hpp"
#include <QTextStream>
#include "include/add_vhost_dialog.hpp"

PageVhosts::PageVhosts(QWidget *parent)
{
	QVBoxLayout* vbox = new QVBoxLayout;
	QHBoxLayout* headerHbox = new QHBoxLayout;
	QPushButton* addVHBtn = new QPushButton("Add VirtualHost");
	headerHbox->addWidget(addVHBtn, 0, Qt::AlignRight);

	connect(addVHBtn, &QPushButton::clicked, this, &PageVhosts::onAddVHostClicked);

	vbox->addLayout(headerHbox);

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

void PageVhosts::onAddVHostClicked()
{
	AddVHostDialog* dialog = new AddVHostDialog(this);
	dialog->exec();

	if (dialog->result() == QDialog::Accepted) {
		QTextStream out(stdout);
		VHost vh = dialog->getVHost();
		out << vh.name << " : " << vh.docRoot << endl;
	}
}