// Automata.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cstdlib>
#include <string>
#include <sstream>
#include "CharRange.h"
#include "TransRel.h"
#include "StateTo.h"
#include "DTransRel.h"
#include "constrs.h"
#include "Sigma.h"
#include "DFA.h"
#include "FA.h"

using namespace std;

/****************************************************************
 Reg<RE> thest:
 no-basis operator(epsilon,empty,symbol): this ==> left = right = 0
 unary operator(star,plus,question): this ==> left = this, right = 0
 binary operator(union(or),concat): this ==> left(this) operator right
 ****************************************************************/
int main1()
{
	/////////////// no-basis operator(epsilon,empty,symbol): this ==> left = right = 0
	// RE = epsilon
	Reg<RE> re1;
	//Reg<RE> re1 = Reg<RE>(); // 等效
	re1.epsilon();
	cout << re1 << endl; // 1  ==> op = EPSILON, left = right = 0

	// RE = empty
	Reg<RE> re2;
	re2.empty();
	cout << re2 << endl;  // 0  ==> op = EMPTY, left = right = 0

	//// RE = a
	Reg<RE> re3;
	re3.symbol('a'); 
	cout << re3 << endl; // a  ==> op = SYMBOL, left = right = 0 

	////////////////////// unary operator(star,plus,question): this ==> left = this, right = 0
	/////// RE = b *
	Reg<RE> re4;
	re4.symbol('b');
	re4.star();
	cout << re4 << endl;  // * 'b' ==> op = STAR, left = b, right = 0

	/////// RE = b +
	Reg<RE> re41;
	re41.symbol('b');
	re41.plus();
	cout << re41 << endl;  // + 'b' ==> op = PLUS, left = b, right = 0

	/////// RE = b ?
	Reg<RE> re42;
	re42.symbol('b');
	re42.question();
	cout << re42 << endl;  // ? 'b'  ==> op = QUESTION, left = b,right = 0

	/////////////// binary operator(union(or),concat): this ==> left(this) operator right
	//// RE =  a | epsilon
	Reg<RE> left, right;
	left.symbol('a');
	right.epsilon();
	left.Or(right);
	cout << left << endl;  // | 'a' 1(epsilon) ==> op = Or, left = a, right = EPSILON

	//// RE =  a concat epsilon
	left.symbol('a');
	right.epsilon();
	left.concat(right);
	cout << left << endl;  // . 'a' 1(epsilon) ==> op = CONCAT, left = a, right = EPSILON

	////////////////////////////// 综合应用
	// RE = (a | epsilon)b* 

	//// RE =  a | epsilon
	left.symbol('a');
	right.epsilon();
	left.Or(right);
	cout << left << endl;  // | 'a' 1(epsilon)

	// b *
	right.symbol('b');
	right.star();
	cout << right << endl; // * 'b'
						   
	// (a | epsilon) concat b* 
	left.concat(right);
	cout << left << endl; // . | 'a' 1(epsilon) * 'b'  ==> op = .,left = (| 'a' 1(epsilon)),right = (* b)

	system("pause");
	return 0;
}

/****************************************************************
	 Thompson's construction[Wat93a, Construction 4.5] test:
	 Reg<RE> re1;
	 //FA fa1(re1);
	 FA fa1 = Thompson(re1);  // 等效
 ****************************************************************/
int main2()
{
	/////////////// no-basis operator(epsilon,empty,symbol): this ==> left = right = 0
	// RE = epsilon
	Reg<RE> re1;
	//Reg<RE> re1 = Reg<RE>(); // 等效
	re1.epsilon();
	cout << re1 << endl; // 1  ==> op = EPSILON, left = right = 0
	//FA fa1(re1);
	//FA fa1 = FA(re1);   // 等效
	FA fa1 = Thompson(re1);  // 等效
	cout << "fa1:" << fa1 << endl; 
	/**
	FA
	Q = [0,2), S = {0}, F = {1}
	Transitions = 0->{}  1->{}
	E =	0->{ 1 }  1->{}
	current = {}
	**/

	// RE = empty
	Reg<RE> re2;
	re2.empty();
	cout << re2 << endl;  // 0  ==> op = EMPTY, left = right = 0
	// FA fa2(re2);
	FA fa2 = Thompson(re2);  // 等效
	cout << "fa2:" << fa2 << endl; 
	/**
	FA
	Q = [0,2), S = {0}, F = {1}
	Transitions = 0->{}  1->{}
	E =	0->{}  1->{}
	current = {}
	**/

	//// RE = a
	Reg<RE> re3;
	re3.symbol('a');
	//FA fa3(re3);
	FA fa3 = Thompson(re3);  // 等效
	cout << "fa3:" << fa3 << endl;  // a  ==> op = SYMBOL, left = right = 0
	/**
	FA
	Q = [0,2), S = {0}, F = {1}
	Transitions = 0->{ 'a'->1 }  1->{}
	E =	0->{}  1->{}
	current = {}
	**/

	////////////////////// unary operator(star,plus,question): this ==> left = this, right = 0
	/////// RE = b *
	Reg<RE> re4;
	re4.symbol('b');
	re4.star();
	cout << re4 << endl;  // * 'b' ==> op = STAR, left = b, right = 0
	//FA fa4(re4);
	FA fa4 = Thompson(re4);  // 等效
	cout << "fa4:" << fa4 << endl;
	/**
	FA
	Q = [0,4), S = {0}, F = {1}
	Transitions = 0->{}  1->{} 2->{ 'b'->3 }  3->{}
	E =	0->{ 1 2 },1->{},2->{},3->{ 1 2 }
	current = {}
	**/

	/////// RE = b +
	Reg<RE> re41;
	re41.symbol('b');
	re41.plus();
	cout << re41 << endl;  // + 'b' ==> op = PLUS, left = b, right = 0
	//FA fa41(re41);
	FA fa41 = Thompson(re41);  // 等效
	cout << "fa41:" << fa41 << endl;
	/**
	FA
	Q = [0,4), S = {0}, F = {1}
	Transitions = 0->{}  1->{} 2->{ 'b'->3 }  3->{}
	E =	0->{ 2 },1->{},2->{},3->{ 1 2 }
	current = {}
	**/

	/////// RE = b ?
	Reg<RE> re42;
	re42.symbol('b');
	re42.question();
	cout << re42 << endl;  // ? 'b'  ==> op = QUESTION, left = b, right = 0
	//FA fa42(re42);
	FA fa42 = Thompson(re42);  // 等效
	cout << "fa42:" << fa42 << endl;
	/**
	FA
	Q = [0,4), S = {0}, F = {1}
	Transitions = 0->{}  1->{} 2->{ 'b'->3 }  3->{}
	E =	0->{ 1 2 },1->{},2->{},3->{ 1 }
	current = {}
	**/

	/////////////// binary operator(union(or),concat): this ==> left(this) operator right
	//// RE =  a | epsilon
	Reg<RE> left, right;
	left.symbol('a');
	right.epsilon();
	left.Or(right);
	cout << left << endl;  // | 'a' 1(epsilon) ==> op = Or, left = a, right = EPSILON
	//FA fa43(left);
	FA fa43 = Thompson(left);  // 等效
	cout << "fa43:" << fa43 << endl;
	/**
	Q = [0,6), S = {0}, F = {1}
	Transitions = 2->{ 'a'->3 }
	E =	0->{ 2 4 },3->{ 1 },4->{ 5 },5->{ 1 }
	**/

	//// RE =  a concat epsilon
	left.symbol('a');
	right.epsilon();
	left.concat(right);
	cout << left << endl;  // . 'a' 1(epsilon) ==> op = CONCAT, left = a, right = EPSILON
	//FA fa44(left);
	FA fa44 = Thompson(left);  // 等效
	cout << "fa44:" << fa44 << endl;
	/**
	Q = [0,4), S = {0}, F = {1}
	Transitions = 0->{ 'a'->2 }
	E =	0->{ },2->{ 3 },3->{ 1 }
	**/

	////////////////////////////// 综合应用
	// RE = (a | epsilon)b* 
	
	//// RE =  a | epsilon
	left.symbol('a');
	right.epsilon();
	left.Or(right);
	cout << left << endl;  // | 'a' 1(epsilon)
	//FA fa5(left);
	FA fa5 = Thompson(left);  // 等效
	cout << "fa5:" << fa5 << endl;
	/**
	Q = [0,6), S = {0}, F = {1}
	Transitions = 2->{ 'a'->3 }
	E =	0->{ 2 4 },3->{ 1 },4->{ 5 },5->{ 1 }
	**/

	// b *
	right.symbol('b');
	right.star();
	cout << right << endl; // * 'b'
	// (a | epsilon) concat b* 
	left.concat(right);
	cout << left << endl; // . | 'a' 1(epsilon) * 'b'  ==> op = .,left = (| 'a' 1(epsilon)),right = (* b)
	//FA fa6(left);
	FA fa6 = Thompson(left);  // 等效
	cout << "fa6:" << fa6 << endl;
	/**
	Q = [0,10), S = {0}, F = {1}
	Transitions = 4->{ 'a'->5 }, 8->{ 'b'->9 }
	E =	0->{ 4 6 },2->{ 3 },3->{ 1 8 },5->{ 2 }, 6->{ 7 }, 7->{ 2 }, 9->{ 1 8 }
	**/
    ///////////////////////////////////////////////////

	system("pause");
	return 0;
}

/****************************************************************
	Thompson's construction[Wat93a, Construction 4.5] test:
	Reg<RE> re1;
	//FA fa1(re1);
	FA fa1 = Thompson(re1);  // 等效
****************************************************************/
int main3()
{
	/////////////// no-basis operator(epsilon,empty,symbol): this ==> left = right = 0
	// RE = epsilon
	Reg<RE> re1;
	re1.epsilon();
	cout << re1 << endl; // 1  ==> op = EPSILON, left = right = 0
	
	FA fa1 = Thompson(re1); // fa1 = FA(re1)
	cout << "fa1:" << fa1 << endl;
	/**
	FA
	Q = [0,2), S = {0}, F = {1}
	Transitions = 0->{}  1->{}
	E =	0->{ 1 }  1->{}
	current = {}
	**/

	system("pause");
	return 0;
}

int main4()
{
	StateSet st1;
	// set How many States can this set contain.
	// [O, domain()) can be contained in *this.
	// 分配了容纳5个状态的StateSet
	st1.set_domain(5); // State index = 0,1，..., 4
	cout << "domain = " << st1.domain() << endl; // 5
	cout << "empty = " << st1.empty() << endl; // 0
	// inserts a State.
	st1.add(2);
	st1.add(4);
	// 状态数
	cout << "number of states: " << st1.size() << endl;  // 2
	// 是否含有状态 r = [0,domain())
	cout << "st1 含状态2: ? " << st1.contains(2) << endl;  // 1
	cout << "st1 含状态1: ？" << st1.contains(1) << endl;  // 0
	cout << "最小状态index[0,domain()): " << st1.smallest() << endl; // 2
	cout << "st1 states: " << st1 << endl;  // {2,4}
	StateSet old_st1 = st1;
	// st1被修改为它的补集
	cout << "st1 complement: " << st1.complement() << endl; // {0,1,3}
	cout << st1 << endl;  // {0,1,3}
	cout << old_st1 << endl; // {2,4}

	StateSet st2;
	st2.set_domain(5);
	st2.add(1);
	old_st1.set_union(st2);
	cout << old_st1 << endl;  // {2,4} union {1} ==> {1,2,4}

	cout << "==========\n";
	st1.clear();
	st2.clear();
	st1.set_domain(5);
	st2.set_domain(5);
	st1.add(2);
	st1.add(4);
	st2.add(1);
	st2.add(3);
	st1.disjointing_union(st2);
	cout << st1 << endl;
	cout << st1.domain() << endl;

	system("pause");
	return 0;
}

int main()
{
	StateSet st1,st2;
	
	st1.set_domain(5);
	st2.set_domain(5);
	st1.add(2);
	st1.add(4);
	st2.add(1);
	st2.add(3);
	cout << st1 << endl;
	cout << st2 << endl;
	st1.disjointing_union(st2);
	cout << st1 << endl;
	cout << st1.domain() << endl;

	system("pause");
	return 0;
}

