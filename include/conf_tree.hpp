
//typedef QMap<QString, QStringList> ConfDict;
//typedef QList<ConfDict*> Tag;

struct ConfNode {
	QString key;
	QStringList values;

	ConfNode() {
	}

	ConfNode(QString key): key(key) {}

	ConfNode(QString key, QStringList values): 
		key(key), values(values) {}

	void print()
	{
		QTextStream out(stdout);
		
		out << "\t" << key << ":";

		for (QString val: values)
			out << " [" << val << "]";

		out << endl;
	
	}
};

class ConfTree
{
private:
	QList<ConfNode> nodes;
	QString tag; 
	QStringList tagValues;
	QList<ConfTree*> subtrees;

public:
	ConfTree() {
		tag = "ROOT";
	}
	
	ConfTree(QString tag): tag(tag) {
	}

	~ConfTree() {
		for(auto tree : subtrees)
		{
			delete tree;
		}
	}

	void add(ConfNode node) {
		nodes.append(node);
	}

	void add(ConfTree* tree) {
		subtrees.append(tree);
	}

	void setTagValues(QStringList values) {
		tagValues = values;
	}


	void printTree() 
	{
		QTextStream out(stdout);

		out << tag;
		for (QString tval : tagValues)
			out << " : " << tval;
		out << endl;

		for (ConfNode node: nodes) {
			node.print();
		}

		for (ConfTree* tree: subtrees)
			tree->printTree();
	}

};