#pragma once

#include <QHash>
#include "conf_node.hpp"

class ConfTree
{
private:
	QString m_filepath;
	QList<ConfNode> nodes;

public:
	QHash<int, ConfTree*> subtrees;
	ConfTree();
	ConfTree(QString filepath);
	~ConfTree();

	inline QString getFilepath() { return this->m_filepath; }
	inline void setFilepath(QString path) { this->m_filepath = path; }

	void add(ConfNode node);
	ConfTree* addTag(ConfNode tagNode);
	void addTree(ConfTree* tree);
	QList<ConfNode> getNodes(QString key, NodeType type = NodeType::KEYVAL);
	inline QString getValue(QString key)
	{
		return getNodes(key).value(0).values.value(0);
	}

	
	void printTree();

};