// Test.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <cstdlib>
// 去下行注释则禁用 assert()
// #define NDEBUG
#include <cassert>  // 必须包含
#include <cstring>
#include <string>
#include <vector>

#include "Test.h"

using namespace std;

A fun1()
{
	A a(20); // 调用自定义构造函数，构造a对象
	return a;
}

// 【非法】虽然程序能执行，但是返回一个局部变量的地址是不可取的
A& fun2()
{
	A a(30);   // 调用自定义构造函数，构造a对象
	return a;  // warning C4172 : 返回局部变量或临时变量的地址: a
}

void fun4()
{
	A a1;      // 调用默认构造函数，构造a1对象
	A a2(10);  // 调用自定义构造函数，构造a2对象
	A a3(a2);  // 调用复制构造函数，构造a3对象
	A a4 = a3; // 调用复制构造函数，构造a4对象
}

void fun3()
{
	// 调用复制构造函数，把fun1()的返回值拷贝给a1. 本语句结束，调用析构函数，销毁函数返回对象
	A a1 = fun1();  
	cout << a1.n << endl;
	a1.n = 30;
    
	A aa; // 调用默认构造函数，构造aa对象
	aa = a1; //调用操作符=重载
	aa.n = 40;

	// error C2440: “初始化”: 无法从“A”转换为“A &”
	// note: 非常量引用只能绑定到左值
	//A& a2 = fun1(); 
	//cout << a2.n << endl;

	// 以下调用不推荐
	// A a3 = fun2();
	// cout << a3.n << endl;
 
}

void pfun1(const int *a)
{
	//*a = 100;  // 非法
	a++;
	cout << *a << endl;
}

void pfun2(int const *a)
{
	//*a = 100;  // 非法
	cout << *a << endl;
}

void pfun3(int *const a)
{
	*a = 100;  // 合法
	cout << *a << endl;
}

void pfun4(int const &a)
{
	// a = 100;  // 非法
	cout << a << endl;
}

void pfun5(const int  &a)
{
	// a = 100;  // 非法
	cout << a << endl;
}


void constTest()
{
	int c = 200;
	pfun3(&c);
	cout << c << endl;

	/*****************
	 变量说明中有'*',则说明是定义指针变量。
	 以'*'为界，根据const在'*'的左右侧，区分指针指向的内容是常量，还是指针本身是常量。
	 const在'*'左侧，则其修饰指针指向的内容是常量;
	 const在'*'右侧，则其修饰指针本身是常量;
	 在'*'左右都有const，则指针本身和指向的内容均为常量。
	 *****************/
	int b = 100;
	const int *a1 = &b;  // const在'*'左侧,则其修饰指针指向的内容是常量。
	int const *a2 = &b;  // 同上
	// *a1 = 200; *a2 = 200; // 非法
	int *const a3 = &b;  // 指针a3本身是常量
	// a3++;  // 非法
	const int* const a4 = &b; // 指阵a4本身和内容均为常量
	//a4++; *a4 = 200; // 非法

	const int &b1 = b;
	int const &b2 = b;
	int &const b3 = b;
	int &b5 = b;
	const int& const b4 = b;
	// b1 = 200, 非法y
	// b2 = 200 //非法
	// b4 = 300; 非法
	b3 = 200; 
	b5 = 300;
	cout << b1<<'\t'<<b2<<'\t'<<b3 << '\t' << b4 << endl;
	cout << *a1 << '\t' << *a2 << '\t' << *a3 << '\t' << *a4 << endl;
    
}

int main1()
{
	
	constTest();
	//fun4();
	// fun3();
	system("pause");
	return 0;
}
/**
自定义构造函数：20
复制构造函数：20
析构函数:20
20
默认构造函数：0
析构函数:30
析构函数:30
请按任意键继续. . .
 **/

int main2()
{
	//int n, a[100][100];
	int n = 4, a[4][4] = { {1,5,3,9},{3,7,5,6},{9,4,6,4},{7,3,1,3} };

	// Finite State Machine
	int i = 0, j = 0, last = 1, next = 1; // last,next = 1,水平，2竖直，3斜下，4斜上 

	printf("%d ", a[0][0]);
	while (1)
	{
		if (i == n - 1 && j == n - 1) break;
		last = next;
		switch (last)
		{
		case 1: // 水平 
			assert(i == 0 || i == n - 1);
			assert(j < n - 1);
			j++;
			if (i == 0) next = 3; // 转斜下 
			else if (i == n - 1) next = 4; // 转斜上 
			break;
		case 2: // 竖直 
			assert(j == 0 || j == n - 1);
			assert(i < n - 1);
			i++;
			if (j == 0) next = 4; // 转斜上 
			else if (j == n - 1) next = 3; // 转斜下 
			break;
		case 3: // 斜下 
			i++; j--;
			if (i > n - 1) i = n - 1;
			if (j < 0) j = 0;

			if (j == 0)
			{
				if (i == n - 1) next = 1; // 转水平 
				if (i < n - 1) next = 2; // 转竖直
			}
			else if (i == n - 1) next = 1; // 转水平 
			break;
		case 4:	// 斜上 
			i--; j++;
			if (i < 0) i = 0;
			if (j > n - 1) j = n - 1;
			if (i == 0)
			{
				if (j == n - 1) next = 2; // 转竖直 
				if (j < n - 1) next = 1; // 转水平	
			}
			else if(j == n-1) next = 2; // 转竖直 
			break;
		}
		printf("%d ", a[i][j]);
	}

	return 0;
}


int main3()
{
	char current[200] = "/d2/d3/d7";
	char command[100][200];  // cd command
	char tmp[200];
	int i, commandNum = 0;

	gets_s(current,100);
	while (1)
	{
		gets_s(tmp,100);
		if (strcmp(tmp, "pwd") == 0) break;
		// strcpy(command[commandNum],&tmp[3]);
		strcpy_s(command[commandNum], tmp);
		//puts(command[commandNum]);
		commandNum++;
	}

	puts("=============");
	for (i = 0; i < commandNum; i++)
	{
		puts(command[i]);
	}

	return 0;
}

// s1 <= s2: s1各字符小于等于s2中的对应字符；或者有大有小，return true
// s1 > s2:  s1各字符大于s2中的对应字符，retrun false
bool compareStr(const string s1, const string s2)
{
	bool flag;
	for (string::const_iterator it2 = s1.begin(); it2 != s1.end(); it2++) {
		flag = true;  // 假设 s1 > s2
		for (string::const_iterator it3 = s2.begin(); it3 != s2.end(); it3++) 
			if (*it2 < *it3) { flag = false;  break; }  
		if (!flag) break;
	}
	return (!flag);
}

int main4()
{
	//vector<string> S = { "0110","0111","2000","1110","0011","2222" };
	vector<string> S = { "1222","3333","0344" };
	vector<string>::iterator max_it = S.begin();  // 首先假定"最大"的string是S的第一个元素
	string max = *max_it;
	for (vector<string>::iterator it = S.begin() + 1; it != S.end(); it++) {
		if (!compareStr(*it, max)) { max = *it; max_it = it; }
	}
	// 删除max，即是所求
	S.erase(max_it);

	// 验证
	for (vector<string>::iterator it = S.begin(); it != S.end(); it++)
		cout << *it << '\t';
	cout << endl;
	return 0;
}

int main5()
{
	//vector<string> S = { "0110","0111","2000","1110","0011","2222" };
	vector<string> S = { "1222","3333","0344" };
	vector<string>::iterator max_it = S.begin();  // 首先假定"最大"的string是S的第一个元素
	string max = *max_it;
	bool flag;
	for (vector<string>::iterator it = S.begin() + 1; it != S.end(); it++) {
		string c = *it;
		flag = true;  // 假定c > max
		// c与max比较
		for (string::iterator it2 = c.begin(); it2 != c.end(); it2++) {
			for (string::iterator it3 = max.begin(); it3 != max.end(); it3++) {
				if (*it2 < *it3) { flag = false;  break; }
			}
			if (!flag) break; // c < c1
		}
		if (flag) { max = c; max_it = it; }
	}
	
	// 删除max，即是所求
	S.erase(max_it);

	// 验证
	for (vector<string>::iterator it = S.begin(); it != S.end(); it++)
		cout << *it << '\t';
	cout << endl;
	return 0;
}

int main()
{
	// https://zh.cppreference.com/w/cpp/language/array
	// 在用于 new[] 表达式时，数组的大小可以为零；这种数组无元素：
	// int* p = new int[0]; // 访问 p[0] 或 *p 为未定义
	// delete[] p; // 仍然要求清理
	int *data = 0, *data1 = 0;
	data = new int[1];
	data1 = new int[0];
	cout << (data == 0) << endl; // 0
	cout << (data1 == 0) << endl; // 0
	delete[] data;  // delete后，data并不等于0（地址）
	delete[] data1;
	cout << (data == 0) << endl; // 0
	cout << (data1 == 0) << endl; // 0
	return 0;
}

