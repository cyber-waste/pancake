#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>

using namespace std;

char* DELIMITER_CHARS = " )(.\t\n,";

int main(int argc, char* argv[]) {
    set<char> delimiters;
    for (int i=0; DELIMITER_CHARS[i]!='\0'; i++) { 
        delimiters.insert(DELIMITER_CHARS[i]);
    }
    
    if (argc < 2){
        cout << "missing file name" << endl;
        return 1;
    }

    set<string> result;

    char* file_name = argv[1];
    ifstream file(file_name);
    if (file.is_open()) {
        string currentWord;
        char currentSymbol;
        set<char> workSymbols;
        bool accept = true;

        while (file >> noskipws >> currentSymbol) {
            cout << currentSymbol;

            if (delimiters.find(currentSymbol) == delimiters.end()) {
                currentWord.push_back(currentSymbol);

                if (workSymbols.find(currentSymbol) != workSymbols.end()) {
                    accept = false;
                }
                workSymbols.insert(currentSymbol);
            } else {
                if (currentWord.length() > 0) {
                    if (accept) {
                        result.insert(currentWord);
                    }
                    accept = true;

                    string newWord;                    
                    currentWord = newWord;
                    workSymbols.clear();
                }
            }
        }
        
        if (currentWord.length() > 0) {
            if (accept) {
                result.insert(currentWord);
            }
            accept = true;    

            string newWord;                    
            currentWord = newWord;
            workSymbols.clear();
        }

        for (set<string>::iterator it = result.begin(); it != result.end(); ++it) {
            cout << (*it) << endl;
        }
    } else { 
        cout << "Can't open file" << endl;
        return 1;
    }
    
    return 0;
}
