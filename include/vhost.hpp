#pragma once

#include <QDebug>
#include "include/conf_node.hpp"

class VHost
{
public:
	QString conf;
	QString name;
	QString docRoot;
public:
	VHost();
	//VHost(QString& conf, QString& name, QString& docRoot);
	~VHost();
	bool save();
	bool update();
	bool disable();
	bool destroy();
};