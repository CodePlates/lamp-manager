#pragma once

#include <QWidget>
#include <QDialog>
#include "vhost.hpp"

class VHostDialog : public QDialog {
private:
	VHost* vhost = nullptr;
	QLineEdit* nameEdit;
	QLineEdit* docRootEdit;
public:
	VHostDialog(QWidget *parent = 0);
	~VHostDialog();
	void onBrowseBtnClicked();
	void onCancelBtnClicked();
	void onOkayBtnClicked();
	void setVHost(VHost* vh);
	VHost* getVHost();
};