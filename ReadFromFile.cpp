#include<iostream>
#include<fstream>
#include <sstream>      
using namespace std;

int main() {

    ifstream myReadFile;
    myReadFile.open("C:\\Users\\mvisan\\Desktop\\smartScriptingCode.txt.txt");
    string myString;

    if (myReadFile.is_open()) {
        stringstream buffer;
        buffer << myReadFile.rdbuf();
        myString = buffer.str();
    }
    else {
        cout << "Failed to open file";
        exit(1);
    }
    myReadFile.close();
    cout << "Ass";
    cout << myString;
    return 0;
}
