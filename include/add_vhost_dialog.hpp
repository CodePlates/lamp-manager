#pragma once

#include <QWidget>
#include <QDialog>
#include "include/vhost.hpp"

class AddVHostDialog : public QDialog {
private:
	QLineEdit* nameEdit;
	QLineEdit* docRootEdit;
public:
	AddVHostDialog(QWidget *parent = 0);
	~AddVHostDialog();
	void onBrowseBtnClicked();
	void onCancelBtnClicked();
	void onOkayBtnClicked();
	VHost getVHost();
};