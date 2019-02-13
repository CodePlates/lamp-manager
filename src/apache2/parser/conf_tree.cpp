#include "include/conf_tree.hpp"
#include <QDebug>

ConfTree::ConfTree() {}

ConfTree::ConfTree(QString filepath):
	m_filepath(filepath) 
{ }

ConfTree::~ConfTree() {
	// for(auto tree : subtrees)
	// {
	// 	delete tree;
	// }
}

void ConfTree::add(ConfNode* node) {
	nodes.append(node);
}

// ConfTree* ConfTree::addTag(ConfNode tagNode) {
// 	tagNode.parent = this;
// 	tagNode.type = NodeType::TAG;
// 	nodes.append(tagNode);

// 	ConfTree* tag = new ConfTree(this->m_filepath);
// 	subtrees.insert(tagNode.id, tag);
// 	return tag;
// }

// void ConfTree::addTree(ConfTree* tree) 
// {
// 	ConfNode treeNode;
// 	treeNode.parent = this;
// 	treeNode.type = NodeType::SUBTREE;
// 	nodes.append(treeNode);

// 	subtrees.insert(treeNode.id, tree);
// }


QList<ConfNode*> ConfTree::getNodes(QString key, NodeType type)
{
	QList<ConfNode*> results;

	for (ConfNode* node: nodes) {
		results.append(node->get(key, type));
	}

	return results;
}

// QString ConfTree::getValue(QString key, QString defaultVal)
// {
// 	QList<ConfNode> nodes = getNodes(key);
// 	if (nodes.length() > 0)
// 		return nodes.at(0);
// 	else
// 		return defaultVal;
// }

void ConfTree::printTree()
{
	for (auto node : nodes)
		qDebug() << node->getKey();
}
