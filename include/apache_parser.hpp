#pragma once

#include "conf_tree.hpp"
#include "conf_node.hpp"
#include "apache_scanner.hpp"


class A2Parser {
private:
	ConfTree* configTree;
	Token curr_tok_type;
	A2Scanner s;
	QString conf;
public:	
	A2Parser(QString conf);
	static ConfTree* parse(QString conf);
	QStringList getValues();
	QList<ConfTree*> parsePath(QString path);
	ConfNode* parseLine();
	ConfNode* parseTag();
	ConfNode* parseTree();
	ConfNode* parseKeyval();
};