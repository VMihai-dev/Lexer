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


Token checkChar(char c) {
	if (c == ' ' || c == 'n') {
		Token myToken(Token::Type::WHITESPACE, c);
		return myToken;
	}

	for (int i = 48; i <= 57; i++) {
		if (i == c) {
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

vector<Token> tokenList(string myString) {
	vector<Token> tkList;
	for (int i = 0; i <= myString.length(); i++) {
		tkList.push_back(checkChar(myString[i]));
	}

	return tkList;
}

string enumToString(Token::Type myType) {
	switch (myType) {
		case Token::Type::UNKNOW:
			return "UNKNOW";
		case Token::Type::WHITESPACE:
			return "WHITESPACE";
		case Token::Type::DIGIT:
			return "DIGIT";
		case Token::Type::LETTER:
			return "LETTER";
		}
	return "NOTHING";
}

int main() {
	vector<Token> tkList;
	string code = "int a = 0; ?? hey 1234 boom \n \n \n \n";
	tkList = tokenList(code);
	for (int i = 0; i < tkList.size(); i++){
		std::cout << enumToString(tkList[i].getType()) << " : " << tkList[i].getValue() << "\n";
	}
}