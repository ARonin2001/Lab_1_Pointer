#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <string>
#include <cctype>

#include "Pointer.h"

using namespace std;

map<string, set<int>> pointer;

Pointer::Pointer() {}
Pointer::Pointer(string word, set<int> pages) {
    string p_word = to_lowercase(word);
    pointer[p_word] = pages;
}
void Pointer::addPage(string word, int page) {
    string p_word = to_lowercase(word);

    if (pointer.count(p_word) && pointer[p_word].size() < 10)
        pointer[p_word].insert(page);
}
void Pointer::setPointer(string word, set<int> pages) {
    string p_word = to_lowercase(word);

    if (pointer.count(p_word)) {
        if (pointer[p_word].size() == 10) {
            cout << "The number of pages is equal 10" << endl;
            return;
        }

        int countPages = pointer[p_word].size() + pages.size();

        if (countPages < 11) {
            for (int i : pages) {
                pointer[p_word].insert(i);
            }
        }
        else {
            cout << "The number of pages should not be more than " << 10 - pointer[p_word].size() << endl;
        }

        return;
    }

    if (pages.size() < 11) {
        pointer[p_word] = pages;
    }
    else {
        cout << "The number of pages cannot be more than 10" << endl;
    }
    
}
void Pointer::setPointersByFile(string filePath) {
    ifstream file(filePath);

    if (file.is_open()) {
        string line;

        while (getline(file, line)) {
            string* splitedLine = splite_line(line);

            string word = splitedLine[0];
            int page = stoi(splitedLine[1]);


            if (pointer.count(word)) {
                addPage(word, page);
            }
            else {
                setPointer(word, set<int> {page} );
            }
        }

        file.close();

        cout << "-----RESULT----\n\n";
        cout << "Data from file was successfully added" << endl << endl;
        cout << "-----RESULT----\n\n";

    }
    else {
        cout << "-----RESULT----\n\n";
        cerr << "Unable to open file" << endl << endl;
        cout << "-----RESULT----\n\n";
    }
}
map<string, set<int>> Pointer::getPointer(string word) {
    string p_word = to_lowercase(word);

    if (pointer.count(p_word)) {
        auto it = pointer.find(p_word);
        map<string, set<int>> p;
        p[it->first] = it->second;

        return p;
    }
    else {
        cout << "This pointer is not exists" << endl << endl;

        return map<string, set<int>> {};
    }
}
set<int> Pointer::getPages(string word) {
    string p_word = to_lowercase(word);

    if (pointer.count(p_word)) {
        return pointer[p_word];
    }

    return {};
}
int Pointer::deletePointer(string word) {
    return pointer.erase(to_lowercase(word));
}

//Методы для работы со строками
string Pointer::to_lowercase(string str)
{
    string toLowerStr = "";
    for (int i = 0; i < str.size(); i++) {
        toLowerStr += tolower(str[i]);
    }
    return toLowerStr;
}

string* Pointer::splite_line(string line) {
    string first, second;
    bool isComma = false;

    for (int i = 0; i < line.size(); i++) {
        if (isComma) {
            if (line[i] != ' ' && line[i] != ',') {
                second += line[i];
            }
        }

        if (line[i] == ',') isComma = true;

        if (!isComma) {
            first += line[i];
        }
    }

    first = to_lowercase(first);

    return new string[]{ first, second };
}
