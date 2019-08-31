#pragma once

#include <QHash>
#include "conf_node_base.hpp"

class ConfTree
{
private:
	QString m_filepath;
	QList<ConfNode*> nodes;

public:
	
	ConfTree();
	ConfTree(QString filepath);
	~ConfTree();

	inline QString getFilepath() { return this->m_filepath; }
	inline void setFilepath(QString path) { this->m_filepath = path; }

	void add(ConfNode* node);
	QList<ConfNode*> getNodes(QString key, NodeType type = NodeType::KEYVAL);
	QString getValue(QString key, QString defaultVal = QString());
};