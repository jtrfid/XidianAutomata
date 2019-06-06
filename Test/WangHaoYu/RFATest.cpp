#include <iostream>
#include "Sigma.h"
#include "FA.h"
#include "Constrs.h"
#include "RFA.h"
#include "LBFA.h"
#include "FiniteAutomata.h"
using namespace std;

/*******************************************************************
	Reg<RE> re1;
	//Reg<RE> re1 = Reg<RE>(); // 等效

	Definition 4.30 (Homomorphism from RE to [RFA]): We define rfa in RE ---> [RFA],
	 to be the unique homomorphism from REs to [RFA]
	//RFA rfa1(re);     // 在RFA.h，RFA.cpp定义和实现RFA(const RE& e)
	RFA rfa1 = rfa(re); // 等效，在Constrs.h中封装，RFA rfa(const RE& r)

	Definition 4.29 (Sigma-algebra of RFA's): The carrier set is [RFA], p33-35
	//RFA rfa1 = Reg<RFA>(re); // 在Sigma.h中定义Reg(const RE& r)，sigma-operator在Sig-RFA.cpp中定义
	RFA rfa1 = rfa_sigma(re);  // 等效,在Constrs.h封装，RFA rfa_sigma(const RE& r)
   
 *******************************************************************/
class RFATestClass
{
public:
	/****************************************************************
	 Example 3.15 (A regular expression),P18：(a | epsilon) concat b* ，
	 Reg<RE> thest:
	 non-basis operator(epsilon,empty,symbol): this ==> left = right = 0
	 unary operator(star,plus,question): this ==> left = this, right = 0
	 binary operator(union(or),concat(dot)): this ==> left(this) operator right
	 ****************************************************************/

	 ///// RE = (a | epsilon)b* 
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
		//cout << right << endl; // * 'b'

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
		//cout << "\n————————测试点11111\n" << endl;
		//  RE =  (a ∪ b) ab
		//left.Or(right).concat(right.symbol('a')).concat(right.symbol('b')); // result error
		left.symbol('a');
		left.Or(right.symbol('b'));
		//cout << left << endl;  // | 'a' 'b'
		
		left.concat(right.symbol('a'));
		//cout << left << endl;  // . | 'a' 'b' 'a'
		left.concat(right.symbol('b'));
		//cout << left << endl;  // . . | 'a' 'b' 'a' 'b'

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
		//cout << left << endl;  // . . * | 'a' 'b' 'a' 'b'

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
	/*************************************************************************
	 Definition 4.30 (Homomorphism from RE to [RFA]): We define rfa in RE ---> [RFA], 
	 to be the unique homomorphism from REs to [RFA]
	 //RFA rfa1(re);     // 在RFA.h，RFA.cpp定义和实现RFA(const RE& e)
	 RFA rfa1 = rfa(re); // 等效，在Constrs.h中封装，RFA rfa(const RE& r)
	 *************************************************************************/
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
		//cout << left << "    (a+b)*a+(aa)*\n" << endl;
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
		//cout << left << "    ((a | epsilon)+)b?cd*|(empty())\n" << endl;
		re = left;

	}
	RFA re2RFA_homomorphismTest(const RE& re) // RE --> RFA (Homomorphism from RE to[RFA])
	{
		cout << "=====re2RFA_homomrphismTest=====\n";
		//RFA rfa1(re);     // 在RFA.h，RFA.cpp定义和实现RFA(const RE& e)
		RFA rfa1 = rfa(re); // 等效，在Constrs.h中封装，RFA rfa(const RE& r)
		return rfa1;
	}

	/*************************************************************************
	  Definition 4.29 (Sigma-algebra of RFA's): The carrier set is [RFA], p33-35
	  //RFA rfa1 = Reg<RFA>(re); // 在Sigma.h中定义Reg(const RE& r)，sigma-operator在Sig-RFA.cpp中定义
	  RFA rfa1 = rfa_sigma(re);  // 等效,在Constrs.h封装，RFA rfa_sigma(const RE& r)
	 *************************************************************************/
	RFA rfa_sigmaTest(const RE& re) // RE --> RFA (Sigma-algebra of RFA's)
	{
		cout << "=====rfa_sigmaTest=====\n";
		//RFA rfa1 = Reg<RFA>(re); // 在Sigma.h中定义Reg(const RE& r)，sigma-operator在Sig-RFA.cpp中定义
		RFA rfa1 = rfa_sigma(re);  // 等效,在Constrs.h封装，RFA rfa_sigma(const RE& r)
		return rfa1;
	}

	/***************************************************************************
	  RE --> LBFA:
	  (1) RE --> RFA
	      RFA rfa = RFA(re); // 或sigma代数运算：Reg<RFA>(re)
	  (2) Specially construct from an RFA(see Definition 4.28). RFA --> LBFA
      //LBFA lbfa = LBFA(rfa); // 在LBFA.h,LBFA.cpp定义 LBFA(const RFA& r)

	  // 等效，由LBFA中的LBFA& decode(const RFA& r)函数完成
	  // LBFA lbfa; lbfa = lbfa.decode(rfa);

	  /////// 综合(1),(2)
	  // Construction 4.32 (Berry-Sethi): Construction BS 属于 RE --> LBFA
	  // lbfa(E) = BS(E) = decode o rfa(E)
	  // 等效，在Constrs.h中封装LBFA BerrySethi(const RE& r)
	  // RE -->RFA: rfa = RFA(re); RFA --> LBFA, lbfa = LBFA(rfa) 或 lbfa = lbfa.decode(rfa)
	  LBFA lbfa = BerrySethi(re); 
	 ***************************************************************************/
	LBFA RFA2LBFA(const RE& re) // RFA --> LBFA
	{
		cout << "=====RFA2LBFA=====\n";
		RFA rfa = re2RFA_homomorphismTest(re);
		// RFA rfa = rfa_sigmaTest(re); // 返回同样的rfa

		//LBFA lbfa = LBFA(rfa); // 在LBFA.h,LBFA.cpp定义 LBFA(const RFA& r)

		// 等效，由LBFA中的LBFA& decode(const RFA& r)函数完成
		LBFA lbfa; lbfa = lbfa.decode(rfa);
		//文档里lbfa那个相关内容有讲到decode和encode，直接跳到函数定义声明里也有涉及
		// 等效，在Constrs.h中封装LBFA BerrySethi(const RE& r)
		// RE -->RFA: rfa=RFA(re), RFA --> LBFA, LBFA(rfa)
		//LBFA lbfa = BerrySethi(re); 
		return lbfa;
	}

	// Implement non-homomorphic RFA->LBFA mapping convert(Defn. 4.35).
	// LBFA& LBFA::convert(const RFA& r)
	LBFA RFAconvertLBFA(const RE& re) // RFA --> LBFA (convert,取RFA的first中编号最小的状态为LBFA的单个{start})
	{
		cout << "=====RFAconvertLBFA=====\n";
		RFA rfa = re2RFA_homomorphismTest(re);
		// RFA rfa = rfa_sigmaTest(re); // 返回同样的rfa

		// convert
		LBFA lbfa; lbfa = lbfa.convert(rfa);

		return lbfa;
	}

	// DFA from LBFA construction:
    // Construction 4.39
	DFA DFAfromLBFA(const RE& re) //实际就是RE->RFA->LBFA->DFA
	{
		cout << "=====DFAfromLBFA=====\n";
		DFA dfa = BerrySethi(re).determinism();
		return dfa;
	}

};

void RFATest1()
{
	cout << "=====RFATest1=====\n";
	RFATestClass test;
	RFA rfa1,rfa2;
	LBFA lbfa1,lbfa2;
	RE re;
	test.reExample315(re);
	cout << "样例1，RE=（a|epsilon) concat b*: " << re << endl; // . | 'a' 1(epsilon) * 'b'  ==> op = .,left = (| 'a' 1(epsilon)),right = (* b)
	cout << "以下为各FA类型构造函数名与构造FA结果\n" << endl;
	rfa1 = test.re2RFA_homomorphismTest(re); // RE --> RFA (Homomorphism from RE to[RFA])
	cout << "rfa1\n" << rfa1 << endl;
	/** RFA————由状态转移图可得RE=(a|1)b*___这里的epsilon是指first就是last
		Q = [0,2) first = { 0  1 } last = { 0  1 }
		Qmap_inverse = { 'a'->0  'b'->1 }
		follow = 0->{ 1 } 1->{ 1 }
		Nullable = true 
		final = false
		current = {}
		**/
	rfa2 = test.rfa_sigmaTest(re);  // RE --> RFA (Sigma-algebra of RFA's)
	cout << "rfa2\n" << rfa2 << endl; // 同上
	lbfa1 = test.RFA2LBFA(re); // RFA --> LBFA
	cout << "lbfa1\n" << lbfa1 << endl; 
	/**
	 LBFA1————由状态转移图可得RE=(a|1)b*
	Q = [0,3) s = 2 F = { 0  1  2 } Qmap_inverse = { 'a'->0  'b'->1 }
    follow = 0->{ 1 } 1->{ 1 } 2->{ 0  1 } current = {}
	 **/
	lbfa2 = test.RFAconvertLBFA(re); // RFA --> LBFA (convert)
	cout <<"lbfa2\n"<< lbfa2 << endl;
	/**
	 LBFA2
	Q = [0,2) s = 0 F = { 0  1 } Qmap_inverse = { 'a'->0  'b'->1 }
	follow = 0->{ 1 } 1->{ 1 }
	current = {}
		 **/
	cout << "以下分别为各类型FA对应转换的DFA\n" << endl;
	DFA RFATest1_dfa1 = rfa1.determinism();
	cout << "———RFATest1_dfa1:" << RFATest1_dfa1 << endl;//——————————————————————成功转换成DFA
	DFA RFATest1_dfa2 = rfa2.determinism();
	cout << "———RFATest1_dfa2:" << RFATest1_dfa2 << endl; //——————————————————————成功转换成DFA
	DFA RFATest1_dfa3 = lbfa1.determinism();
	cout << "———RFATest1_dfa3:" << RFATest1_dfa3 << endl;//——————————————————————成功转换成DFA
	DFA RFATest1_dfa4 = lbfa2.determinism();
	cout << "———RFATest1_dfa4:" << RFATest1_dfa4 << endl;//——————————————————————成功转换成DFA
	cout << "以下为lbfa1通过另一种方式对应转换的DFA\n" << endl;
	DFA RFATest1_dfa5 = test.DFAfromLBFA(re);
	cout << RFATest1_dfa5 << endl;
	/**
	DFA————由状态转移图可得RE=(a|1)b*
	Q = [0,3) S = { 0 } F = { 0  1  2 }
	Transitions = 0->{ 'a'->1  'b'->2 } 1->{ 'b'->2 } 2->{ 'b'->2 }
	current = -1
	**/
	//因为1-2DFA是完全一样的，3-4同理，所以只比较1,3,5的DFA，以下同理不再注释
	FiniteAutomata ffa1;
	ffa1.perform(RFATest1_dfa1, "RFATest1_dfa1.ADS");
	FiniteAutomata ffa2;
	ffa2.perform(RFATest1_dfa3, "RFATest1_dfa3.ADS");
	FiniteAutomata ffa3;
	ffa3.perform(RFATest1_dfa5, "RFATest1_dfa5.ADS");
}

void RFATest2()
{
	cout << "=====rRFATest2=====\n";
	RFATestClass test;
	RFA rfa1, rfa2;
	LBFA lbfa1,lbfa2;
	RE re;
	test.reExample2_9noStar(re);
	cout << "样例2，RE=(a∪b)ab: " << re << endl; // . . | 'a' 'b' 'a' 'b'
	cout << "以下为各FA类型构造函数名与构造FA结果\n" << endl;
	
	rfa1 = test.re2RFA_homomorphismTest(re); // RE --> RFA (Homomorphism from RE to[RFA])
	cout << "rfa1\n" << rfa1 << endl;
	/** ————画状态图得RE=(a∪b)ab
	 Q = [0,4) first = { 0  1 } last = { 3 }
     Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'b'->3 }  // 'a'->2 表示T:(0,a,2)和(1,a,b), 每个状态的各个入弧均为同一个字母
	 follow = 0->{ 2 } 1->{ 2 } 2->{ 3 } 3->{}
	 Nullable = false final = false current = {}
	**/
	rfa2 = test.rfa_sigmaTest(re);  // RE --> RFA (Sigma-algebra of RFA's)
	cout << "rfa2\n" << rfa2 << endl; // 同上

	lbfa1 = test.RFA2LBFA(re); // RFA --> LBFA
	cout << "lbfa1\n" << lbfa1 << endl;
	/**
	 LBFA————画状态图得RE=（a∪b)ab
	 Q = [0,5) s = 4 F = { 3 }
	 Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'b'->3 }
	 follow = 0->{ 2 } 1->{ 2 } 2->{ 3 } 3->{} 4->{ 0  1 }
     current = {}
	 **/

	lbfa2 = test.RFAconvertLBFA(re); // RFA --> LBFA (convert)
	cout << "lbfa2\n" << lbfa2 << endl;
	/**
	 LBFA————画状态图得R=aab（本来对应前面的RFA的fist里包含0和1，这里因为是LBFA的原因所以只有一个0（问题
	 Q = [0,4) s = 0  F = { 3 }
     Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'b'->3 }
	 follow = 0->{ 2 } 1->{ 2 } 2->{ 3 } 3->{}
	 current = {}
	 **/
	cout << "以下分别为各类型FA对应转换的DFA\n" << endl;
	DFA RFATest2_dfa1 = rfa1.determinism();
	cout << "———RFATest2_dfa1:" << RFATest2_dfa1 << endl;//——————————————————————成功转换成DFA
	DFA RFATest2_dfa2 = rfa2.determinism();
	cout << "———RFATest2_dfa2:" << RFATest2_dfa2 << endl; //——————————————————————成功转换成DFA
	DFA RFATest2_dfa3 = lbfa1.determinism();
	cout << "———RFATest2_dfa3:" << RFATest2_dfa3 << endl;//——————————————————————成功转换成DFA
	DFA RFATest2_dfa4 = lbfa2.determinism();
	cout << "———RFATest2_dfa4:" << RFATest2_dfa4 << endl;//——————————————————————成功转换成DFA
	cout << "以下为lbfa1通过另一种方式对应转换的DFA\n" << endl;
	DFA RFATest2_dfa5 = test.DFAfromLBFA(re);
	cout << RFATest2_dfa5 << endl;
	/**
	 DFA————画状态图得RE=（a∪b)ab
	 Q = [0,5) 	S = { 0 } 	F = { 4 }
	 Transitions = 0->{ 'a'->1  'b'->2 }  1->{ 'a'->3 }	2->{ 'a'->3 } 3->{ 'b'->4 }
	 4->{} current = -1
	 **/
	FiniteAutomata ffa1;
	ffa1.perform(RFATest2_dfa1, "RFATest2_dfa1.ADS");
	FiniteAutomata ffa2;
	ffa2.perform(RFATest2_dfa3, "RFATest2_dfa3.ADS");
	FiniteAutomata ffa3;
	ffa3.perform(RFATest2_dfa5, "RFATest2_dfa5.ADS");
}

void RFATest3()
{
	cout << "=====RFATest3=====\n";
	RFATestClass test;
	RFA rfa1, rfa2;
	LBFA lbfa1,lbfa2;
	RE re;
	test.reExample2_9Star(re);
	cout << "样例3，RE=((a∪b)*)ab: " << re << endl; // . . * | 'a' 'b' 'a' 'b'
	cout << "以下为各FA类型构造函数名与构造FA结果\n" << endl;
	rfa1 = test.re2RFA_homomorphismTest(re); // RE --> RFA (Homomorphism from RE to[RFA])
	cout << "rfa1\n" << rfa1 << endl;
	/** RFA————由状态转移图可得RE=(a∪b)*ab
	Q = [0,4)  first = { 0  1  2 }
	last = { 3 }  Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'b'->3 }
	follow = 0->{ 0  1  2 }   1->{ 0  1  2 }  2->{ 3 }  3->{}
	Nullable = false
	final = false
	current = {}
	**/
	rfa2 = test.rfa_sigmaTest(re);  // RE --> RFA (Sigma-algebra of RFA's)
	cout << "rfa2\n" << rfa2 << endl; // 同上

	lbfa1 = test.RFA2LBFA(re); // RFA --> LBFA
	cout << "lbfa1\n" << lbfa1 << endl;
	/**
	LBFA————由状态转移图可得RE=(a∪b)*ab————加了新的状态q4作为唯一起始状态使得 少了RFA中只有一个b的情况
	Q = [0,5)  s = 4  F = { 3 }
	Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'b'->3 }
	follow = 0->{ 0  1  2 }   1->{ 0  1  2 }  2->{ 3 }  3->{}   4 ->{ 0 1 2 }
	current = {}
	 **/

	lbfa2 = test.RFAconvertLBFA(re); // RFA --> LBFA (convert)
	cout << "lbfa2\n" << lbfa2 << endl;
	/**
	convert(RFA)  to  LBFA————由状态转移图可得RE=(a∪b)*ab
	Q = [0,4)  s = 0  F = { 3 }
	Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'b'->3 }
	follow = 0->{ 0  1  2 }   1->{ 0  1  2 }  2->{ 3 }  3->{}
	current = {}
	 **/
	cout << "以下分别为各类型FA对应转换的DFA\n" << endl;
	DFA RFATest3_dfa1 = rfa1.determinism();
	cout << "———RFATest3_dfa1:" << RFATest3_dfa1 << endl;//——————————————————————成功转换成DFA
	DFA RFATest3_dfa2 = rfa2.determinism();
	cout << "———RFATest3_dfa2:" << RFATest3_dfa2 << endl; //——————————————————————成功转换成DFA
	DFA RFATest3_dfa3 = lbfa1.determinism();
	cout << "———RFATest3_dfa3:" << RFATest3_dfa3 << endl;//——————————————————————成功转换成DFA
	DFA RFATest3_dfa4 = lbfa2.determinism();
	cout << "———RFATest3_dfa4:" << RFATest3_dfa4 << endl;//——————————————————————成功转换成DFA
	cout << "以下为lbfa1通过另一种方式对应转换的DFA\n" << endl;
	DFA RFATest3_dfa5 = test.DFAfromLBFA(re);
	cout << "\n"<< RFATest3_dfa5 << endl;
	/**
	DFA from LBFA(————由状态转移图得出RE=(a∪b)*ab)
	Q = [0,4)  S = { 0 }   F = { 3 }
	Transitions =
	0->{ 'a'->1  'b'->2 }
	1->{ 'a'->1  'b'->3 }
	2->{ 'a'->1  'b'->2 }
	3->{ 'a'->1  'b'->2 }
	current = -1
	 **/
	/**————错误版本
	DFA from LBFA(————由状态转移图得出RE=(1+b+)a(a+ +b(ab)*)
	Q = [0,5)  S = { 0 }   F = { 3  4 }
	Transitions =
	0->{ 'a'->1  'b'->2 }
	1->{ 'a'->3  'b'->4 }
	2->{ 'a'->1  'b'->2 }
	3->{ 'a'->3  'b'->4 }
	4->{ 'a'->1  'b'->2 }
	current = -1
	 **/
	FiniteAutomata ffa1;
	ffa1.perform(RFATest3_dfa1, "RFATest3_dfa1.ADS");
	FiniteAutomata ffa2;
	ffa2.perform(RFATest3_dfa3, "RFATest3_dfa3.ADS");
	FiniteAutomata ffa3;
	ffa3.perform(RFATest3_dfa5, "RFATest3_dfa5.ADS");
}
void RFATest4()
{
	cout << "=====RFATest4=====\n";
	RFATestClass test;
	RFA rfa1, rfa2;
	LBFA lbfa1,lbfa2;
	RE re;
	test.ex4(re);
	cout << "样例4，RE=(a|b)*a|(aa)*: " << re << endl; // | . * | 'a' 'b' 'a' * . 'a' 'a'
	cout << "以下为各FA类型构造函数名与构造FA结果\n" << endl;
	rfa1 = test.re2RFA_homomorphismTest(re); // RE --> RFA (Homomorphism from RE to[RFA])
	cout << "rfa1\n" << rfa1 << endl;
	/** RFA————由状态转移图可得RE=(a|b)*a|(aa)*
	Q = [0,5)  first = { 0  1  2  3 }
	last = { 2  4 }  Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'a'->3  'a'->4 }
	follow = 0->{ 0  1  2 }   1->{ 0  1  2 }  2->{}  3->{ 4 }  4->{ 3 }
	Nullable = true
	final = false
	current = {}
	**/
	rfa2 = test.rfa_sigmaTest(re);  // RE --> RFA (Sigma-algebra of RFA's)
	cout << "rfa2\n" << rfa2 << endl; // 同上

	lbfa1 = test.RFA2LBFA(re); // RFA --> LBFA
	cout << "lbfa1\n" << lbfa1 << endl;
	/**
	 LBFA1————画状态图得RE=(a+b)*a+(aa)*
	 Q = [0,6) s = 5 F = { 2 4 5 }
	 Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'a'->3  'a'->4 }
	 follow = 0->{ 0 1 2 } 1->{ 0 1 2 } 2->{} 3->{ 4 } 4->{ 3 } 5->{ 0 1 2 3 }
	 current = {}
	 **/

	lbfa2 = test.RFAconvertLBFA(re); // RFA --> LBFA (convert)
	cout << "lbfa2\n" << lbfa2 << endl;
	/**
	 LBFA2————画状态图得RE=(a+b)*a+(aa)*
	 Q = [0,5) s = 0 F = { 2 4 }
	 Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'a'->3  'a'->4 }
	 follow = 0->{ 0 1 2 } 1->{ 0 1 2 } 2->{} 3->{ 4 } 4->{ 3 } 
	 current = {}	 **/
	cout << "以下分别为各类型FA对应转换的DFA\n" << endl;
	DFA RFATest4_dfa1 = rfa1.determinism();
	cout << "———RFATest4_dfa1:" << RFATest4_dfa1 << endl;//——————————————————————成功转换成DFA
	DFA RFATest4_dfa2 = rfa2.determinism();
	cout << "———RFATest4_dfa2:" << RFATest4_dfa2 << endl; //——————————————————————成功转换成DFA
	DFA RFATest4_dfa3 = lbfa1.determinism();
	cout << "———RFATest4_dfa3:" << RFATest4_dfa3 << endl;//——————————————————————成功转换成DFA
	DFA RFATest4_dfa4 = lbfa2.determinism();
	cout << "———RFATest4_dfa4:" << RFATest4_dfa4 << endl;//——————————————————————成功转换成DFA
	cout << "以下为lbfa1通过另一种方式对应转换的DFA\n" << endl;
	DFA RFATest4_dfa5 = test.DFAfromLBFA(re);
	cout << RFATest4_dfa5 << endl;
	/**
	 DFA————画状态图得RE=(a+b)*a+(aa)*
	 Q = [0,5) 	S = { 0 } 	F = { 0 1 3 4 }
	 Transitions =
	 0->{ 'a'->1  'b'->2 }
	 1->{ 'a'->3  'b'->2 }
	 2->{ 'a'->4  'b'->2 }
	 3->{ 'a'->1  'b'->2 }
	 4->{ 'a'->4  'b'->2 }
	 current = -1
	  **/
	FiniteAutomata ffa1;
	ffa1.perform(RFATest4_dfa1, "RFATest4_dfa1.ADS");
	FiniteAutomata ffa2;
	ffa2.perform(RFATest4_dfa3, "RFATest4_dfa3.ADS");
	FiniteAutomata ffa3;
	ffa3.perform(RFATest4_dfa5, "RFATest4_dfa5.ADS");
}
void RFATest5()
{
	cout << "=====RFATest5=====\n";
	RFATestClass test;
	RFA rfa1, rfa2;
	LBFA lbfa1,lbfa2;
	RE re;
	test.ex5(re);
	cout << "样例5，RE=((a | epsilon)+)b?cd*|(empty()): " << re << endl; // | . . . + | 'a' 1 ? 'a' 'c' * 'd' 0
	cout << "以下为各FA类型构造函数名与构造FA结果\n" << endl;
	rfa1 = test.re2RFA_homomorphismTest(re); // RE --> RFA (Homomorphism from RE to[RFA])
	cout << "rfa1\n" << rfa1 << endl;
	/** RFA————由状态转移图可得RE=((a | epsilon)+)b?cd*|(empty())
	Q = [0,4)  first = { 0  1  2 }
	last = { 2  3 }  Qmap_inverse = { 'a'->0  'b'->1  'c'->2  'd'->3  }
	follow = 0->{ 0  1  2 }   1->{ 2 }  2->{ 3 }  3->{ 3 } 
	Nullable = false
	final = false
	current = {}
	**/
	rfa2 = test.rfa_sigmaTest(re);  // RE --> RFA (Sigma-algebra of RFA's)
	cout << "rfa2\n" << rfa2 << endl; // 同上

	lbfa1 = test.RFA2LBFA(re); // RFA --> LBFA
	cout << "lbfa1\n" << lbfa1 << endl;
	/**
	 LBFA1————画状态图得RE=((a | epsilon)+)b?cd*|(empty())
	 Q = [0,5) s = 4 F = { 2 3 }
	 Qmap_inverse = { 'a'->0  'b'->1  'c'->2  'd'->3  }
	 follow = 0->{ 0  1  2 }   1->{ 2 }  2->{ 3 }  3->{ 3 }  4->{ 0 1 2 }
	 current = {}
	 **/
	
	lbfa2 = test.RFAconvertLBFA(re); // RFA --> LBFA (convert)
	cout << "lbfa2\n" << lbfa2 << endl;
	/**
	 LBFA2————画状态图得RE=((a | epsilon)+)b?cd*|(empty())
	 Q = [0,4) s = 0 F = { 2 3 }
	 Qmap_inverse = { 'a'->0  'b'->1  'c'->2  'd'->3  }
	 follow = 0->{ 0  1  2 }   1->{ 2 }  2->{ 3 }  3->{ 3 }
	 current = {}	 **/
	cout << "以下分别为各类型FA对应转换的DFA\n" << endl;
	DFA RFATest5_dfa1 = rfa1.determinism();
	cout << "———RFATest5_dfa1:" << RFATest5_dfa1 << endl;//——————————————————————成功转换成DFA
	DFA RFATest5_dfa2 = rfa2.determinism();
	cout << "———RFATest5_dfa2:" << RFATest5_dfa2 << endl; //——————————————————————成功转换成DFA
	DFA RFATest5_dfa3 = lbfa1.determinism();
	cout << "———RFATest5_dfa3:" << RFATest5_dfa3 << endl;//——————————————————————成功转换成DFA
	DFA RFATest5_dfa4 = lbfa2.determinism();
	cout << "———RFATest5_dfa4:" << RFATest5_dfa4 << endl;//——————————————————————成功转换成DFA
	cout << "以下为lbfa1通过另一种方式对应转换的DFA\n" << endl;
	DFA RFATest5_dfa5 = test.DFAfromLBFA(re);
	cout << RFATest5_dfa5 << endl;
	/**
	 DFA————画状态图得RE=((a | epsilon)+)b?cd*|(empty())
	 Q = [0,5) 	S = { 0 } 	F = { 3 4 }
	 Transitions =
	 0->{ 'a'->1  'b'->2  'c'->3 }
	 1->{ 'a'->1  'b'->2  'c'->3 }
	 2->{ 'c'->3 }
	 3->{ 'd'->4 }
	 4->{ 'd'->4 }
	 current = -1
	  **/
	FiniteAutomata ffa1;
	ffa1.perform(RFATest5_dfa1, "RFATest5_dfa1.ADS");
	FiniteAutomata ffa2;
	ffa2.perform(RFATest5_dfa3, "RFATest5_dfa3.ADS");
	FiniteAutomata ffa3;
	ffa3.perform(RFATest5_dfa5, "RFATest5_dfa5.ADS");
}
void RFATest()
{
	cout << "=====RFATest=====\n" <<flush;
	//从上往下依次为RE样例1-5
	RFATest1();
	RFATest2();
	RFATest3();
	RFATest4();
	RFATest5();
}


