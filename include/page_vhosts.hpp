#pragma once

#include <QStandardItemModel>
#include <QTableView>
#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QModelIndex>

class PageVhosts: public QWidget {
private:
	QStandardItemModel *model;
	QTableView *table;
	int selectedRow;
	QPushButton* editVhostBtn;
	QPushButton* delVhostBtn;
public:
	PageVhosts(QWidget *parent = 0);
	~PageVhosts();
	void onAddVHostClicked();
	void onTableItemSelected(const QModelIndex &index);
	void loadVHostsModel();
	
};