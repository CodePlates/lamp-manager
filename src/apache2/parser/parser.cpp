#include <QStack>
#include <QDirIterator>
#include "include/apache_parser.hpp"
#include <QDebug>

// overrall my parser is very ugly and i will eventually just use bison
A2Parser::A2Parser(QString conf):
	s(conf), conf(conf)
{
	
}

ConfTree* A2Parser::parse(QString conf)
{
	ConfTree* configTree = new ConfTree(conf);
	A2Parser p(conf);

	ConfNode* node = nullptr;
	while((node = p.parseLine()) != nullptr) {
		configTree->add(node);	
	}
	return configTree;
}

QList<ConfTree*> A2Parser::parsePath(QString path)
{
	QList<ConfTree*> lst;	
	QFileInfo fileinfo(conf);
	QString currFolder = fileinfo.dir().absolutePath();
	if (currFolder.at(currFolder.length() - 1) != '/') currFolder.append('/');

	if (!path.startsWith("/"))
		path.prepend(currFolder);

	QFileInfo info(path);
	QDirIterator it(info.dir().absolutePath(), QStringList() << info.fileName());

	while (it.hasNext()) {
		QString conf = it.next();
		ConfTree* tree = parse(conf);
		lst.append(tree);
	}
	return lst;
}

ConfNode* A2Parser::parseLine()
{	

	curr_tok_type = s.get_tok();

	while (curr_tok_type == Token::TOK_LINE_END) {
		curr_tok_type = s.get_tok();
		continue;
	}

	if (curr_tok_type == Token::TOK_END)
		return nullptr;
		
	ConfNode* result = parseTag();
	return result;
	
}
	


ConfNode* A2Parser::parseTag()
{

	if (curr_tok_type == Token::TOK_OPEN_ANGLE) {
		curr_tok_type = s.get_tok();
		QString tag = s.currText;
		QStringList values = getValues();
		TagNode* tagNode = new TagNode(tag, values);

		if (curr_tok_type == Token::TOK_CLOSE_ANGLE) {
			s.get_tok();
			ConfNode* node = parseLine();
			while (curr_tok_type != Token::TOK_END) {
				if (curr_tok_type == Token::TOK_CLOSE_TAG) {
					curr_tok_type = s.get_tok(); // tagname
					curr_tok_type = s.get_tok(); // close angle			
					return tagNode;
				}else {
					tagNode->addNode(node);
					node = parseLine();
				}
			}
		} 
		qDebug() << conf;
		qWarning("Unexpected end of file."); exit(-1);
		return nullptr;
		
	}else if (curr_tok_type == Token::TOK_CLOSE_TAG) {
		return nullptr;
	}else {
		return parseTree();
	}
}

ConfNode* A2Parser::parseTree()
{
	if (curr_tok_type == Token::TOK_WORD) {
		
   	if (QString::compare(s.currText, "Include") == 0 || 
   		QString::compare(s.currText, "IncludeOptional") == 0 ) {

   			SubtreeNode* subtree = new SubtreeNode(s.currText);
   			
   			QStringList values = getValues();
   			for(QString val: values) {
   				QList<ConfTree*> treelist = parsePath(val);
   				for (auto tree : treelist) {
   					subtree->addTree(tree);
   				}
   			}
   			return subtree;
   	}
   } 
   	
   return parseKeyval();
}


ConfNode* A2Parser::parseKeyval()
{
	if (curr_tok_type == Token::TOK_WORD) {
   	QString key = s.currText;
   	QStringList values = getValues();
   	KeyvalNode* keynode = new KeyvalNode(key, values);
   	return keynode;

	}else {
		return nullptr;
	}
}
	
QStringList A2Parser::getValues() {
	QString value;
	QStringList values;
	while ((curr_tok_type = s.get_tok()) == Token::TOK_WORD) {
		values.append(s.currText);
	}
	return values;
}

	

