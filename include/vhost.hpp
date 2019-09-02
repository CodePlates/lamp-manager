#pragma once

#include <QDebug>
#include "conf_node.hpp"

class VHost
{
private:
	struct Details {
		QString conf;
		QString name;
		QString docRoot;
	};
	Details details;
	Details oldDetails; 
public:
	VHost();
	VHost(QString name, QString docRoot, QString conf = QString());
	~VHost();
	void setDetails(QString name, QString docRoot, QString conf = QString());
	void setConf(QString& conf);
	QString getConf();
	QString getName();
	QString getDocRoot();
	QString getOldName();
	QString getOldDocRoot();
	bool save();
	bool update();
	bool enable();
	bool disable();
	bool destroy();
};