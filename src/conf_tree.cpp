#include "include/conf_tree.hpp"

ConfTree::ConfTree() {}

ConfTree::ConfTree(QString filepath):
	m_filepath(filepath) 
{ }

ConfTree::~ConfTree() {
	for(auto tree : subtrees)
	{
		delete tree;
	}
}

void ConfTree::add(ConfNode node) {
	node.parent = this;
	node.type = NodeType::KEYVAL;
	nodes.append(node);
}

ConfTree* ConfTree::addTag(ConfNode tagNode) {
	tagNode.parent = this;
	tagNode.type = NodeType::TAG;
	nodes.append(tagNode);

	ConfTree* tag = new ConfTree(this->m_filepath);
	subtrees.insert(tagNode.id, tag);
	return tag;
}

void ConfTree::addTree(ConfTree* tree) 
{
	ConfNode treeNode;
	treeNode.parent = this;
	treeNode.type = NodeType::SUBTREE;
	nodes.append(treeNode);

	subtrees.insert(treeNode.id, tree);
}


QList<ConfNode> ConfTree::getNodes(QString key, NodeType type)
{
	QList<ConfNode> results;

	for (ConfNode node: nodes) {
		if (QString::compare(key, node.key) == 0 && type == node.type) {
			results.append(node);
		}
		if (node.type == NodeType::SUBTREE) {
			results.append(node.parent->subtrees[node.id]->getNodes(key, type));
		}
	}

	return results;
}

void ConfTree::printTree() 
{
	QTextStream out(stdout);
	static QString tab = ""; 

	for (ConfNode node: nodes) {
		node.print(tab);
		tab += "\t";
		if (node.type == NodeType::SUBTREE || node.type == NodeType::TAG) {
			subtrees[node.id]->printTree();
		} 
		tab.chop(1);
	}

}