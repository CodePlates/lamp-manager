#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QDir>
#include "page_vhosts.hpp"
#include "vhost_dialog.hpp"
#include <QItemSelectionModel>
#include <QItemSelection>


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
	table->setShowGrid(true);
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

	QItemSelectionModel *selectionModel = table->selectionModel();
	connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &PageVhosts::onTableItemSelected);
	connect(addVHBtn, &QPushButton::clicked, this, &PageVhosts::onAddVHostClicked);
	connect(editVhostBtn, &QPushButton::clicked, this, &PageVhosts::onEditVHostClicked);
	connect(delVhostBtn, &QPushButton::clicked, this, &PageVhosts::onDelVHostClicked);
	//connect(table, &QTableView::clicked, this, &PageVhosts::onTableItemSelected);


	bodyHbox->addWidget(table);
	bodyHbox->addLayout(tactionsVbox);
   vbox->addLayout(bodyHbox);
	setLayout(vbox);
}

void PageVhosts::onTableItemSelected(const QItemSelection &selected, const QItemSelection &deselected)
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
   	VHost* vhost = vhosts.at(row);
      model->setItem(row, 0, new QStandardItem(vhost->getName()));
      model->setItem(row, 1, new QStandardItem(vhost->getDocRoot()));
   }
}

PageVhosts::~PageVhosts()
{
	for (VHost* vhost : vhosts)
		delete vhost;
}

void PageVhosts::onAddVHostClicked()
{
	VHostDialog dialog(this);
	dialog.setWindowTitle("Add VirtualHost");
	dialog.exec();

	if (dialog.result() == QDialog::Accepted) {
		VHost* vh = dialog.getVHost();

		if (vh->save()) {
			vhosts.append(vh);
			QList<QStandardItem*> cols;
			cols << new QStandardItem(vh->getName());
			cols << new QStandardItem(vh->getDocRoot());
			model->appendRow(cols);
		}
	}
}

void PageVhosts::onEditVHostClicked()
{
	VHostDialog dialog(this);
	VHost* vh = vhosts.at(selectedRow);
	dialog.setVHost(vh);
	dialog.setWindowTitle("Edit VirtualHost");
	dialog.exec();

	if (dialog.result() == QDialog::Accepted) {
		VHost* vh = dialog.getVHost();

		if (vh->update()) {
			model->item(selectedRow, 0)->setData(vh->getName(), Qt::DisplayRole);
			model->item(selectedRow, 1)->setData(vh->getDocRoot(), Qt::DisplayRole);
		}
	}
}

void PageVhosts::onDelVHostClicked()
{
	VHost* vh = vhosts.at(selectedRow);
	if (vh->destroy()) {
		vhosts.removeAt(selectedRow);
		model->removeRow(selectedRow);
		table->selectionModel()->clearSelection();
		selectedRow = -1;
	}
}