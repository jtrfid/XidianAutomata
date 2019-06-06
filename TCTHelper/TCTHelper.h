/******************************************************************
一个用来生成 TCT 工具所用的 ADS 文件的小工具。

本类接受DFA类的输出重定向函数【friend std::ostream& operator<<(std::ostream& os, const DFA& r)】的输出字符串，
生成TCT接受的.ADS文件。

这里还提供一个生成 FIRE engine 中的类 DFA 的方法，也即成员函数 getDFA()。

不过在执行这个函数之前，得先确保已经有了一个 TCTHelper 对象，无论是通过键盘键入，还是通过另外一个DFA对象进行解析。

因为类 DFA 要求label 为一个 char 变量，而 TCT tools 要求label 为正整数，所以使用这个类的要求是，label为[0,9]，算是一点妥协。


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
	// 依据.ADS文件，生成当前对象
	bool adsToDFA(std::string adsfilename);
	// 当前对象生成默认的DFA.ADS文件
	bool perform();
	// 当前对象生成.ADS文件
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
	std::vector<label> V;  // .为 [0,9] 的整数
	std::string theDFA;     // 保存类DFA的输出
	std::string adsDirectory; // .ADS文件所在目录
	size_t num_state;
};



#endif // !TCTHelper_H

