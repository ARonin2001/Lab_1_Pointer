#include <iostream>

using namespace std;

#pragma once

#ifndef MYSTR_H
#define MYSTR_H

class MyStr
{
public:
	static string to_lowercase(string str);
	static string* splite_line(string line);
};

#endif