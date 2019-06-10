/******************************************************************
一个用来生成 TCT 工具所用的 ADS 文件的小工具。

本类接受DFA类的输出重定向函数【friend std::ostream& operator<<(std::ostream& os, const DFA& r)】的输出字符串，
生成TCT接受的.ADS文件。

DFA的字母V，接受字母'0' to '9'或'a' to 'z'或'A' to 'Z'。转换为TCT .ADS文件时，字母V的整数值约定如下：
case 1: ['0','9'] ==> [0,9]
case 2: ['a','z'] ==> [10,35]
case 3: ['A','Z'] ==> [36,61]
other case is illegal.
本类数据成员Trans，V存储的字母对应的整数值，可通过两个函数转换：label toADS_V(char v); 或 char toDFA_V(label v);

使用举例：

    TCTHelper tct1;
	// 由DFA对象生成ADS/test.ADS文件
	tct1.perform(dfa1, "test.ads");
	cout << "tct1:" << tct1 << endl;

	// 当前对象转换为DFA
	DFA_components dfa_com1 = tct1.getDFA();
	DFA dfa2(dfa_com1);
	cout << "dfa2:" << dfa2 << endl;

	// 依据ADS/test.ADS文件，生成当前对象
	TCTHelper tct2;
	tct2.adsToDFA("test.ads");
	cout << "tct2:" << tct2 << endl;

	// 判断两个tct对象是否相同，即代表同样一个DFA
	cout << "tct1 == tct2 ? " << (tct1 == tct2) << endl;
	assert(tct1 == tct2);

	// 键盘键入DFA，生成ADS文件
	cout << "键盘键入DFA\n";
	TCTHelper tct3;
	cin >> tct3;
	tct3.perform("DFATest.ADS"); //生成DFATest.ADS文件
	cout << "tct3:" << tct3 << endl;

	DFA_components dfa_com3 = tct3.getDFA();
	DFA dfa3(dfa_com3);
	cout << "dfa3:" << dfa3 << endl;

******************************************************************/


#ifndef TCTHelper_H
#define TCTHelper_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <assert.h>
#include "DFA.h"
#include "DFA_components.h"

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32



typedef int state;
typedef int label;

// (stprime,T,stdest) 
struct Transition
{
	state stprime;
	label T;
	state stdest;
	Transition() :stprime(0), T(0), stdest(0) {};
	bool operator==(const Transition &D)
	{
		return (stprime == D.stprime&&T == D.T&&stdest == D.stdest);
	}
	bool operator!=(const Transition &D)
	{
		return !(*this==D);
	}
	bool operator<(const Transition &D)
	{
		if (stprime == D.stprime)
		{
			return (T < D.T);
		}
		else
		{
			return (stprime < D.stprime);
		}
	}
};

class TCTHelper
{
public:
	TCTHelper();
	// 通过str(通常为DFA的输出字符串)构造TCTHelper对象
	TCTHelper(std::string str);
	// 通过dfa构造TCTHelper对象
	TCTHelper(DFA &dfa);
	~TCTHelper();
	// 通过str(通常为DFA的输出字符串)重新构造当前对象
	TCTHelper& reconstruct(std::string str);
	// 状态数
	size_t size();
	// 当前对象生成DFA_components对象
	DFA_components getDFA();
	// 依据ADS/adsfilename.ADS文件，生成当前对象
	bool adsToDFA(std::string adsfilename);
	// 当前对象生成默认的ADS/DFA.ADS文件
	bool perform();
	// 当前对象生成ADS/filepath.ADS文件
	bool perform(std::string filepath);
	// DFA对象生成.ADS文件
	bool perform(DFA &dfa, std::string filepath);
	TCTHelper& clear();
	friend std::istream& operator>>(std::istream& input, TCTHelper& D);  
	friend std::ostream& operator<<(std::ostream& output, TCTHelper& D); 
	bool operator==(TCTHelper& D);                                       
	bool quite;  // 这里是为命令参数设置的一个选项。
private:
	// 将DFA的输出字符串解析成为本类可以识别的格式。
    // 开始状态编号均为整数0
	bool analyze(std::string& str);  // 解析类 DFA 的输出，当作字符串来解析
	bool check(const state& t);
	std::vector<Transition> Trans;
	//std::vector<state> initial;
	std::vector<state> F;  // Final State Set. 正整数
	std::vector<state> Q;  // StatePool ，预留
	std::vector<label> V;  // 接受字母'0'至'z'。约定：如果'0' <= 所有字母 <= '9'，则V的整数值对应0 ~ 9; 如果'a' <= 所有字母 <= 'z'，则V的整数值对应10+0,10+1,...10+25; 
	std::string theDFA;     // 保存类DFA的输出
	std::string adsDirectory; // .ADS文件所在目录
	size_t num_state;         // 状态数

	/*******************************************
	 按照约定，DFA转移表字母的整数值:
	 case 1: ['0','9'] ==> [0,9]
	 case 2: ['a','z'] ==> [10,35]
	 case 3: ['A','Z'] ==> [36,61]
	 other case is illegal.
	 *******************************************/
	label toADS_V(char v);
	char toDFA_V(label v);
	
	/*******************************************
	 按照约定，字母必须是['0','9'] || ['a','z'] || ['A','Z'].
	 other case is illegal.
	 *******************************************/
	bool isV(char c);
    
	// 处理DFA输出的一行字符串
	// 返回本行末尾字符'\n'的位置索引。如果处理结束，返回std::string::npos。
	std::string::size_type processLine(const std::string &str, std::string::size_type pos1);
	
	// 记录处理DFA输出的transitions line行数，总行数与状态数(num_state)相同。
	int transitionsLineNum;
};

#endif // !TCTHelper_H

