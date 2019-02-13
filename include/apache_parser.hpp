#pragma once

#include <QFile>
#include <QTextStream>
#include "conf_tree.hpp"
#include "conf_node.hpp"

enum class Token {
	TOK_END,
	TOK_OPEN_ANGLE,
	TOK_CLOSE_ANGLE,
	TOK_CLOSE_TAG,
	TOK_WORD,
	TOK_LINE_END
};

namespace A2Parser {

	Token get_tok(QTextStream& in, QString& token);
	QStringList getValues(QTextStream& in, bool tag = false);

	ConfTree* parse(QString conf);
	QList<ConfTree*> parsePath(QString path, QFileInfo& fileinfo);
	ConfNode* getNext(QTextStream& in, QFileInfo& fileinfo);
}