#pragma once

#include <QList>
#include <QStandardItemModel>
#include <QTableView>
#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QModelIndex>
#include "vhost.hpp"
#include "apache_config.hpp"

class PageVhosts: public QWidget {
private:
	int selectedRow;
	QList<VHost*> vhosts;
	QTableView* table;
	QStandardItemModel* model = nullptr;
	QPushButton* editVhostBtn;
	QPushButton* delVhostBtn;
public:
	PageVhosts(QWidget *parent = 0);
	~PageVhosts();
	void loadVHostsModel();
	void onTableItemSelected(const QItemSelection &selected, const QItemSelection &deselected);
	void onAddVHostClicked();
	void onEditVHostClicked();
	void onDelVHostClicked();
	
};