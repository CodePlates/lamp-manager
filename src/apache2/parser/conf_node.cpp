#include "include/conf_node.hpp"


KeyvalNode::KeyvalNode(QString key, QStringList values) :
	ConfNode(key, values)
{
	m_type = NodeType::KEYVAL;
}

KeyvalNode::~KeyvalNode()
{

}

QList<ConfNode*> KeyvalNode::get(QString key, NodeType type)
{
	QList<ConfNode*> nodes;
	if (isNode(key, type)) {
		nodes.append(this);
	}
	return nodes;
}




SubtreeNode::SubtreeNode(QString key) :
	ConfNode(key)
{
	m_type = NodeType::SUBTREE;
}

SubtreeNode::~SubtreeNode()
{
	for (ConfTree* tree : m_trees)
		delete tree;
}

void SubtreeNode::addTree(ConfTree* tree)
{
	m_trees.append(tree);
}

QList<ConfNode*> SubtreeNode::get(QString key, NodeType type)
{
	QList<ConfNode*> nodes;
	if (isNode(key, type)) {
		nodes.append(this);
	}else {
		for (auto tree : m_trees)
			nodes.append(tree->getNodes(key, type));
	}
	return nodes;
}




TagNode::TagNode(QString key, QStringList values) :
	ConfNode(key, values)
{
	m_type = NodeType::TAG;
}

TagNode::~TagNode()
{
	for (ConfNode* node : m_nodes)
		delete node;
}

void TagNode::addNode(ConfNode* node)
{
	m_nodes.append(node);
}

QList<ConfNode*> TagNode::get(QString key, NodeType type)
{
	QList<ConfNode*> nodes;
	if (isNode(key, type)) {
		nodes.append(this);
	}else {
		for(ConfNode* node: m_nodes) {
			nodes.append(node->get(key, type));
		}
	}
	return nodes;
}

QString TagNode::getValue(QString key, QString defaultVal)
{
	QList<ConfNode*> nodes = get(key, NodeType::KEYVAL);
	if (nodes.length() > 0)
		return nodes.at(0)->m_values.at(0);
	else
		return defaultVal;
}

