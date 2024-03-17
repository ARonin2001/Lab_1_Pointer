#include <string>
#include <iostream>
#include "MyStr.h"

using namespace std;

string MyStr::to_lowercase(string str)
{
    string toLowerStr = "";
    for (int i = 0; i < str.size(); i++) {
        toLowerStr += tolower(str[i]);
    }
    return toLowerStr;
}

string* MyStr::splite_line(string line) {
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