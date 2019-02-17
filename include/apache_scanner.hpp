#pragma once

#include <QTextStream>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QRegularExpressionMatch>

enum class Token {
	TOK_END,
	TOK_OPEN_ANGLE,
	TOK_CLOSE_ANGLE,
	TOK_CLOSE_TAG,
	TOK_WORD,
	TOK_LINE_END
};

struct A2Scanner {
	QString contents;
	QString currText = QString();
	int pos = 0;
	A2Scanner(QString filepath);
	Token get_tok();
};



