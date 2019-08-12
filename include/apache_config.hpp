#pragma once

#include <QTextStream>
#include <QList>
#include "vhost.hpp"


class A2Config
{
private:
	QStringList configs;
	ConfTree* configTree;
	static QString apacheConf;
	static QString apacheRoot;

	static void findConf();
	void processConf();

public:
	A2Config();
	~A2Config();
	static QString getA2Path(QString folder = NULL);
	static QString getAvailableSitesFolder();
	QList<VHost*> getVhosts();

};
