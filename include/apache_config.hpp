#pragma once

#include <QTextStream>
#include <QList>
#include "vhost.hpp"
#include "conf_tree.hpp"

class A2Config
{
private:
	QStringList configs;
	QString findConf();
	int get_tok(QTextStream& in, QString& token);
	void parseFile(QString path, QString conf = QString());
	void parse(QString conf, QTextStream& in);

public:
	A2Config();
	~A2Config();
	QList<VHost> getVhosts();

};
