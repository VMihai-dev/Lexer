#include <iostream>
#include<fstream>
#include <sstream>       
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
		NUMBER,
		WORD,
		LETTER,
		OPERATOR,
		COMMENT,
		UNKNOW,
	};
	Token(Type type, char value) : myType{ type }, myValue{ value } {}
	Token(Type type, string stringValue) : myType{ type }, stringValue{ stringValue } {}

	Type getType() { return myType; }
	string getValue() { if (myValue == '@') { return stringValue; } else { string s(1, myValue); return s; } }

private:
	Type myType;
	char myValue = '@';
	string stringValue;
};

class Lexer {
public:
	Lexer (string code) : myPath{code} {
		std::ifstream myReadFile;
		myReadFile.open(code);
		if (myReadFile.is_open()) {
			std::stringstream buffer;
			buffer << myReadFile.rdbuf();
			myCode = buffer.str();
		}
		else {
			std::cout << "Failed to open file";
			exit(1);
		}
		myReadFile.close();
	}
	string myCode;
private:
	string myPath;
	
};



Token::Type checkChar(char c) {
	if (c == ' ') {
		//Token myToken(Token::Type::WHITESPACE, c);
		return Token::Type::WHITESPACE;
	}

	for (int i = 48; i <= 57; i++) {
		if (i == c) {
		//	Token myToken(Token::Type::DIGIT, c);
			return Token::Type::DIGIT;
		}
	}

	char upperChar = 'A';
	for (char lowerChar = 'a'; lowerChar <= 'z'; lowerChar++) {
		if (c == lowerChar || c == upperChar) {
		//	Token myToken(Token::Type::WORD, formWord());
			return Token::Type::LETTER;
		}
		upperChar++;
	}

	//Token myToken(Token::Type::UNKNOW, c);
	return Token::Type::UNKNOW;
}
Token formWord(string myString, int &pos) {
	vector<char> myTokenVec;
	myTokenVec.push_back(myString[pos]);

	int nextPos = pos + 1;
	while (pos < myString.length() && checkChar(myString[nextPos]) == Token::LETTER) {
		myTokenVec.push_back(myString[nextPos]);
		nextPos++;
		pos++;
	}
	string myTokenString(myTokenVec.begin(), myTokenVec.end());
	Token myTokenObj(Token::Type::WORD, myTokenString);
	return myTokenObj;
}

Token formNumber(string myString, int &pos) {
	vector<char> myTokenVec;
	myTokenVec.push_back(myString[pos]);

	int nextPos = pos + 1;
	while (pos < myString.length() && checkChar(myString[nextPos]) == Token::DIGIT) {
		myTokenVec.push_back(myString[nextPos]);
		nextPos++;
		pos++;
	}
	string myTokenString(myTokenVec.begin(), myTokenVec.end());
	Token myTokenObj(Token::Type::NUMBER, myTokenString);
	return myTokenObj;
}

vector<Token> tokenList(string myString) {
	vector<Token> tkList;
	for (int i = 0; i <= myString.length(); i++) {
		Token::Type myTokenType = checkChar(myString[i]);
		if (myTokenType == Token::WHITESPACE) {
			continue;
		} 
		else if (myTokenType == Token::LETTER) {
			tkList.push_back(formWord(myString, i));
		}
		else if (myTokenType == Token::DIGIT) {
			tkList.push_back(formNumber(myString, i));
		}
		else {
			Token myToken(Token::Type::UNKNOW, myString[i]);
			tkList.push_back(myToken);
		}
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
		case Token::Type::WORD:
			return "WORD";
		case Token::Type::NUMBER:
			return "NUMBER";
		case Token::Type::LETTER:
			return "LETTER";
		}
	return "NOTHING";
}

int main() {
	string path = "C:\\Users\\mvisan\\Desktop\\smartScriptingCode.txt.txt";
	Lexer myLex(path);
	string code = myLex.myCode;

	vector<Token> tkList;
	tkList = tokenList(code);
	for (int i = 0; i < tkList.size(); i++){
		std::cout << enumToString(tkList[i].getType()) << " : " << tkList[i].getValue() << "\n";
	}
}