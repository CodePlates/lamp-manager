#include <QStack>
#include <QDirIterator>
#include "include/apache_parser.hpp"
#include <QDebug>

// overrall my parser is very ugly and i will eventually just use bison
namespace A2Parser {

	ConfTree* parse(QString conf)
	{
		QFile file(conf);
		QFileInfo fileinfo(conf);
		if (!file.open(QIODevice::ReadOnly)) {
			qWarning("Cannot open configuration file");
			return nullptr;
		}

		QTextStream in(&file);
		ConfTree* configTree = new ConfTree(conf);
		
		ConfNode* node;
		while((node = getNext(in, fileinfo)) != nullptr){
			configTree->add(node);
		}

		file.close();

		return configTree;
	}

	ConfNode* getNext(QTextStream& in, QFileInfo& fileinfo)
	{
		QString key, value;		
		Token tok_type;
		
		
		tok_type = get_tok(in, key);
		
		while(tok_type == Token::TOK_LINE_END)
			tok_type = get_tok(in, key);


		if (tok_type == Token::TOK_END)
			return nullptr;

		if (tok_type == Token::TOK_OPEN_ANGLE) {
			
			tok_type = get_tok(in, key);
			QStringList values = getValues(in, true);
			
			TagNode* tagNode = new TagNode(key, values);
			
			ConfNode* node;
			while ((node = getNext(in, fileinfo)) != nullptr) {
				tagNode->addNode(node);
			}
			return tagNode;
			
		}

		if (tok_type == Token::TOK_CLOSE_TAG) {
			while (tok_type != Token::TOK_END && tok_type != Token::TOK_CLOSE_ANGLE) {
				//if (tok_type == Token::TOK_WORD) values.append(value);
				tok_type = get_tok(in, value);
			}
			return nullptr;			
		}
		
		if (tok_type == Token::TOK_WORD) {
			
	   	QStringList values = getValues(in);

	   	if (QString::compare(key, "Include") == 0 || 
	   		QString::compare(key, "IncludeOptional") == 0 ) {

	   			SubtreeNode* subtree = new SubtreeNode(key);

	   			for(QString val: values) {
	   				QList<ConfTree*> treelist = parsePath(val, fileinfo);
	   				for (auto tree : treelist) {
	   					subtree->addTree(tree);
	   				}
	   			}
	   			return subtree;
	   	}
	   	
	   	KeyvalNode* keynode = new KeyvalNode(key, values);
	   	return keynode;

		}	

		return nullptr;
	}

	QList<ConfTree*> parsePath(QString path, QFileInfo& fileinfo)
	{
		QList<ConfTree*> lst;	
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

	QStringList getValues(QTextStream& in, bool tag) {
		Token tok_type;
		QString value;
		QStringList values;
		Token end = Token::TOK_LINE_END;

		if (tag)
			end = Token::TOK_CLOSE_ANGLE;

		tok_type = get_tok(in, value);

		while (tok_type != Token::TOK_END && tok_type != end) {
			if (tok_type == Token::TOK_WORD) {
				values.append(value);
			}
			tok_type = get_tok(in, value);
		}

		return values;
	}

	Token get_tok(QTextStream& in, QString& token)
	{
		token = "";
		QChar ch;
		bool word = false;
		static QChar prev = '\0';

		while (!in.atEnd()) {

			if (prev == '\0')
				ch = in.read(1).at(0);
			else {
				ch = prev;
				prev = '\0';
			}

			if (word && (ch.isSpace() || ch == '<' || ch == '>')) {
				prev = ch;
				return Token::TOK_WORD; 
			}

			else if (ch == '\n') {
				return Token::TOK_LINE_END;
			}

			else if (ch == '\'' || ch == '\"') {
				QChar nextCh;
				while (!in.atEnd()) {
					nextCh = in.read(1).at(0);
					if (nextCh == ch) break;
					token.append(nextCh);
				}
				return Token::TOK_WORD;
			}

			else if (ch == '#') {
				in.readLine();
				continue;
			}

			else if (ch.isSpace()) {
				continue;
			}

			else if (ch == '<'){
				QChar nextCh;
				nextCh = in.read(1).at(0);
				if (nextCh == '/') {
					return Token::TOK_CLOSE_TAG; 
				}else {
					prev = nextCh;
					return Token::TOK_OPEN_ANGLE;
				}
			}
			else if (ch == '>'){
				return Token::TOK_CLOSE_ANGLE; 
			}
			
			token.append(ch);
			word = true;
			
		}

		if (word) return Token::TOK_WORD;

		return Token::TOK_END;
	}

}