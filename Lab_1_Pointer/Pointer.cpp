#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <string>
#include <cctype>

#include "Pointer.h"
#include "MyStr.h"

using namespace std;

map<string, set<int>> pointer;

Pointer::Pointer() {}
Pointer::Pointer(string word, set<int> pages) {
    string p_word = MyStr::to_lowercase(word);
    pointer[p_word] = pages;
}
void Pointer::addPage(string word, int page) {
    string p_word = MyStr::to_lowercase(word);

    if (pointer.count(p_word) && pointer[p_word].size() < 11)
        pointer[p_word].insert(page);
}
void Pointer::setPointer(string word, set<int> pages) {
    string p_word = MyStr::to_lowercase(word);

    if (!pointer.count(p_word)) {
        if (pages.size() < 11)
            pointer[p_word] = pages;
        else
            cout << "The size of pages greater than 10";
    }
    else {
        cout << "This pointer already exists " << endl;
    }
}
void Pointer::setPointersByFile(string filePath) {
    ifstream file(filePath);

    if (file.is_open()) {
        string line;

        while (getline(file, line)) {
            string* splitedLine = MyStr::splite_line(line);

            string word = splitedLine[0];
            int page = stoi(splitedLine[1]);


            if (pointer.count(word)) {
                addPage(word, page);
            }
            else {
                setPointer(word, { {page} });
            }
        }

        file.close();
        cout << "Data from file was successfully added" << endl << endl;
    }
    else {
        cerr << "Unable to open file" << endl << endl;
    }
}
map<string, set<int>> Pointer::getPointer(string word) {
    string p_word = MyStr::to_lowercase(word);

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
    string p_word = MyStr::to_lowercase(word);

    if (pointer.count(p_word)) {
        return pointer[p_word];
    }

    return {};
}
int Pointer::deletePointer(string word) {
    return pointer.erase(MyStr::to_lowercase(word));
}
