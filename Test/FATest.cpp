#include<iostream>
#include<fstream>
#include"FA.h"
#include"RE.h"

using namespace std;

class FATestClass
{
public:
	void FA_RETest1()
	{
		cout << "input a regular expression re:" << endl;
		RE re;
		ifstream infile("re3.txt");
		infile >> re;
		//cin >> re;//>>.*'a'*'b'
		cout << "re=" << re << endl;//.*'a'*'b'
		FA fa(re);
		cout << fa << endl;
	}

	void FA_RETest2()
	{
		cout << "input a regular expression re:" << endl;
		RE re;
		ifstream infile("re6.txt");
		infile >> re;
		//cin >> re;//>>|?'a'+'b'
		cout << "re=" << re << endl;//|?'a'+'b'
		FA fa(re);
		cout << fa << endl;
	}

	void FA_RETest3()
	{
		cout << "input a regular expression re:" << endl;
		RE re;
		ifstream infile("re7.txt");
		infile >> re;
		//cin >> re;//>>|'a'1
		cout << "re=" << re << endl;//|'a'1
		FA fa(re);
		cout << fa << endl;
	}
};

void FATest()
{
	FATestClass fat;
	//fat.FA_RETest1();
	//fat.FA_RETest2();
	fat.FA_RETest3();
}