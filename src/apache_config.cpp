#include <QFile>
#include <QDirIterator>
#include <QStack>
#include <cstdio>
#include "include/apache_config.hpp"


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
	QString data, conf;
	int i;
	char buffer[256];
	const char* cmd = "apachectl -V 2>&1";

	FILE* stream = popen(cmd, "r");
	if (stream) {
		while (!feof(stream)) {
			if (fgets(buffer, 256, stream) != NULL) 
				data.append(buffer);
		}
		pclose(stream);
	}

	i = data.indexOf("HTTPD_ROOT=");
	for (i = i+12; data.at(i) != '"'; i++)
		conf.append(data.at(i));

	if (conf.at(conf.length() - 1) != '/') conf.append('/');

	i = data.indexOf("SERVER_CONFIG_FILE=");
	for (i = i+20; data.at(i) != '"'; i++)
		conf.append(data.at(i));

	return conf;
}

void A2Config::parseFile(QString path, ConfTree* parent)
{
	QFileInfo info(path);

	if (parent != nullptr) {
		QFileInfo confInfo(parent->getFilepath());
		QDir::setCurrent(confInfo.dir().absolutePath());
	}

	QDirIterator it(info.dir().absolutePath(), QStringList() << info.fileName());

	while (it.hasNext()) {
		QString conf = it.next();

		QFile file(conf);
		if (!file.open(QIODevice::ReadOnly)) {
			qWarning("Cannot open configuration file");
			return;
		}

		QTextStream in(&file);

		ConfTree* tree = parse(conf, in);
		if (parent == nullptr) 
			this->configTree = tree;
		else
			parent->addTree(tree);

		file.close();
	}
}

QStringList A2Config::getValues(QTextStream& in, bool tag) {
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

ConfTree* A2Config::parse(QString conf, QTextStream& in)
{
	ConfTree* configTree = new ConfTree(conf);
	ConfTree* currTree = configTree;
	QStack<ConfTree*> stack; 
	stack.push(configTree);
	QTextStream out(stdout);

	
	QString key, value;
	
	Token tok_type;
	
	do {
		tok_type = get_tok(in, key);

		if (tok_type == Token::TOK_OPEN_ANGLE) {
			
			tok_type = get_tok(in, key);
			QStringList values = getValues(in, true);
			
			ConfNode tagNode(key, values);
			ConfTree* tag = currTree->addTag(tagNode);
			stack.push(tag);
			currTree = tag;

			continue;
		}

		if (tok_type == Token::TOK_CLOSE_TAG) {
			while (tok_type != Token::TOK_END && tok_type != Token::TOK_CLOSE_ANGLE) {
				//if (tok_type == Token::TOK_WORD) values.append(value);
				tok_type = get_tok(in, value);
			}
 
			stack.pop();
			currTree = stack.last();
			
			continue;
		}
		
		if (tok_type == Token::TOK_WORD) {
			
	   	QStringList values = getValues(in);
	   	ConfNode node(key, values);
	   	currTree->add(node);

	   	if (QString::compare(key, "Include") == 0 || 
	   		QString::compare(key, "IncludeOptional") == 0 ) {

	   			for(QString val: values)
	   				parseFile(val, currTree);
	   	}

		}

	} while (tok_type != Token::TOK_END);


	return configTree;

}

Token A2Config::get_tok(QTextStream& in, QString& token)
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

QList<VHost> A2Config::getVhosts()
{
	QList<VHost> vhosts;
	QList<ConfNode> vhost_nodes = this->configTree->getNodes("VirtualHost", NodeType::TAG);

	for(auto node: vhost_nodes){
		VHost vhost;
		ConfTree* vhost_node = node.parent->subtrees[node.id];
		vhost.name = vhost_node->getValue("ServerName", "localhost");
		vhost.docRoot = vhost_node->getValue("DocumentRoot");

		vhosts.append(vhost);
	}

	return vhosts;
}


