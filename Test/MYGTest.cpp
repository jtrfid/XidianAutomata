#include <iostream>
#include "../Automata/Sigma.h"
#include "../Automata/FA.h"
#include "../Automata/Constrs.h"
#include "../Automata/LBFA.h"

using namespace std;
/**
// Construction 4.39 (variation of McNaughton-Yamada-Glushkov)
inline DFA MYG_shortcut(const RE& r)
{
	return(RFA(r).determinism2());
}
// DFA from LBFA construction:
// Construction 4.39
inline DFA MYG(const RE& r)
{
	return(BerrySethi(r).determinism());
}
**/

void minTest(DFA dfa2);


using namespace std;
class MYGTestClass
{
public:
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
		cout << "\n" << endl;
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
	void reExample315(RE& re)
	{
		//cout << "=====reExample315=====\n";
		Reg<RE> left, right;
		///// RE = (a | epsilon)b* 

		// RE =  a | epsilon
		left.symbol('a');
		right.epsilon();
		left.Or(right);
		//cout << left << endl;  // | 'a' 1(epsilon)

		// b *
		right.symbol('b');
		right.star();
		cout << right << endl; // * 'b'

		// (a | epsilon) concat b* 
		left.concat(right);
		//cout << left<<"    输出应该是(a | epsilon) concat b*\n " << endl; // . | 'a' 1(epsilon) * 'b'  ==> op = .,left = (| 'a' 1(epsilon)),right = (* b)
		re = left;
	}

	//  RE =  (a ∪ b)ab
	void reExample2_9noStar(RE& re)
	{
		//cout << "=====reExample2_9noStar=====\n";
		Reg<RE> left, right;
		cout << "\n————————测试点11111\n" << endl;
		//  RE =  (a ∪ b) ab
		//left.Or(right).concat(right.symbol('a')).concat(right.symbol('b')); // result error
		left.symbol('a');
		left.Or(right.symbol('b'));
		//cout << left << endl;  // | 'a' 'b'

		left.concat(right.symbol('a'));
		//cout << left << endl;  // . | 'a' 'b' 'a'
		left.concat(right.symbol('b'));
		cout << left << endl;  // . . | 'a' 'b' 'a' 'b'

		re = left;
	}

	//  RE =  (* (a ∪ b)) ab

	void reExample2_9Star(RE& re)
	{
		//cout << "=====reExample2_9Star=====\n";
		Reg<RE> left, right;

		//  RE =  (* (a ∪ b)) ab
		left.symbol('a');
		left.Or(right.symbol('b'));
		left.star();
		//cout << left << endl;  // * | 'a' 'b'

		left.concat(right.symbol('a'));
		//cout << left << endl;  // . * | 'a' 'b' 'a'
		left.concat(right.symbol('b'));
		cout << left << endl;  // . . * | 'a' 'b' 'a' 'b'

		re = left;

	}
	void ex4(RE& re)  //RE = (a + b)*a + (aa)*
	{
		//cout << "=====ex4=====\n";
		Reg<RE> left, right;
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
		cout << left << "    (a+b)*a+(aa)*\n" << endl;
		re = left;

	}
	void ex5(RE& re)  //RE=((a | epsilon)+)b?cd*|(empty())
	{
		//cout << "=====ex5=====\n";
		Reg<RE> left, right;
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
		cout << left << "    ((a | epsilon)+)b?cd*|(empty())\n" << endl;
		re = left;

	}
	//  RE =  ((a ∪ b*)) ab（为了研究与RE =  (* (a ∪ b)) ab的区别多设立的一个同等作用的函数）
	/**
	void reExample2extra_9Star(RE& re)
	{
		cout << "\n=====reExample2extra_9Star=====\n";
		Reg<RE> left, right;

		//  RE =  ((a ∪ b*)) ab
		left.symbol('a');
		right.symbol('b');
		right.star();
		left.Or(right);

		//cout << left << endl;  //  | 'a' *'b'

		left.concat(right.symbol('a'));
		//cout << left << endl;  // .  | 'a' *'b' 'a'
		left.concat(right.symbol('b'));
		cout << left << endl;  // . .  | 'a' *'b' 'a' 'b'

		re = left;
	}
	**/




	
	DFA MYG_shortcut(const RE& r)
	{
		//cout << "=====MYG_shortcut=====\n";
		return(RFA(r).determinism2());
	}
	DFA MYG(const RE& r)
	{
		//cout << "=====MYG=====\n";
		return(BerrySethi(r).determinism());
	}

};
void MYGTest1()
{
	cout << "=====MYGTest1=====\n";
	MYGTestClass test;
	LBFA lbfa1;
	RE re;
	test.reExample315(re);
	cout << "样例1，RE=（a|epsilon) concat b*: " << re << endl; // . | 'a' 1(epsilon) * 'b'  ==> op = .,left = (| 'a' 1(epsilon)),right = (* b)


	//lbfa1 = BerrySethi(re);
	//cout << "LBFA1\n" << lbfa1 << endl;
	/**
	 LBFA————由状态转移图可得RE=(a|1)b*——这里只为了验证LBFA正确性，跟实际MYGTest功能没有关联，所以TEST2/3省略此环节
	Q = [0,3) s = 2 F = { 0  1 2 } Qmap_inverse = { 'a'->0  'b'->1 }
	follow = 0->{ 1 } 1->{ 1 } 2->{ 0 1 }
	current = {}
		 **/
	
	DFA dfa1 = test.MYG_shortcut(re);
	DFA dfa2 = test.MYG(re);
	cout << "DFA1__MYG_shortcut\n" << dfa1 << endl;
	cout << "DFA2__MYG\n" << dfa2 << endl;
	/**
	DFA1=DFA2————由状态转移图可得RE=(a|1)b*
	Q = [0,3) S = { 0 } F = { 0  1  2 }
	Transitions = 0->{ 'a'->1  'b'->2 } 1->{ 'b'->2 } 2->{ 'b'->2 }
	current = -1
	两个函数出来的结果是一样的
	**/

	minTest(dfa1);
	minTest(dfa2);

}
void MYGTest2()
{
	cout << "=====MYGTest2=====\n";
	MYGTestClass test;
	RE re;
	test.reExample2_9noStar(re);
	cout << "样例2，RE=（a∪b)ab: " << re << endl; // . . | 'a' 'b' 'a' 'b'

	DFA dfa1 = test.MYG_shortcut(re);
	DFA dfa2 = test.MYG(re);
	cout << "DFA1__MYG_shortcut\n" << dfa1 << endl;
	cout << "DFA2__MYG\n" << dfa2 << endl;
	/**
	DFA1=DFA2————画状态图得RE=（a∪b)ab
	 Q = [0,5) 	S = { 0 } 	F = { 4 }
	 Transitions = 0->{ 'a'->1  'b'->2 }  1->{ 'a'->3 }	2->{ 'a'->3 } 3->{ 'b'->4 }
	 4->{} current = -1
	 两个函数出来的结果是一样的
	 **/
	minTest(dfa1);
	minTest(dfa2);

}
void MYGTest3()
{
	cout << "=====MYGTest3=====\n";
	MYGTestClass test;
	RE re;
	test.reExample2_9Star(re);
	cout << "样例3，RE=(a∪b)*ab: " << re << endl; // . . * | 'a' 'b' 'a' 'b'

	DFA dfa1 = test.MYG_shortcut(re);
	DFA dfa2 = test.MYG(re);
	cout << "DFA1__MYG_shortcut\n" << dfa1 << endl;
	cout << "DFA2__MYG\n" << dfa2 << endl;
	/**
	DFA1=DFA2————由状态转移图得出RE=(a∪b)*ab
	Q = [0,4)  S = { 0 }   F = { 3 }
	Transitions =
	0->{ 'a'->1  'b'->2 }
	1->{ 'a'->1  'b'->3 }
	2->{ 'a'->1  'b'->2 }
	3->{ 'a'->1  'b'->2 }
	current = -1
	两个函数出来的结果是一样的
	 **/
	minTest(dfa1);
	minTest(dfa2);

}
void MYGTest4()
{
	cout << "=====MYGTest4=====\n";
	MYGTestClass test;
	RE re;
	test.ex4(re);
	cout << "样例4，RE=(a+b)*a+(aa)*: " << re << endl; // | . * | 'a' 'b' 'a' * . 'a' 'a'

	DFA dfa1 = test.MYG_shortcut(re);
	DFA dfa2 = test.MYG(re);
	cout << "DFA1__MYG_shortcut\n" << dfa1 << endl;
	cout << "DFA2__MYG\n" << dfa2 << endl;
	/**
	DFA1=DFA2————画状态图得RE=(a+b)*a+(aa)*
	Q = [0,5)  S = { 0 }   F = { 0  1  3  4 }
	Transitions =
	0->{ 'a'->1  'b'->2 }
	1->{ 'a'->3  'b'->2 }
	2->{ 'a'->4  'b'->2 }
	3->{ 'a'->1  'b'->2 }
	4->{ 'a'->4  'b'->2 }
	current = -1
	两个函数出来的结果是一样的
	 **/
	minTest(dfa1);
	minTest(dfa2);
}
void MYGTest5()
{
	cout << "=====MYGTest5=====\n";
	MYGTestClass test;
	RE re;
	test.ex5(re);
	cout << "样例5，RE=((a | epsilon)+)b?cd*|(empty()): " << re << endl; // | . . . + | 'a' 1 ? 'a' 'c' * 'd' 0

	DFA dfa1 = test.MYG_shortcut(re);
	DFA dfa2 = test.MYG(re);
	cout << "DFA1__MYG_shortcut\n" << dfa1 << endl;
	cout << "DFA2__MYG\n" << dfa2 << endl;
	/**
	 DFA1=DFA2————画状态图得RE=((a | epsilon)+)b?cd*|(empty())
	 Q = [0,5) 	S = { 0 } 	F = { 3 4 }
	 Transitions =
	 0->{ 'a'->1  'b'->2  'c'->3 }
	 1->{ 'a'->1  'b'->2  'c'->3 }
	 2->{ 'c'->3 }
	 3->{ 'd'->4 }
	 4->{ 'd'->4 }
	 current = -1
	两个函数出来的结果是一样的
	 **/
	minTest(dfa1);
	minTest(dfa2);
}
void MYGTest()
{
	cout << "=====MYGTest测试=====\n";
	MYGTestClass test; //Reg_RE_Test()用来测试RE构造是否正确；
	//test.Reg_RE_Test();
	MYGTest1();
	MYGTest2();
	MYGTest3();
	MYGTest4();
	MYGTest5();
}