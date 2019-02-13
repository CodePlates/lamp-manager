#pragma once 

#include <QString>
#include <QList>

class ConfTree;
enum class NodeType { KEYVAL, TAG, SUBTREE };

class ConfNode {
public:
	ConfTree* parent = nullptr;
	NodeType m_type;
	QString m_key;
	QStringList m_values;
	inline bool isNode(QString key, NodeType type) {
		return (m_type == type && QString::compare(m_key, key) == 0);
	}
public:
	ConfNode(QString key, QStringList values = QStringList());
	inline void setParent(ConfTree* parent) { this->parent = parent; }
	virtual ~ConfNode();
	virtual QList<ConfNode*> get(QString key, NodeType type);
	inline QString getKey() { return m_key; }
};