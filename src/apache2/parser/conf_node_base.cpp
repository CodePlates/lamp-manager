#include "include/conf_node_base.hpp"

ConfNode::ConfNode(QString key, QStringList values) : 
	m_key(key), m_values(values) 
{}

ConfNode::~ConfNode() 
{}

QList<ConfNode*> ConfNode::get(QString key, NodeType type) 
{
	QList<ConfNode*> empty;
	return empty;
}

