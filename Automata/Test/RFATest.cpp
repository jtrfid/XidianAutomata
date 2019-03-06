#include <iostream>
#include "../Sigma.h"
#include "../FA.h"
#include "../Constrs.h"

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
		//cout << left << endl; // . | 'a' 1(epsilon) * 'b'  ==> op = .,left = (| 'a' 1(epsilon)),right = (* b)
		re = left;
	}

	//  RE =  (a ∪ b)ab
	void reExample2_9noStar(RE& re)
	{
		//cout << "=====reExample2_9noStar=====\n";
		Reg<RE> left, right;

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
	/*************************************************************************
	 Definition 4.30 (Homomorphism from RE to [RFA]): We define rfa in RE ---> [RFA], 
	 to be the unique homomorphism from REs to [RFA]
	 //RFA rfa1(re);     // 在RFA.h，RFA.cpp定义和实现RFA(const RE& e)
	 RFA rfa1 = rfa(re); // 等效，在Constrs.h中封装，RFA rfa(const RE& r)
	 *************************************************************************/
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
	DFA DFAfromLBFA(const RE& re) 
	{
		cout << "=====DFAfromLBFA=====\n";
		DFA dfa = BerrySethi(re).determinism();
		return dfa;
	}

};

void reExample315RFATest()
{
	cout << "=====reExample315RFATest=====\n";
	RFATestClass test;
	RFA rfa1,rfa2;
	LBFA lbfa;
	RE re;
	test.reExample315(re);
	cout << "reExample315: " << re << endl; // . | 'a' 1(epsilon) * 'b'  ==> op = .,left = (| 'a' 1(epsilon)),right = (* b)
	
	rfa1 = test.re2RFA_homomorphismTest(re); // RE --> RFA (Homomorphism from RE to[RFA])
	cout << rfa1 << endl;
	/** RFA
		Q = [0,2) first = { 0  1 } last = { 0  1 }
		Qmap_inverse = { 'a'->0  'b'->1 }
		follow = 0->{ 1 } 1->{ 1 }
		Nullable = true
		final = false
		current = {}
		**/
	rfa2 = test.rfa_sigmaTest(re);  // RE --> RFA (Sigma-algebra of RFA's)
	cout << rfa2 << endl; // 同上

	lbfa = test.RFA2LBFA(re); // RFA --> LBFA
	cout << lbfa << endl;
	/**
	 LBFA
	Q = [0,3) s = 2 F = { 0  1  2 } Qmap_inverse = { 'a'->0  'b'->1 }
    follow = 0->{ 1 } 1->{ 1 } 2->{ 0  1 } current = {}
	 **/

	lbfa = test.RFAconvertLBFA(re); // RFA --> LBFA (convert)
	cout << lbfa << endl;
	/**
	 LBFA
	Q = [0,2) s = 0 F = { 0  1 } Qmap_inverse = { 'a'->0  'b'->1 }
	follow = 0->{ 1 } 1->{ 1 }
	current = {}
		 **/

	DFA dfa = test.DFAfromLBFA(re);
	cout << dfa << endl;
	/**
	DFA
	Q = [0,3) S = { 0 } F = { 0  1  2 }
	Transitions = 0->{ 'a'->1  'b'->2 } 1->{ 'b'->2 } 2->{ 'b'->2 }
	current = -1
	**/
}

void reExample2_9noStarRFATest()
{
	cout << "=====reExample2_9noStarRFATest=====\n";
	RFATestClass test;
	RFA rfa1, rfa2;
	LBFA lbfa;
	RE re;
	test.reExample2_9noStar(re);
	cout << "reExample2_9noStar: " << re << endl; // . . | 'a' 'b' 'a' 'b'

	rfa1 = test.re2RFA_homomorphismTest(re); // RE --> RFA (Homomorphism from RE to[RFA])
	cout << rfa1 << endl;
	/** RFA
	 Q = [0,4) first = { 0  1 } last = { 3 }
     Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'b'->3 }  // 'a'->2 表示T:(0,a,2)和(1,a,b), 每个状态的各个入弧均为同一个字母
	 follow = 0->{ 2 } 1->{ 2 } 2->{ 3 } 3->{}
	 Nullable = false final = false current = {}
	**/
	rfa2 = test.rfa_sigmaTest(re);  // RE --> RFA (Sigma-algebra of RFA's)
	cout << rfa2 << endl; // 同上

	lbfa = test.RFA2LBFA(re); // RFA --> LBFA
	cout << lbfa << endl;
	/**
	 LBFA
	 Q = [0,5) s = 4 F = { 3 }
	 Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'b'->3 }
	 follow = 0->{ 2 } 1->{ 2 } 2->{ 3 } 3->{} 4->{ 0  1 }
     current = {}
	 **/

	lbfa = test.RFAconvertLBFA(re); // RFA --> LBFA (convert)
	cout << lbfa << endl;
	/**
	 LBFA
	 Q = [0,4) s = 0  F = { 3 }
     Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'b'->3 }
	 follow = 0->{ 2 } 1->{ 2 } 2->{ 3 } 3->{}
	 current = {}
	 **/

	DFA dfa = test.DFAfromLBFA(re);
	cout << dfa << endl;
	/**
	 DFA
	 Q = [0,5) 	S = { 0 } 	F = { 4 }
	 Transitions = 0->{ 'a'->1  'b'->2 }  1->{ 'a'->3 }	2->{ 'a'->3 } 3->{ 'b'->4 }
	 4->{} current = -1
	 **/
}

void reExample2_9StarRFATest()
{
	cout << "=====reExample2_9StarRFATest=====\n";
	RFATestClass test;
	RFA rfa1, rfa2;
	LBFA lbfa;
	RE re;
	test.reExample2_9Star(re);
	cout << "reExample2_9Star: " << re << endl; // . . * | 'a' 'b' 'a' 'b'

	rfa1 = test.re2RFA_homomorphismTest(re); // RE --> RFA (Homomorphism from RE to[RFA])
	cout << rfa1 << endl;
	/** RFA
	Q = [0,4)  first = { 0  1  2 }
	last = { 3 }  Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'b'->3 }
	follow = 0->{ 0  1  2 }   1->{ 0  1  2 }  2->{ 3 }  3->{}
	Nullable = false
	final = false
	current = {}
	**/
	rfa2 = test.rfa_sigmaTest(re);  // RE --> RFA (Sigma-algebra of RFA's)
	cout << rfa2 << endl; // 同上

	lbfa = test.RFA2LBFA(re); // RFA --> LBFA
	cout << lbfa << endl;
	/**
	LBFA
	Q = [0,5)  s = 4  F = { 3 }
	Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'b'->3 }
	follow = 0->{ 0  1  2 }   1->{ 0  1  2 }  2->{ 3 }  3->{}   4 ->{ 0 1 2 }
	current = {}
	 **/

	lbfa = test.RFAconvertLBFA(re); // RFA --> LBFA (convert)
	cout << lbfa << endl;
	/**
	convert(RFA)  to  LBFA
	Q = [0,4)  s = 0  F = { 3 }
	Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'b'->3 }
	follow = 0->{ 0  1  2 }   1->{ 0  1  2 }  2->{ 3 }  3->{}
	current = {}
	 **/

	DFA dfa = test.DFAfromLBFA(re);
	cout << dfa << endl;
	/**
	DFA from LBFA
	Q = [0,5)  S = { 0 }   F = { 3  4 }
	Transitions =
	0->{ 'a'->1  'b'->2 }
	1->{ 'a'->3  'b'->4 }
	2->{ 'a'->1  'b'->2 }
	3->{ 'a'->3  'b'->4 }
	4->{ 'a'->1  'b'->2 }
	current = -1
	 **/
}

void RFATest()
{
	cout << "=====RFATest=====\n" <<flush;
	reExample315RFATest();
	//reExample2_9noStarRFATest();
	//reExample2_9StarRFATest();
}


