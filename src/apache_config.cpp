#include <QFile>
#include <QDirIterator>
#include <QMap>
#include <QStack>
#include "include/apache_config.hpp"

enum Token {
	TOK_END,
	TOK_OPEN_ANGLE,
	TOK_CLOSE_ANGLE,
	TOK_CLOSE_TAG,
	TOK_WORD,
	TOK_LINE_END
};

A2Config::A2Config()
{
	QString conf = this->findConf();
	configs.append(conf);
	parseFile(conf);
}

A2Config::~A2Config()
{
}

QString A2Config::findConf()
{
	return "/etc/apache2/apache2.conf";
}

void A2Config::parseFile(QString path, QString conf)
{
	QFileInfo info(path);

	if (!conf.isNull()) {
		QFileInfo confInfo(conf);
		QDir::setCurrent(confInfo.dir().absolutePath());
	}

	QDirIterator it(info.dir().absolutePath(), QStringList() << info.fileName());

	//QTextStream out(stdout);

	//out << path << endl;

	while (it.hasNext()) {
		QString conf = it.next();

		//out << conf << endl;

		QFile file(conf);
		if (!file.open(QIODevice::ReadOnly)) {
			qWarning("Cannot open configuration file");
			return;
		}

		QTextStream in(&file);

		parse(conf, in);

		file.close();
	}
}

void A2Config::parse(QString conf, QTextStream& in)
{
	ConfTree configTree;
	ConfTree* currTree = &configTree;
	QStack<ConfTree*> stack; 
	stack.push(&configTree);

	
	QString key, tag, value;
	
	int tok_type = get_tok(in, key);
	while (tok_type != TOK_END)
	{
		
		if (tok_type == TOK_OPEN_ANGLE) {
			QStringList values;
			tok_type = get_tok(in, tag);
			ConfTree* tree = new ConfTree(tag);
			stack.push(tree);
			currTree = tree;

			tok_type = get_tok(in, value);
			while (tok_type != TOK_END && tok_type != TOK_CLOSE_ANGLE) {
				if (tok_type == TOK_WORD) {
					values.append(value);
				}
				tok_type = get_tok(in, value);
			}
			tree->setTagValues(values);	
		}

		if (tok_type == TOK_CLOSE_TAG) {
			while (tok_type != TOK_END && tok_type != TOK_CLOSE_ANGLE) {
				//if (tok_type == TOK_WORD) values.append(value);
				tok_type = get_tok(in, value);
			}

			ConfTree* old = currTree; 
			stack.pop();
			currTree = stack.last();
			currTree->add(old);
			
		}
		
		if (tok_type == TOK_WORD) {
			QStringList values;

			tok_type = get_tok(in, value);
			while (tok_type != TOK_END && tok_type != TOK_LINE_END) {
				if (tok_type == TOK_WORD) values.append(value);
				tok_type = get_tok(in, value);
			}
	   		
	   	ConfNode node(key, values);
	   	currTree->add(node);

	   	if (QString::compare(key, "Include") == 0 || 
	   		QString::compare(key, "IncludeOptional") == 0 ) {

	   			for(QString val: values)
	   				parseFile(val, conf);
	   	}

		}

		tok_type = get_tok(in, key);
	}

	configTree.printTree();

}

int A2Config::get_tok(QTextStream& in, QString& token)
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
			return TOK_WORD; 
		}

		if (ch == '\n') {
			return TOK_LINE_END;
		}

		if (ch == '\'' || ch == '\"') {
			QChar nextCh;
			while (!in.atEnd()) {
				nextCh = in.read(1).at(0);
				if (nextCh == ch) break;
				token.append(nextCh);
			}
			return TOK_WORD;
		}

		if (ch == '#') {
			in.readLine();
			continue;
		}

		if (ch.isSpace()) {
			continue;
		}

		if (ch == '<'){
			QChar nextCh;
			nextCh = in.read(1).at(0);
			if (nextCh == '/') {
				return TOK_CLOSE_TAG; 
			}else {
				prev = nextCh;
				return TOK_OPEN_ANGLE;
			}
		}
		if (ch == '>'){
			return TOK_CLOSE_ANGLE; 
		}
		
		token.append(ch);
		word = true;
		
	}

	if (word) return TOK_WORD;

	return TOK_END;
}

QList<VHost> A2Config::getVhosts()
{
	QList<VHost> lst;
	return lst;
}


