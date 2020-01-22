#include <iostream>
#include <vector>
using std::vector;

#include <string>
using std::string;

// Class to constract a Token, types grabbed from wikipedia.
class Token {
public:
	enum Type
	{
		WHITESPACE,
		DIGIT,
		LETTER,
		OPERATOR,
		COMMENT,
		UNKNOW,
	};
	Token(Type type, char value) : myType{ type }, myValue{ value } {}
	
	Type getType() { return myType; }
	char getValue() { return myValue; }

private:
	Type myType;
	char myValue;
};

class Lexer {
public:
	Lexer (string code) : myString{code} {}
	

private:
	string myString;
};

vector<Token> tokenList(string myString) {
	vector<Token> tkList;
	for (int i = 0; i <= myString.length(); i++) {

	}

	return tkList;
}

Token checkChar(char c) {
	if (c == ' ' || c == '\n') {
		Token myToken(Token::Type::WHITESPACE, c);
		return myToken;
	}

	for (int i = 0; i <= 9; i++) {
		if ((char)i == c) {
			Token myToken(Token::Type::DIGIT, c);
			return myToken;
		}
	}

	char upperChar = 'A';
	for (char lowerChar = 'a'; lowerChar <= 'z'; lowerChar++) {
		if (c == lowerChar || c == upperChar) {
			 Token myToken(Token::Type::LETTER, c);
			 return myToken;
		}
		upperChar++;
	}

	Token myToken(Token::Type::UNKNOW, c);
	return myToken;
}
int main() {
 
}