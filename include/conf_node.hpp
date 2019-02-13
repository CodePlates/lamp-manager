#pragma once 

#include <QStringList>
#include "include/conf_node_base.hpp"
#include "include/conf_tree.hpp"


class KeyvalNode : public ConfNode
{

public:
	KeyvalNode(QString key, QStringList values);
	~KeyvalNode();
	QList<ConfNode*> get(QString key, NodeType type);
};

class SubtreeNode : public ConfNode
{
private:
	QList<ConfTree*> m_trees;
public:
	SubtreeNode(QString key);
	~SubtreeNode();
	void addTree(ConfTree* tree);
	QList<ConfNode*> get(QString key, NodeType type);
};

class TagNode : public ConfNode
{
private:
	QList<ConfNode*> m_nodes;
public:
	TagNode(QString key, QStringList values);
	~TagNode();
	void addNode(ConfNode* node);
	QList<ConfNode*> get(QString key, NodeType type);
	QString getValue(QString key, QString defaultVal = QString());
};