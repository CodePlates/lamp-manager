#include "apache_scanner.hpp"
#include "utilities.hpp"

A2Scanner::A2Scanner(QString filepath)
{
	contents = file_read(filepath);
	contents.append('\n');
}

Token A2Scanner::get_tok()
{
	currText = "";
	static QChar ch = contents.at(pos);
	
	while (pos < contents.length()) {

		ch = contents.at(pos);

		if (ch == '\n') {
			while (pos < contents.length() && contents.at(pos).isSpace()) {
				pos++;			
			}
			return Token::TOK_LINE_END;
		}

		else if (ch.isSpace()) {
			while(pos < contents.length() && contents.at(pos) != '\n' && contents.at(pos).isSpace()) {
				pos++;
			}
			continue; 
		}

		else if (ch == '#') {
			while (pos < contents.length() && ch != '\n') {
				ch = contents.at(pos++);
			}
			continue;
		}

		else if (ch == '\'' || ch == '\"') {
			pos++;
			while (pos < contents.length()) {
				QChar nextCh = contents.at(pos);
				if (nextCh == ch && contents.at(pos - 1) != '\\')
					break;
				currText.append(nextCh);
				pos++;
			}
			pos++;
			return Token::TOK_WORD;
		}

		else if (ch == '<'){
			if (contents.at(++pos) == '/') {
				pos++;
				return Token::TOK_CLOSE_TAG; 
			}else {
				return Token::TOK_OPEN_ANGLE;
			}
		}

		else if (ch == '>') {
			pos++;
			return Token::TOK_CLOSE_ANGLE; 
		}

		else {
			while (pos < contents.length() &&
				!contents.at(pos).isSpace() && 
				contents.at(pos) != '<' && 
				contents.at(pos) != '>' && 
				contents.at(pos) != '#') 
			{
					ch = contents.at(pos);
					currText.append(ch);
					pos++;
			}
			
			return Token::TOK_WORD;
		}

	}

	return Token::TOK_END;
}