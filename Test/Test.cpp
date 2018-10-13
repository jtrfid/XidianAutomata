// Test.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>

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

int main()
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

