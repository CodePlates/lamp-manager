#pragma once

#include <QTextStream>
#include <QList>
#include "vhost.hpp"
#include "conf_tree.hpp"

enum class Token {
	TOK_END,
	TOK_OPEN_ANGLE,
	TOK_CLOSE_ANGLE,
	TOK_CLOSE_TAG,
	TOK_WORD,
	TOK_LINE_END
};

class A2Config
{
private:
	QStringList configs;

	QString findConf();
	Token get_tok(QTextStream& in, QString& token);
	void parseFile(QString path, ConfTree* parent = nullptr);
	ConfTree* parse(QString conf, QTextStream& in);
	QStringList getValues(QTextStream& in, bool tag = false);

public:
	ConfTree* configTree;
	A2Config();
	~A2Config();
	QList<VHost> getVhosts();

};
