#pragma once

#include <QStandardItemModel>
#include <QTableView>
#include <QWidget>

class PageVhosts: public QWidget {
private:
	QStandardItemModel *model;
	QTableView *table;
public:
	PageVhosts(QWidget *parent = 0);
	~PageVhosts();
	void onAddVHostClicked();
	
};