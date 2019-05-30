#include<iostream>
#include<fstream>
#include"RE.h"
#include"FA.h"

using namespace std;

class RETestClass
{
public:
	void SingleCharacterTest()
	{
		cout << "SingleCharacterTest:" << endl;
		cout << "input a regular expression re(single character):" << endl;
		RE re;
		ifstream infile("re1.txt");
		infile >> re;
		//cin >> re;//>>'a'or any other character

		cout << "re=" << re << endl;//'a'
		cout << "re 1st symbol: " << re.First() << endl;//{'a'}
		cout << "re root_operator: " << re.root_operator() << endl;//2
		assert(re.root_operator() == 2);
		cout << "re operator number: " << re.num_operators() << endl;//1
		assert(re.num_operators() == 1);
		cout << "re symbol number: " << re.num_symbols() << endl;//1
		assert(re.num_symbols() == 1);
		cout << "re symbol: " << re.symbol() << endl;//'a'
		//cout << re.left_subexpr() << endl;(a single character or a string has no such property)
		//cout << re.right_subexpr() << endl;
	}

	void StringTest()
	{
		cout << "StringTest:" << endl;
		cout << "input a regular expression re(string):" << endl;
		RE re;
		ifstream infile("re2.txt");
		infile >> re;
		//cin >> re;//>>['a''c']or any other strings(输入方式必须类似于['a''c']，可更改字母)

		cout << "re=" << re << endl;//['a','c']
		cout << "re 1st symbol: " << re.First() << endl;//{['a','c']}
		cout << "re root_operator: " << re.root_operator() << endl;//2
		assert(re.root_operator() == 2);
		cout << "re operator number: " << re.num_operators() << endl;//1
		assert(re.num_operators() == 1);
		cout << "re symbol number: " << re.num_symbols() << endl;//1
		assert(re.num_symbols() == 1);
		cout << "re symbol: " << re.symbol() << endl;//['a','c']
		//cout << re.left_subexpr() << endl;(a single character or a string has no such property)
		//cout << re.right_subexpr() << endl;
	}

	/*
	using operaters as *,|,+ or ?
	*/
	void ComplexTest()
	{
		cout << "ComplexTest:" << endl;
		cout << "input a regular expression re:" << endl;
		RE re;
		ifstream infile("re3.txt");
		infile >> re;
		//cin >> re;//>>.*'a'*'b'

		cout << "re=" << re << endl;//.*'a'*'b'
		cout << "re 1st symbol: " << re.First() << endl;//{'a' 'b'}
		cout << "re root_operator: " << re.root_operator() << endl;//4
		assert(re.root_operator() == 4);
		cout << "re operator number: " << re.num_operators() << endl;//5
		assert(re.num_operators() == 5);
		cout << "re symbol number: " << re.num_symbols() << endl;//2
		assert(re.num_symbols() == 2);
		//cout << re.symbol() << endl;(operator isn't symbol)
		cout << "re left subexpression" << re.left_subexpr() << endl;//*'a' (exists only in using operators "|" or "or")
		cout << "re right subexpression" << re.right_subexpr() << endl;//*'b'
	}

	void CompareFunctionTest()
	{
		RE re1, re2;
		cout << "ComPareFunctionTest:" << endl;
		cout << "input first regular expression re1:" << endl;
		ifstream infile1("re4.txt");
		infile1 >> re1;
		//cin >> re1;
		cout << "input second regular expression re2:" << endl;
		ifstream infile2("re5.txt");
		infile2 >> re2;
		//cin >> re2;

		cout << "re1=" << re1 << endl;
		cout << "re2=" << re2 << endl;
		cout << "re1<re2? " << re1.operator<(re2) << endl;
		cout << "re1<=re2? " << re1.operator<=(re2) << endl;
		cout << "re1=re2? " << re1.operator==(re2) << endl;
		cout << "re1>re2? " << re1.operator>(re2) << endl;
		cout << "re1>=re2? " << re1.operator>=(re2) << endl;
		cout << "re1!=re2? " << re1.operator!=(re2) << endl;
		re1.operator=(re2);
		cout << "re1=" << re1 << endl;
	}
};

void RETest()
{
	RETestClass t;
	t.SingleCharacterTest();
	//t.StringTest();
	//t.ComplexTest();
	//t.CompareFunctionTest();
}