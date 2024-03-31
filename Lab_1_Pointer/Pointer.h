#include <iostream>
#include <map>
#include <set>

using namespace std;

#pragma once

#ifndef POINTER_H
#define PONTER_H

class Pointer
{
private:
    map<string, set<int>> pointer;

public:
    Pointer();
    Pointer(string word, set<int> pages);

    void addPage(string word, int page);
    void setPointer(string word, set<int> pages);
    void setPointersByFile(string filePath);

    map<string, set<int>> getPointer(string word);
    set<int> getPages(string word);

    int deletePointer(string word);

    static string to_lowercase(string str);
    static string* splite_line(string line);

};

#endif