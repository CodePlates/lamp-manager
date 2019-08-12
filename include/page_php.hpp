#pragma once

#include <QWidget>
#include <QLabel> 

class PagePhp: public QWidget {
private:
	QLabel* a2VersionLabel = nullptr;
	QLabel* cliVersionLabel = nullptr;
public:
	PagePhp(QWidget *parent = 0);
	~PagePhp();	
};

class HorizontalLine: public QFrame {
public:
	HorizontalLine():QFrame() {
		this->setFrameShape(QFrame::HLine);
		this->setFrameShadow(QFrame::Sunken);
		this->setStyleSheet("margin-bottom: 0px");
	}	
};
