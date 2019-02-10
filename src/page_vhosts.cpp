#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QList>
#include <QDir>
#include "include/page_vhosts.hpp"
#include "include/conf_node.hpp"
#include "include/apache_config.hpp"
#include "include/vhost.hpp"
#include <QTextStream>
#include "include/add_vhost_dialog.hpp"
#include <cstdio>

PageVhosts::PageVhosts(QWidget *parent)
{
	selectedRow = -1;
	QVBoxLayout* vbox = new QVBoxLayout;
	QHBoxLayout* bodyHbox = new QHBoxLayout;

	loadVHostsModel();
 
 	table = new QTableView();
	table->setModel(model);
	table->horizontalHeader()->setStretchLastSection(true);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);
	table->resizeColumnsToContents();
	table->show();

	QVBoxLayout* tactionsVbox = new QVBoxLayout;
	QPushButton* addVHBtn = new QPushButton("Add VirtualHost");
	editVhostBtn = new QPushButton("Edit VirtualHost");
	delVhostBtn = new QPushButton("Delete VirtualHost");

	editVhostBtn->setEnabled(false);
	delVhostBtn->setEnabled(false);

	tactionsVbox->addWidget(addVHBtn);
	tactionsVbox->addSpacing(20);
	tactionsVbox->addWidget(editVhostBtn);
	tactionsVbox->addWidget(delVhostBtn);
	tactionsVbox->addStretch(1);

	connect(addVHBtn, &QPushButton::clicked, this, &PageVhosts::onAddVHostClicked);
	//connect(table, &QTableView::selectionChanged, this, &PageVhosts::onTableItemUnselected);
	connect(table, &QTableView::clicked, this, &PageVhosts::onTableItemSelected);

	bodyHbox->addWidget(table);
	bodyHbox->addLayout(tactionsVbox);
   vbox->addLayout(bodyHbox);
	setLayout(vbox);
}

// void PageVhosts::onTableItemUnselected(const QItemSelection &selected, const QItemSelection &deselected)
// {
// 	qDebug() << "Unselected";
// }

void PageVhosts::onTableItemSelected(const QModelIndex &index)
{
	
	QItemSelectionModel *selectionModel = table->selectionModel();
	if (selectionModel->hasSelection()){
		QModelIndexList indexes = selectionModel->selectedRows();
		selectedRow = indexes.at(0).row();
		editVhostBtn->setEnabled(true);
		delVhostBtn->setEnabled(true);
	}else{
		editVhostBtn->setEnabled(false);
		delVhostBtn->setEnabled(false);
	}
	
}

void PageVhosts::loadVHostsModel()
{
	model = new QStandardItemModel();
	A2Config a2config;
	QList<VHost> vhosts = a2config.getVhosts();

	model->setHorizontalHeaderLabels({"Domain", "Documnet Root"});
   
   for (int row = 0; row < vhosts.length(); row++) {
   	VHost vhost = vhosts[row];
      model->setItem(row, 0, new QStandardItem(vhost.name));
      model->setItem(row, 1, new QStandardItem(vhost.docRoot));
   }
}

PageVhosts::~PageVhosts()
{
	
}

void PageVhosts::onAddVHostClicked()
{
	AddVHostDialog* dialog = new AddVHostDialog(this);
	dialog->exec();

	if (dialog->result() == QDialog::Accepted) {
		VHost vh = dialog->getVHost();

		QString conf =	"<VirtualHost *:80>\n"
							"	ServerAdmin webmaster@localhost\n"
							"	DocumentRoot %%docRoot%%\n"
							"\n"
							"	ServerName %%domain%%\n"
							"	ServerAlias www.%%domain%%\n"
							"\n"
							"	ErrorLog ${APACHE_LOG_DIR}/error.log\n"
							"	CustomLog ${APACHE_LOG_DIR}/access.log combined\n"
							"</VirtualHost>";
					
		conf.replace("%%domain%%", vh.name);
		conf.replace("%%docRoot%%", vh.docRoot);

		QString folder = A2Config::getAvailableSitesFolder();
		QString filename = QString(vh.name).append(".conf");
		QString filepath = QString(folder).append("/").append(filename);

		QFile file(filepath);
		if (file.open(QIODevice::WriteOnly)) {
	    	QTextStream outstream(&file);
	    	outstream << conf;
	    	file.close();
	   }

	   char cmd[50];
	   sprintf(cmd, "a2ensite %s 2>&1", filename.toStdString().c_str());

		FILE* stream = popen(cmd, "r");
		if (stream) {
			pclose(stream);
		}

		QFile hostsfile("/etc/hosts");
		if (hostsfile.open(QIODevice::Append | QIODevice::Text)) {
	    	QTextStream outstream(&hostsfile);
	    	outstream << "127.0.0.1	" << vh.name;
	    	hostsfile.close();
	   }

	   popen("apachectl -k graceful", "r");

		QList<QStandardItem*> cols;
		cols << new QStandardItem(vh.name);
		cols << new QStandardItem(vh.docRoot);
		model->appendRow(cols);
	}
}