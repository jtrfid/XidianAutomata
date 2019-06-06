#include <iostream>
#include "Sigma.h"
#include "FA.h"
#include "Constrs.h"
#include "FiniteAutomata.h"
using namespace std;

/*******************************************************************
	// 构造RE(Regular Expression)
	Reg<RE> re1;
	//Reg<RE> re1 = Reg<RE>(); // 等效， 在Sigma.h中定义Reg(const RE& r),sigma-operator在Sig-RE.cpp中定义

    ///////////////////////// Thompson's construction: 由RE(Regular Expression)构造FA
	// Thompson's top-down construction [Wat93a, Construction 4.5]. 更有效
	// This constructor can be more efficient than using the Σ-algebra Reg<FA>.

	// Thompson's Construction 4.5 (Top-down Thompson's)
	FA fa1(re1);
	//FA fa1 = FA(re1);   // 等效，在FA.cpp中定义，递归函数：td(const State s, const RE& e, const State f);
	//FA fa1 = Thompson(re1);  // 等效,在Constrs.h中封装，FA Thompson(const RE& r)

	// Thompson's Construction 4.3 (Top-down sigma-algebra Thompson)
	Reg<FA> fa1(re1);
	//FA fa1 = Reg<FA>(re1);   // 等效，在Sigma.h中定义Reg(const RE& r),sigma-operator在Sig-FA.cpp中定义
	//FA fa1 = Thompson_sigma(re1);  // 等效，,在Constrs.h中封装，FA Thompson_sigma(const RE& r)
 *******************************************************************/
class ThompsonTestClass
{
public:
	/****************************************************************
	 Reg<RE> thest:
	 non-basis operator(epsilon,empty,symbol): this ==> left = right = 0
	 unary operator(star,plus,question): this ==> left = this, right = 0
	 binary operator(union(or),concat(dot)): this ==> left(this) operator right
	 ****************************************************************/
	void Reg_RE_Test()
	{
		cout << "=====Reg_RE_Test=====\n";
		/////////////// non-basis operator(epsilon,empty,symbol): this ==> left = right = 0
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
		cout << "\n" << endl;

		/////////////// binary operator(union(or),concat(dot)): this ==> left(this) operator right
		//// RE =  a | epsilon
		Reg<RE> left, right;
		left.symbol('a');
		right.epsilon();
		left.Or(right);
		cout << left << endl;  // | 'a' 1(epsilon) ==> op = Or, left = a, right = EPSILON
		cout <<"\n" << endl;
		//// RE =  a concat epsilon
		left.symbol('a');
		right.epsilon();
		left.concat(right);
		cout << left << endl;  // . 'a' 1(epsilon) ==> op = CONCAT, left = a, right = EPSILON
		cout << "以上为八个基础运算符的RE输出\n" << endl;
		////////////////////////////// 综合应用
		// RE = (a | epsilon)b* 

		//// RE =  a | epsilon
		left.symbol('a');
		right.epsilon();
		left.Or(right);	
		// b *
		right.symbol('b');
		right.star();
		// (a | epsilon) concat b* 
		left.concat(right);
		cout << left << "————这是(a | epsilon) concat b* \n" << endl; // . | 'a' 1(epsilon) * 'b'  ==> op = .,left = (| 'a' 1(epsilon)),right = (* b)
		
		//(01)新增测试样例：蒋宗礼版自动机教材p127页习题4中挑选最具代表性的表达式进行改造使其更复杂
		//得：r+(sr?t|r|1)*——1就是epsilon
		//按照自顶向下方法对表达式进行拆分然后构造每步运算
		/*cout << "\n\n——新增测试样例\n" << endl;
		Reg<RE> left0, right0, left1, right1;//避免与上面代码混乱采取新的变量名尾缀
		left0.symbol('s');
		right0.symbol('r');
		right0.question();
		left0.concat(right0);
		right0.symbol('t');
		left0.concat(right0);//构成括号里的srt
		cout << left0 << "    这是sr?t \n" << endl;
		right0.symbol('r');
		right0.Or(right1.epsilon());//构成括号里的r|1
		cout << right0 << "    这是r|1 \n" << endl;
		left0.Or(right0);
		cout << left0 << "    这是sr?t+r|1 \n" << endl;
		left1.symbol('r');
		left1.plus();
		left0.star();
		left1.concat(left0);
		cout << left1 << "    这是最后结果r+(sr?t|r|1)* \n" << endl;//最后结果
		*/
	}

	/****************************************************************
	   Thompson's construction[Wat93a, Construction 4.5] td(const State s, const RE& e, const State f);
	   Reg<RE> re1;                           注意：const，即初始和终止状态以及正则表达式RE都是const；
	   //FA fa1(re1);
	   //FA fa1 = FA(re1);   // 等效
	   FA fa1 = Thompson(re1);  // 等效
	 ****************************************************************/
	void ThompsonTest1()
	{
		cout << "=====ThompsonTest1\n";
		/////////////// non-basis operator(epsilon,empty,symbol): this ==> left = right = 0
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
		cout << re3 << endl;  // a  ==> op = SYMBOL, left = right = 0 
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

		cout << "以上为测试基础构造FA功能部分\n"<< endl;
		cout << "以下为样例测试,输出格式为：RE+RE构造的FA+FA对应转换的DFA\n" << endl;
		cout << left << " ————测试fa6对应的RE=(a | epsilon) concat b* \n" << endl; // . | 'a' 1(epsilon) * 'b'  ==> op = .,left = (| 'a' 1(epsilon)),right = (* b)
		//FA fa6(left);
		FA fa6 = Thompson(left);  // 等效
		cout << "fa6:" << fa6 << endl;
		DFA ThompsonTest1_dfa1 = fa6.determinism();
		cout << "————ThompsonTest1_dfa1:" << ThompsonTest1_dfa1 << endl;//——————————————————————成功转换成DFA
		FiniteAutomata ffa1;
		ffa1.perform(ThompsonTest1_dfa1, "ThompsonTest1_dfa1.ADS");
		/**文档p22
		Q = [0,10), S ={0}, F = {1}
		Transitions = 4->{ 'a'->5 }, 8->{ 'b'->9 }
		E =	0->{ 4 6 },2->{ 3 },3->{ 1 8 },5->{ 2 }, 6->{ 7 }, 
		7->{ 2 }, 9->{ 1 8 }
		**/
		//(02)新增测试样例：R1R2*R3|R4
	    /*
		left.symbol('a');
		right.symbol('b');
		right.star();
		left.concat(right);
		right.symbol('c');
		left.concat(right);
		right.symbol('d');
		left.Or(right);
		cout << left << "    ab*c|d\n" << endl;
		FA fa7 = Thompson(left);
		cout << "fa7:" << fa7 << endl;
		*/
		/**
		Q = [0,12), S = {0}, F = {1}
		Transitions = 2->{ 'a'->6 }, 5->{ 'c'->3 },8->{ 'b'->9 }, 10->{ 'd'->11 }
		E =	0->{ 2 10 },3->{ 1 },4->{ 5 },6->{ 7 }, 7->{ 4 8 }, 9->{ 4 8 }, 11->{ 1 }
		**/

		//  RE =  (a ∪ b) ab
		//left.Or(right).concat(right.symbol('a')).concat(right.symbol('b')); // result error
		left.symbol('a');
		left.Or(right.symbol('b'));
		//cout << left << endl;  // | 'a' 'b'
		left.concat(right.symbol('a'));
		//cout << left << endl;  // . | 'a' 'b' 'a'
		left.concat(right.symbol('b'));
		cout << left << " ————测试fa7对应的RE=(a ∪ b) ab\n" << endl;
		FA fa7 = Thompson(left);
		cout << "fa7:" << fa7 << endl;
		cout << "\nThompson1\n" <<endl;
		DFA ThompsonTest1_dfa2 = fa7.determinism();
        cout << "————ThompsonTest1_dfa2:" << ThompsonTest1_dfa2 << endl;//————成功转换成DFA
		/**
		Q = [0,10), S = {0}, F = {1}
		Transitions = 3->{ 'b'->1 }, 5->{ 'a'->2 },6->{ 'a'->7 }, 8->{ 'b'->9 }
		E =	0->{ 6 8 },2->{ 3 },4->{ 5 },7->{ 4 }, 9->{ 4 }
		**/
		FiniteAutomata ffa2;
		ffa2.perform(ThompsonTest1_dfa2, "ThompsonTest1_dfa2.ADS");

		//  RE =  (* (a ∪ b)) ab
		left.symbol('a');
		left.Or(right.symbol('b'));
		left.star();
		//cout << left << endl;  // * | 'a' 'b'
		left.concat(right.symbol('a'));
		//cout << left << endl;  // . * | 'a' 'b' 'a'
		left.concat(right.symbol('b'));
		cout << left << " ————fa8对应的RE= ((a ∪ b)*) ab\n" << endl;  // . . * | 'a' 'b' 'a' 'b'
		FA fa8 = Thompson(left);
		cout << "fa8:" << fa8 << endl;
		DFA ThompsonTest1_dfa3 = fa8.determinism();
		cout << "————ThompsonTest1_dfa3:" << ThompsonTest1_dfa3 << endl;//——————————————————————成功转换成DFA
		/**
		Q = [0,12), S = {0}, F = {1}
		Transitions = 3->{ 'b'->1 }, 5->{ 'a'->2 },8->{ 'a'->9 }, 10->{ 'b'->11 }
		E =	0->{ 4 6 },2->{ 3 },4->{ 5 },6->{ 8 10 },7->{ 4 6 },9->{ 7 },11->{ 7 }
		**/
		FiniteAutomata ffa3;
		ffa3.perform(ThompsonTest1_dfa3, "ThompsonTest1_dfa3.ADS");

		//测试：新增正则表达式例子（书本p119）：(a|b)*a|(aa)*
		left.symbol('a');
		right.symbol('b');
		left.Or(right);
		left.star();
		right.symbol('a');
		left.concat(right);
		right.symbol('a');
		right.concat(right);
		right.star();
		left.Or(right);
		cout << left << " ————fa9对应的RE= (a|b)*a|(aa)*\n" << endl;
		FA fa9 = Thompson(left);
		cout << "测试fa9:" << fa9 << endl;//输出结果  | . * | 'a' 'b' 'a' * . 'a' 'a'
		DFA ThompsonTest1_dfa4 = fa9.determinism();
		cout << "————ThompsonTest1_dfa4:" << ThompsonTest1_dfa4 << endl;//——————————————————————成功转换成DFA
		/**画出状态转移图可得对应的RE=(a+b)*a+(aa)*
		Q = [0,18), S = {0}, F = {1}
		Transitions = 0->{},1->{},2->{},3->{},4->{},5->{ 'a'->3 },6->{},7->{},8->{ 'a'->9 },9->{},10->{ 'b'->11 },
		              11->{},12->{},13->{},14->{ 'a'->16 },15->{},16->{},17->{ 'a'->15 }
		E =	0->{ 2 12 },1->{},2->{ 4  6 },3->{ 1 },1->{},6->{ 7 }, 7->{ 4 8 }, 9->{ 4 8 }, 11->{ 1 }
		**/
		FiniteAutomata ffa4;
		ffa4.perform(ThompsonTest1_dfa4, "ThompsonTest1_dfa4.ADS");


		//测试：新增正则表达式例子（自己设计的包含所有零元、一元、二元运算符的多字母表达式）：
		//	RE=((a | epsilon)+)b?cd*|(empty())
		left.symbol('a');
		right.epsilon();
		left.Or(right);
		left.plus();
		right.symbol('b');
		right.question();
		left.concat(right);
		right.symbol('c');
		left.concat(right);
		right.symbol('d');
		right.star();
		left.concat(right);
		right.empty();
		left.Or(right);
		cout << left << " ————fa10对应的RE=((a | epsilon)+)b?cd*|(empty())\n" << endl;
		FA fa10 = Thompson(left);
		cout << "测试fa10:" << fa10 << endl;//输出结果  | . . . + | 'a' 1 ? 'a' 'c' * 'd' 0
		DFA ThompsonTest1_dfa5 = fa10.determinism();
		cout << "————ThompsonTest1_dfa5:" << ThompsonTest1_dfa5 << endl;//——————————————————————成功转换成DFA
		/**画出状态转移图可得对应的RE=((a | epsilon)+)b?cd*|(empty())
		Q = [0,22), S = {0}, F = {1}
		Transitions = 0->{},1->{},2->{},3->{},4->{},5->{},6->{},7->{ 'c'->4 },8->{},9->{},10->{},
					  11->{},12->{ 'a'->13 },13->{},14->{},15->{},16->{ 'b'->17 },17->{},18->{ 'd'->19 },
					  19->{},20->{},21->{}
		E =	0->{ 2 20 },1->{},2->{ 10 },3->{ 1 },4->{ 5 },5->{ 3 18 },6->{ 7 },7->{},8->{ 9 },9->{ 6 16 },
			10->{ 12 14 },11->{ 8 10 },12->{},13->{ 11 },14->{ 15 },15->{ 11 },16->{},17->{ 6 },18->{},
			19->{ 3 18 },20->{},21->{ 1 }
		**/
		///////////////////////////////////////////////////
		FiniteAutomata ffa5;
		ffa5.perform(ThompsonTest1_dfa5, "ThompsonTest1_dfa5.ADS");
	}

	/****************************************************************
	   Thompson's construction[Wat93a, Construction 4.5] td(const State s, const RE& e, const State f);
	   Reg<RE> re1;
	   FA fa1(re1);
	   //FA fa1 = FA(re1);   // 等效
	   //FA fa1 = Thompson(re1);  // 等效
	 ****************************************************************/
	
	void Thompson_sigmaTest1()
	{
		cout << "=====Thompson_sigmaTest1\n";
		/////////////// non-basis operator(epsilon,empty,symbol): this ==> left = right = 0
		// RE = epsilon
		Reg<RE> re1;
		//Reg<RE> re1 = Reg<RE>(); // 等效
		re1.epsilon();
		cout << re1 << endl; // 1  ==> op = EPSILON, left = right = 0
		cout << "\n——————测试点（等效与否）\n" << endl;
		Reg<FA> fa1(re1);//用Reg<FA>或FA得出的结果相同
		FA fb1 = Reg<FA>(re1);   // 等效+用Reg<FA>或FA得出的结果相同
		FA fc1 = Thompson_sigma(re1);  // 等效
		cout << "\nfa1:" << fa1 << endl;
		cout << "\nfb1:" << fb1 << endl;
		cout << "\nfc1:" << fc1 << endl;
		
		/**
		FA
		Q = [0,2), S = {0}, F = {1}
		Transitions = 0->{}  1->{}
		E =	0->{ 1 }  1->{}
		current = {}
		fa1\fb1\fc1输出结果相同说明其等效
		**/

		// RE = empty
		Reg<RE> re2;
		re2.empty();
		cout << re2 << endl;  // 0  ==> op = EMPTY, left = right = 0
		FA fa2 = Thompson_sigma(re2);  
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
		//Reg<FA> fa3(re3);   // 等效
		//FA fa3 = Reg<FA>(re3);   // 等效
		FA fa3 = Thompson_sigma(re3);  
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
		
		FA fa48(re4);
		cout << "\n__________fa48:" << fa48 << endl;
		
		
		
		FA fa4 = Thompson_sigma(re4);  // 与fa46等效——————用老师软件画出最简图再换一下
		cout << "__________fa4:" << fa4 << endl;
		Reg<FA> fa46(re4);
		cout << "__________fa46:\n" << fa46 << endl;
		/**fa48的输出结果如下，与前面ThompsonTest里fa4部分的输出一样，与fa4和fa46不同
	    FA
	    Q = [0,4), S = {0}, F = {1}
	    Transitions = 0->{}  1->{} 2->{ 'b'->3 }  3->{}
	    E =	0->{ 1 2 },1->{},2->{},3->{ 1 2 }
	    current = {}
	    **/
		/**对于fa4与fa46输出结果都是一样的，说明这两个语句是等效的
		FA
		Q = [0,4), S = {2}, F = {3}
		Transitions = 0->{ 'b'->1 } 
		E =	1->{ 0 3 },2->{ 0 3 }
		current = {}
		同时由画图可得虽然表面上输出结果不同，但实际上两幅图是等价的，都是表示b*
		**/

		/////// RE = b +
		Reg<RE> re41;
		re41.symbol('b');
		re41.plus();
		cout << re41 << endl;  // + 'b' ==> op = PLUS, left = b, right = 0
		FA fa41 = Thompson_sigma(re41);  
		cout << "fa41:" << fa41 << endl;
		/**
		FA
		Q = [0,4), S = {2}, F = {3}
		Transitions =  0->{ 'b'->1 } 
		E =	1->{ 0 3 },2->{ 0 }
		current = {}
		**/

		/////// RE = b ?
		Reg<RE> re42;
		re42.symbol('b');
		re42.question();
		cout << re42 << endl;  // ? 'b'  ==> op = QUESTION, left = b, right = 0
		FA fa42 = Thompson_sigma(re42);  // 等效
		cout << "fa42:" << fa42 << endl;
		/**
		FA
		Q = [0,4), S = {2}, F = {3}
		Transitions = 0->{ 'b'->1 } 
		E =	1->{ 3 },2->{ 0 3 }
		current = {}
		**/

		/////////////// binary operator(union(or),concat): this ==> left(this) operator right
		//// RE =  a | epsilon
		Reg<RE> left, right;
		left.symbol('a');
		right.epsilon();
		left.Or(right);
		cout << left << endl;  // | 'a' 1(epsilon) ==> op = Or, left = a, right = EPSILON
		FA fa43 = Thompson_sigma(left);  
		cout << "fa43:" << fa43 << endl;
		/**
		Q = [0,6), S = {4}, F = {5}
		Transitions = 0->{ 'a'->1 }
		E =	1->{ 5 },2->{ 3 },3->{ 5 },4->{ 0 2 }
		**/

		//// RE =  a concat epsilon
		left.symbol('a');
		right.epsilon();
		left.concat(right);
		cout << left << endl;  // . 'a' 1(epsilon) ==> op = CONCAT, left = a, right = EPSILON
		FA fa44 = Thompson_sigma(left);
		cout << "fa44:" << fa44 << endl;
		/**
		Q = [0,4), S = {0}, F = {3}
		Transitions = 0->{ 'a'->1 }
		E =	0->{ },1->{ 2 },2->{ 3 }
		**/

		////////////////////////////// 综合应用
		// RE = (a | epsilon)b* 

		//// RE =  a | epsilon
		left.symbol('a');
		right.epsilon();
		left.Or(right);
		cout << left << endl;  // | 'a' 1(epsilon)
		FA fa5 = Thompson_sigma(left);
		cout << "fa5:" << fa5 << endl;
		
		/**
		Q = [0,6), S = {4}, F = {5}
		Transitions = 0->{ 'a'->1 }
		E =	1->{ 5 },2->{ 3 },3->{ 5 },4->{ 0 2 }
		**/

		// b *
		right.symbol('b');
		right.star();
		cout << right << endl; // * 'b'
		cout << "以上为测试基础构造FA功能部分\n" << endl;
		cout << "以下为样例测试,输出格式为：RE+RE构造的FA+FA对应转换的DFA\n" << endl;
		// (a | epsilon) concat b* 
		left.concat(right);
		cout << left << "————测试fa6对应的RE=(a | epsilon) concat b* \n" << endl; // . | 'a' 1(epsilon) * 'b'  ==> op = .,left = (| 'a' 1(epsilon)),right = (* b)
		FA fa6 = Thompson_sigma(left);
		cout << "fa6:" << fa6 << endl;
		DFA Thompson_sigmaTest1_dfa1 = fa6.determinism();
		cout << "———Thompson_sigmaTest1_dfa1:" << Thompson_sigmaTest1_dfa1 << endl;//——————————————————————成功转换成DFA
		/**
		Q = [0,10), S = {4}, F = {9}
		Transitions = 0->{ 'a'->1 }, 6->{ 'b'->7 }
		E =	1->{ 5 },2->{ 3 },3->{ 5 },4->{ 0 2 }, 5->{ 8 }, 7->{ 6 9 }, 8->{ 6 9 }
		**/
		FiniteAutomata ffa1;
		ffa1.perform(Thompson_sigmaTest1_dfa1, "Thompson_sigmaTest1_dfa1.ADS");

		//  RE =  (a ∪ b) ab
        //left.Or(right).concat(right.symbol('a')).concat(right.symbol('b')); // result error
		left.symbol('a');
		left.Or(right.symbol('b'));
		//cout << left << endl;  // | 'a' 'b'
		left.concat(right.symbol('a'));
		//cout << left << endl;  // . | 'a' 'b' 'a'
		left.concat(right.symbol('b'));
		cout << left << "————测试fa7对应的RE=(a ∪ b) ab\n" << endl;
		FA fa7 = Thompson_sigma(left);
		cout << "fa7:" << fa7 << endl;
		DFA Thompson_sigmaTest1_dfa2 = fa7.determinism();
		cout << "————Thompson_sigmaTest1_dfa2:" << Thompson_sigmaTest1_dfa2 << endl;//——————————————————————成功转换成DFA
		/**
		Q = [0,10), S = {4}, F = {9}
		Transitions = 0->{ 'a'->1 }, 2->{ 'b'->3 },6->{ 'a'->7 }, 8->{ 'b'->9 }
		E =	1->{ 5 },3->{ 5 },4->{ 0 2 },5->{ 6 }, 7->{ 8 }
		**/
		FiniteAutomata ffa2;
		ffa2.perform(Thompson_sigmaTest1_dfa2, "Thompson_sigmaTest1_dfa2.ADS");

		//  RE =  (* (a ∪ b)) ab
		left.symbol('a');
		left.Or(right.symbol('b'));
		left.star();
		//cout << left << endl;  // * | 'a' 'b'
		left.concat(right.symbol('a'));
		//cout << left << endl;  // . * | 'a' 'b' 'a'
		left.concat(right.symbol('b'));
		cout << left << "————测试fa8对应的RE=((a ∪ b)* ) ab\n" << endl;  // . . * | 'a' 'b' 'a' 'b'
		FA fa8 = Thompson_sigma(left);
		cout << "fa8:" << fa8 << endl;
		DFA Thompson_sigmaTest1_dfa3 = fa8.determinism();
		cout << "————Thompson_sigmaTest1_dfa3:" << Thompson_sigmaTest1_dfa3 << endl;//——————————————————————成功转换成DFA
		/**
		Q = [0,12), S = {6}, F = {11}
		Transitions = 0->{ 'a'->1 }, 2->{ 'b'->3 },8->{ 'a'->9 }, 10->{ 'b'->11 }
		E =	1->{ 5 },3->{ 5 },4->{ 0 2 },5->{ 4 7 }, 6->{ 4 7 }, 7->{ 8 }, 9->{ 10 }
		**/  
		FiniteAutomata ffa3;
		ffa3.perform(Thompson_sigmaTest1_dfa3, "Thompson_sigmaTest1_dfa3.ADS");


		left.symbol('a');
		right.symbol('b');
		left.Or(right);
		left.star();
		right.symbol('a');
		left.concat(right);
		right.symbol('a');
		right.concat(right);
		right.star();
		left.Or(right);
		cout << left << "————测试fa9对应的RE=(a+b)*a+(aa)*\n" << endl;
		FA fa9 = Thompson_sigma(left);
		cout << "fa9:" << fa9 << endl;//输出结果  | . * | 'a' 'b' 'a' * . 'a' 'a'
		DFA Thompson_sigmaTest1_dfa4 = fa9.determinism();
		cout << "————Thompson_sigmaTest1_dfa4:" << Thompson_sigmaTest1_dfa4 << endl;//——————————————————————成功转换成DFA
		/**画出状态转移图可得对应的RE=(a+b)*a+(aa)*
		Q = [0,18), S = {16}, F = {17}
		Transitions = 0->{ 'a'->1 },1->{},2->{ 'b'->3 },3->{},4->{},5->{},6->{},7->{},8->{ 'a'->9 },9->{},10->{ 'a'->11 },
					  11->{},12->{ 'a'->13 },13->{},14->{},15->{},16->{},17->{}
		E =	0->{},1->{ 5 },2->{},3->{ 5 },4->{ 0 2 },5->{ 4 7 },6->{ 4 7 },7->{ 8 },8->{},9->{ 17 },10->{},
		11->{ 12 },12->{},13->{ 10 15 },14->{ 10 15 },15->{ 17 }, 16->{ 6 14 },17->{}
		**/
		FiniteAutomata ffa4;
		ffa4.perform(Thompson_sigmaTest1_dfa4, "Thompson_sigmaTest1_dfa4.ADS");


		left.symbol('a');
		right.epsilon();
		left.Or(right);
		left.plus();
		right.symbol('b');
		right.question();
		left.concat(right);
		right.symbol('c');
		left.concat(right);
		right.symbol('d');
		right.star();
		left.concat(right);
		right.empty();
		left.Or(right);
		cout << left << "————测试fa10对应的RE=((a | epsilon)+)b?cd*|(empty())\n" << endl;
		FA fa10 = Thompson_sigma(left);
		cout << "fa10:" << fa10 << endl;//输出结果  | . . . + | 'a' 1 ? 'a' 'c' * 'd' 0
		DFA Thompson_sigmaTest1_dfa5 = fa10.determinism();
		cout << "————Thompson_sigmaTest1_dfa5:" << Thompson_sigmaTest1_dfa5 << endl;//——————————————————————成功转换成DFA
		/**画出状态转移图可得对应的RE=((a | epsilon)+)b?cd*|(empty())
		Q = [0,22), S = {20}, F = {21}
		Transitions = 0->{ 'a'->1 },1->{},2->{},3->{},4->{},5->{},6->{},7->{},8->{ 'b'->9 },9->{},10->{},
					  11->{},12->{ 'c'->13 },13->{},14->{ 'd'->15 },15->{},16->{},17->{},18->{},
					  19->{},20->{},21->{}
		E =	0->{},1->{ 5 },2->{ 3 },3->{ 5 },4->{ 0 2 },5->{ 4 7 },6->{ 4 },7->{ 10 },8->{},9->{ 11 },
			10->{ 8 11 },11->{ 12 },12->{},13->{ 16 },14->{},15->{ 14 17 },16->{ 14 17 },17->{ 21 },18->{},
			19->{ 21 },20->{ 6 18 },21->{}
		**/
		FiniteAutomata ffa5;
		ffa5.perform(Thompson_sigmaTest1_dfa5, "Thompson_sigmaTest1_dfa5.ADS");
		///////////////////////////////////////////////////
	}

   /****************************************************************
	 Thompson's construction[Wat93a, Construction 4.3]
	 Construction 4.3 (Thompson): Thompson's construction is the (unique) homomorphism Th(The operators (with subscript Th, for Thompson))
	 from RE to Thompson's Sigma-algebra of FA's.
	 C(epsilon,Th),C(empty,Th),C(a,Th),C(.,Th([M0],[M1])),C(union,Th([M0],[M1])),C(star,Th([M])),C(star,Th([M])),C(plus,Th([M])),C(question,Th([M]))
		Reg<FA> fa3(re3);   // 等效
		//FA fa3 = Reg<FA>(re3);   // 等效
		//FA fa3 = Thompson_sigma(re3);
	****************************************************************/
	
};

void ThompsonTest()
{
	cout << "=====ThompsonTest测试11111=====\n";
	ThompsonTestClass test;//下述测试中只有ThompsonTest1和Thompson_sigmaTest1是用来样例测试的，Reg_RE_Test()用来测试RE构造是否正确；
	//test.Reg_RE_Test();
	test.ThompsonTest1();
	test.Thompson_sigmaTest1();

}


