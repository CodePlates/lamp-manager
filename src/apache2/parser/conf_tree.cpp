#include "include/conf_tree.hpp"
#include <QDebug>

ConfTree::ConfTree() {}

ConfTree::ConfTree(QString filepath):
	m_filepath(filepath) 
{ }

ConfTree::~ConfTree() {
	for(ConfNode* node : nodes)
	{
		delete node;
	}
}

void ConfTree::add(ConfNode* node) {
	nodes.append(node);
}


QList<ConfNode*> ConfTree::getNodes(QString key, NodeType type)
{
	QList<ConfNode*> results;

	for (ConfNode* node: nodes) {
		results.append(node->get(key, type));
	}

	return results;
}
