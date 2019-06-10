#pragma once
#include <string>
#include <algorithm>
#include <functional>  

using namespace std;

static class Tools
{
public:
	Tools();
	~Tools();
	static string& ltrim(string &str) {
		string::iterator p = find_if(str.begin(), str.end(), not1(ptr_fun<int, int>(isspace)));
		str.erase(str.begin(), p);
		return str;
	}

	static string& rtrim(string &str) {
		string::reverse_iterator p = find_if(str.rbegin(), str.rend(), not1(ptr_fun<int, int>(isspace)));
		str.erase(p.base(), str.end());
		return str;
	}

    static string& trim(string &str) {
		ltrim(rtrim(str));
		return str;
	}
};

