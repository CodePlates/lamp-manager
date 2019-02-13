#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QDir>
#include "include/page_vhosts.hpp"
#include <QTextStream>
#include "include/vhost_dialog.hpp"
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
	connect(editVhostBtn, &QPushButton::clicked, this, &PageVhosts::onEditVHostClicked);
	connect(table, &QTableView::clicked, this, &PageVhosts::onTableItemSelected);

	bodyHbox->addWidget(table);
	bodyHbox->addLayout(tactionsVbox);
   vbox->addLayout(bodyHbox);
	setLayout(vbox);
}

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
	vhosts = a2config.getVhosts();

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
	VHostDialog dialog(this);
	dialog.exec();

	if (dialog.result() == QDialog::Accepted) {
		VHost* vh = dialog.getVHost();

		if (vh->save()) {
			QList<QStandardItem*> cols;
			cols << new QStandardItem(vh->name);
			cols << new QStandardItem(vh->docRoot);
			model->appendRow(cols);
		}
	}
}

void PageVhosts::onEditVHostClicked()
{
	VHostDialog dialog(this);
	VHost vh = vhosts.at(selectedRow);
	qDebug() << vh.name << " : " << vh.conf;
	dialog.setVHost(vh);
	dialog.exec();
}

void PageVhosts::onDelVHostClicked()
{

}