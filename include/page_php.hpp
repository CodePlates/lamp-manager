#pragma once

#include <QWidget>

class PagePhp: public QWidget {
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
