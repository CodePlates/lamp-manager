#pragma once 

#include <QTextStream>

class ConfTree;

enum class NodeType { KEYVAL, TAG, SUBTREE };

static int nodecount = 0;

struct ConfNode {
	NodeType type;
	QString key;
	QStringList values;
	int id;
	ConfTree* parent = nullptr;

	ConfNode() {
		id = nodecount++;
	}

	ConfNode(QString key, QStringList values): 
		key(key), values(values) 
	{
		id = nodecount++;
	}

	void print(QString tab = "")
	{
		QTextStream out(stdout);
		
		out << tab << key << ":";

		for (QString val: values)
			out << " [" << val << "]";

		out << endl;
	
	}
};
