#include <iostream>
#include "Sigma.h"
#include "FA.h"
#include "Constrs.h"
#include "LBFA.h"
#include "RBFA.h"

void minTest(DFA dfa2)
{
	DFA dfa1_1 = dfa2;
	std::cout << "-------------min by Brzozowski" << dfa1_1.min_Brzozowski() << std::endl;

	DFA dfa1_2 = dfa2;
	std::cout << "-------------min by dragon" << dfa1_1.min_dragon() << std::endl;

	DFA dfa1_3 = dfa2;
	std::cout << "-------------min by Hopcroft" << dfa1_1.complete().min_Hopcroft().usefulf() << std::endl;

	DFA dfa1_4 = dfa2;
	std::cout << "-------------min by HopcroftUllman" << dfa1_1.min_HopcroftUllman() << std::endl;

	DFA dfa1_5 = dfa2;
	std::cout << "-------------min by Watson" << dfa1_1.min_Watson() << std::endl;
}

using namespace std;
class BSTestClass
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
		//Reg<RE> re1 = Reg<RE>(); // ��Ч
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
		cout << "����Ϊ�˸������������RE���\n" << endl;
		////////////////////////////// �ۺ�Ӧ��
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
		cout << left << "������������(a | epsilon) concat b* \n" << endl; // . | 'a' 1(epsilon) * 'b'  ==> op = .,left = (| 'a' 1(epsilon)),right = (* b)

		//(01)����������������������Զ����̲�p127ҳϰ��4����ѡ��ߴ����Եı��ʽ���и���ʹ�������
		//�ã�r+(sr?t|r|1)*����1����epsilon
		//�����Զ����·����Ա��ʽ���в��Ȼ����ÿ������
		/*cout << "\n\n����������������\n" << endl;
		Reg<RE> left0, right0, left1, right1;//���������������Ҳ�ȡ�µı�����β׺
		left0.symbol('s');
		right0.symbol('r');
		right0.question();
		left0.concat(right0);
		right0.symbol('t');
		left0.concat(right0);//�����������srt
		cout << left0 << "    ����sr?t \n" << endl;
		right0.symbol('r');
		right0.Or(right1.epsilon());//�����������r|1
		cout << right0 << "    ����r|1 \n" << endl;
		left0.Or(right0);
		cout << left0 << "    ����sr?t+r|1 \n" << endl;
		left1.symbol('r');
		left1.plus();
		left0.star();
		left1.concat(left0);
		cout << left1 << "    ���������r+(sr?t|r|1)* \n" << endl;//�����
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
		//cout << left<<"    ���Ӧ����(a | epsilon) concat b*\n " << endl; // . | 'a' 1(epsilon) * 'b'  ==> op = .,left = (| 'a' 1(epsilon)),right = (* b)
		re = left;
	}

	//  RE =  (a �� b)ab
	void reExample2_9noStar(RE& re)
	{
		//cout << "=====reExample2_9noStar=====\n";
		Reg<RE> left, right;
		cout << "\n�������������������Ե�11111\n" << endl;
		//  RE =  (a �� b) ab
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

	//  RE =  (* (a �� b)) ab

	void reExample2_9Star(RE& re)
	{
		//cout << "=====reExample2_9Star=====\n";
		Reg<RE> left, right;

		//  RE =  (* (a �� b)) ab
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
	//  RE =  ((a �� b*)) ab��Ϊ���о���RE =  (* (a �� b)) ab�������������һ��ͬ�����õĺ�����
	/**
	void reExample2extra_9Star(RE& re)
	{
		cout << "\n=====reExample2extra_9Star=====\n";
		Reg<RE> left, right;

		//  RE =  ((a �� b*)) ab
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
	
	//���ִ���ĵط��������ֱ��LBFA->DFA�Ļ�
	
	DFA LBFA2DFA(LBFA lbfa) //ʵ�ʾ���RE->RFA->LBFA->DFA(�Ҳ������ֱ�Ӵ�LBFA��DFA)
	{
		
		cout << "=====LBFA2DFA=====\n";
		DFA dfa=lbfa.determinism();
		return dfa;
	}
	
	/**
	����дҲ�ǿ��Եģ�����RE->RFA->LBFA->DFA���������������������Ŀ�ľ��ǲ���BerrySethi()��
	����BerrySethi()������������������ת����RE->LBFA������ֻ��Ҫ����һ��LBFA->DFA�ĺ����Ϳ�����
	Ҳ������RFATest����������;����RFA����Ҳ�����ĵ���˵��BS��һ��������rfa()+decode()��˵��Ϊ��Ч�ķ�ʽ
	DFA DFAfromLBFA(const RE& re) //ʵ�ʾ���RE->RFA->LBFA->DFA
	{
		cout << "=====DFAfromLBFA=====\n";
		DFA dfa = BerrySethi(re).determinism();
		return dfa;
	}
	**/
};
	void BSTest1()
	{
		cout << "=====BSTest1=====\n";
		BSTestClass test;
		LBFA lbfa1,lbfa2;
		RBFA rbfa1, rbfa2;
		RE re;
		test.reExample315(re);
		cout << "����1��RE=��a|epsilon) concat  b*: " << re << endl; // . | 'a' 1(epsilon) * 'b'  ==> op = .,left = (| 'a' 1(epsilon)),right = (* b)

		
		lbfa1 = BerrySethi(re); 
		lbfa2 = BS_variation(re);
		rbfa1 = BerrySethLdual(re);
		rbfa2 = BS_variation_dual(re);
		cout << "\n������������������LBFA1:\n" <<lbfa1 << endl;
		cout << "\n������������������LBFA2:\n" << lbfa2 << endl;
		cout << "\n������������������RBFA1:\n" << rbfa1 << endl;
		cout << "\n������������������RBFA2:\n" << rbfa2 << endl;
		/**
		 LBFA1����������״̬ת��ͼ�ɵ�RE=(a|1)b*
		Q = [0,3) s = 2 F = { 0  1  2 } Qmap_inverse = { 'a'->0  'b'->1 }
		follow = 0->{ 1 } 1->{ 1 } 2->{ 0 1 }
		current = {}
		 LBFA2��������
		 Q = [0,3) s = 0 F = { 0  1  2 } Qmap_inverse = { '$'->0  'a'->1  'b'->2 }
		follow = 0->{ 1 2 } 1->{ 2 } 2->{ 2 }
		current = {}
		 RBFA1�������������s=0�������'a'���ȥ������ȷ�ģ�����ȱ��1->2��ת�����������ת���𣿼���'$'�������ģ�����ʲô��
	    Q = [0,3) S = { 0  1  2 } f = 2 Qmap_inverse = { 'a'->0  'b'->1 }
		follow = 0->{ 1 2 } 1->{ 1 2 }
		current = {}
		 RBFA2��������
		Q = [0,3) S = { 2 } f = 2 Qmap_inverse = { 'a'->0  'b'->1  '$'->2 }
		follow = 0->{ 1 2 } 1->{ 1 2 } 
		current = {}
			 **/
		cout << "���·ֱ����lbfa1��lbfa2����ת����DFA��lbfa1ͨ������һ�ַ�ʽ�����DFA\n" << endl;
		DFA DFA1 = lbfa1.determinism();
		cout << "����������������DFA1_lbfa1:" << DFA1 << endl;//���������������������������������������������ɹ�ת����DFA
		DFA DFA2 = lbfa2.determinism();
		cout << "����������������DFA1_lbfa2:" << DFA2 << endl;//���������������������������������������������ɹ�ת����DFA
		
		DFA dfa = test.LBFA2DFA(lbfa1);
		cout << dfa << endl;

		minTest(DFA1);
		minTest(DFA2);


		/**
		DFA����������״̬ת��ͼ�ɵ�RE=(a|1)b*
		Q = [0,3) S = { 0 } F = { 0  1  2 }
		Transitions = 0->{ 'a'->1  'b'->2 } 1->{ 'b'->2 } 2->{ 'b'->2 }
		current = -1
		**/
		
	}
	void BSTest2()
	{
		cout << "=====BSTest2=====\n";
		BSTestClass test;
		LBFA lbfa1, lbfa2;
		RBFA rbfa1, rbfa2;
		RE re;
		test.reExample2_9noStar(re);
		cout << "����2��RE=��a��b)ab: " << re << endl; // . . | 'a' 'b' 'a' 'b'

		lbfa1 = BerrySethi(re);
		lbfa2 = BS_variation(re);
		rbfa1 = BerrySethLdual(re);
		rbfa2 = BS_variation_dual(re);
		cout << "\n������������������LBFA1:\n" << lbfa1 << endl;
		cout << "\n������������������LBFA2:\n" << lbfa2 << endl;
		cout << "\n������������������RBFA1:\n" << rbfa1 << endl;
		cout << "\n������������������rBFA2:\n" << rbfa2 << endl;
		/**
	     LBFA1����������״̬ͼ��RE=��a��b)ab
	     Q = [0,5) s = 4 F = { 3 }
	     Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'b'->3 }
	     follow = 0->{ 2 } 1->{ 2 } 2->{ 3 } 3->{} 4->{ 0  1 }
	     current = {}
		 LBFA2��������
		 Q = [0,5) s = 0 F = { 4 }
		 Qmap_inverse = { '$'->1 'a'->1  'b'->2  'a'->3  'b'->4 }
		 follow = 0->{ 1 2 } 1->{ 3 } 2->{ 3 } 3->{ 4 } 4->{ }
		 current = {}
		 RBFA1�������������s=0/1�����'a''b'���ȥ������ȷ�ģ�����ȱ��3->4��ת�����������ת���𣿼���'$'�������ģ�����ʲô��
		 Q = [0,5) s = { 0 1 } F = 4
		 Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'b'->3 }
		 follow = 0->{ 2 } 1->{ 2 } 2->{ 3 } 3->{ 4 } 
		 current = {}
		 RBFA2��������
		 Q = [0,5) s = { 4 } F = 4
		 Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'b'->3 '$'->4 }
		 follow = 0->{ 2 } 1->{ 2 } 2->{ 3 } 3->{ 4 }
		 current = {}
			 **/
		cout << "���·ֱ����lbfa1��lbfa2����ת����DFA��lbfa1ͨ������һ�ַ�ʽ�����DFA\n" << endl;
		DFA DFA1 = lbfa1.determinism();
		cout << "����������������DFA1_lbfa1:" << DFA1 << endl;//���������������������������������������������ɹ�ת����DFA
		DFA DFA2 = lbfa2.determinism();
		cout << "����������������DFA1_lbfa2:" << DFA2 << endl;//���������������������������������������������ɹ�ת����DFA
		
		DFA dfa = test.LBFA2DFA(lbfa1);
		cout << dfa << endl;
		/**
	    DFA����������״̬ͼ��RE=��a��b)ab
    	 Q = [0,5) 	S = { 0 } 	F = { 4 }
	     Transitions = 0->{ 'a'->1  'b'->2 }  1->{ 'a'->3 }	2->{ 'a'->3 } 3->{ 'b'->4 }
	     4->{} current = -1
	     **/

		minTest(DFA1);
		minTest(DFA2);
		minTest(dfa);

	}
	
	void BSTest3()
	{
		cout << "=====BSTest3=====\n";
		BSTestClass test;
		LBFA lbfa1, lbfa2;
		RBFA rbfa1, rbfa2;
		RE re;
		test.reExample2_9Star(re);
		cout << "����3��RE=(��a��b)*)ab: " << re << endl; // . . * | 'a' 'b' 'a' 'b'


		lbfa1 = BerrySethi(re);
		lbfa2 = BS_variation(re);
		rbfa1 = BerrySethLdual(re);
		rbfa2 = BS_variation_dual(re);
		cout << "\n������������������LBFA1:\n" << lbfa1 << endl;
		cout << "\n������������������LBFA2:\n" << lbfa2 << endl;
		cout << "\n������������������RBFA1:\n" << rbfa1 << endl;
		cout << "\n������������������rBFA2:\n" << rbfa2 << endl;
		/**
	     LBFA����������״̬ת��ͼ�ɵ�RE=(a��b)*ab�������������µ�״̬q4��ΪΨһ��ʼ״̬ʹ�� ����RFA��ֻ��һ��b�����
	     Q = [0,5)  s = 4  F = { 3 }
	     Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'b'->3 }
         follow = 0->{ 0  1  2 }   1->{ 0  1  2 }  2->{ 3 }  3->{}   4 ->{ 0 1 2 }
	     current = {}
		 LBFA2����������״̬ת��ͼ�ɵ�RE=(a��b)*ab
		 Q = [0,5)  s = 0  F = { 4 }
		 Qmap_inverse = { '$'->0  'a'->1  'b'->2  'a'->3  'b'->4 }
		 follow = 0->{ 1  2  3 }   1->{ 1  2  3 }  2->{ 1  2  3 }  3->{ 4 }   4 ->{ }
		 current = {}


		 RBFA1������������������Ҳ�ǶԵģ��������ͬ���������ǵð�������Ĺ��ĸ�+ע��һ�£�
		 Q = [0,5)  s = { 0  1  2 }  F = 4
		 Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'b'->3 }
		 follow = 0->{ 0  1  2 }   1->{ 0  1  2 }  2->{ 3 }  3->{ 4 }   4 ->{ }
		 current = {}
		 RBFA2���������������ͬ���������ǵð�������Ĺ��ĸ�+ע��һ�£�
		 Q = [0,5)  s = 4  F = { 4 }
		 Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'b'->3  '$'->4  }
		 follow = 0->{ 0  1  2 }   1->{ 0  1  2 }  2->{ 3 }  3->{ 4 }   4 ->{ }
		 current = {}
			 **/
		cout << "���·ֱ����lbfa1��lbfa2����ת����DFA��lbfa1ͨ������һ�ַ�ʽ�����DFA\n" << endl;
		DFA DFA1 = lbfa1.determinism();
		cout << "����������������DFA1_lbfa1:" << DFA1 << endl;//���������������������������������������������ɹ�ת����DFA
		DFA DFA2 = lbfa2.determinism();
		cout << "����������������DFA1_lbfa2:" << DFA2 << endl;//���������������������������������������������ɹ�ת����DFA
		
		DFA dfa = test.LBFA2DFA(lbfa1);
		cout << dfa << endl;
		/**
		DFA from LBFA(����������״̬ת��ͼ�ó�RE=(a��b)*ab)
		Q = [0,4)  S = { 0 }   F = { 3 }
		Transitions =
		0->{ 'a'->1  'b'->2 }
		1->{ 'a'->1  'b'->3 }
		2->{ 'a'->1  'b'->2 }
		3->{ 'a'->1  'b'->2 }
		current = -1
		 **/
		minTest(DFA1);
		minTest(DFA2);
		minTest(dfa);
      }
	void BSTest4()
	{
		cout << "=====BSTest4=====\n";
		BSTestClass test;
		LBFA lbfa1, lbfa2;
		RBFA rbfa1, rbfa2;
		RE re;
		test.ex4(re);
		cout << "����4��RE=(a+b)*a+(aa)*: " << re << endl; // | . * | 'a' 'b' 'a' * . 'a' 'a'

		lbfa1 = BerrySethi(re);
		lbfa2 = BS_variation(re);
		rbfa1 = BerrySethLdual(re);
		rbfa2 = BS_variation_dual(re);
		cout << "\n������������������LBFA1:\n" << lbfa1 << endl;
		cout << "\n������������������LBFA2:\n" << lbfa2 << endl;
		cout << "\n������������������RBFA1:\n" << rbfa1 << endl;
		cout << "\n������������������rBFA2:\n" << rbfa2 << endl;
		/**
		 LBFA1����������״̬ͼ��RE=(a+b)*a+(aa)*
		 Q = [0,6) s = 5 F = { 2 4 5 }
		 Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'a'->3  'a'->4 }
		 follow = 0->{ 0 1 2 } 1->{ 0 1 2 } 2->{} 3->{ 4 } 4->{ 3 } 5->{ 0 1 2 3 }
		 current = {}
		 LBFA2����������״̬ͼ��RE=(a+b)*a+(aa)*
		 Q = [0,6) s = 0 F = { 0 3 5 }
		 Qmap_inverse = { '$'->0  'a'->1  'b'->2  'a'->3  'a'->4  'a'->5 }
		 follow = 0->{ 1 2 3 4 } 1->{ 1 2 3 } 2->{ 1 2 3 } 3->{} 4->{ 5 } 5->{ 4 } 
		 current = {}
		 RBFA1��������RE=(a+b)*a+(aa)*
		 Q = [0,6) s = {  0 1 2 3 5 } F = 5
		 Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'a'->3  'a'->4 }
		 follow = 0->{ 0 1 2 } 1->{ 0 1 2 } 2->{ 5 } 3->{ 4 } 4->{ 3 5 } 5->{ }
		 current = {}
		 RBFA2��������RE=(a+b)*a+(aa)*
		 Q = [0,6) s = { 5 } F = 5
		 Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'a'->3  'a'->4 '$'->5 }
		 follow = 0->{ 0 1 2 } 1->{ 0 1 2 } 2->{ 5 } 3->{ 4 } 4->{ 3 5 } 5->{ }
		 current = {}
			 **/
		cout << "���·ֱ����lbfa1��lbfa2����ת����DFA��lbfa1ͨ������һ�ַ�ʽ�����DFA\n" << endl;
		DFA DFA1 = lbfa1.determinism();
		cout << "����������������DFA1_lbfa1:" << DFA1 << endl;//���������������������������������������������ɹ�ת����DFA
		DFA DFA2 = lbfa2.determinism();
		cout << "����������������DFA1_lbfa2:" << DFA2 << endl;//���������������������������������������������ɹ�ת����DFA
		
		DFA dfa = test.LBFA2DFA(lbfa1);
		cout << dfa << endl;
		/**
		DFA����������״̬ͼ��RE=(a+b)*a+(aa)*
		 Q = [0,5) 	S = { 0 } 	F = { 0 1 3 4 }
		Transitions =
		0->{ 'a'->1  'b'->2 }
		1->{ 'a'->3  'b'->2 }
		2->{ 'a'->4  'b'->2 }
		3->{ 'a'->1  'b'->2 }
		4->{ 'a'->4  'b'->2 }
		current = -1
		 **/

		minTest(DFA1);
		minTest(DFA2);
		minTest(dfa);
	}
	void BSTest5()
	{
		cout << "=====BSTest5=====\n";
		BSTestClass test;
		LBFA lbfa1, lbfa2;
		RBFA rbfa1, rbfa2;
		RE re;
		test.ex5(re);
		cout << "����5��RE=((a | epsilon)+)b?cd*|(empty()): " << re << endl; // | . . . + | 'a' 1 ? 'a' 'c' * 'd' 0

		lbfa1 = BerrySethi(re);
		lbfa2 = BS_variation(re);
		rbfa1 = BerrySethLdual(re);
		rbfa2 = BS_variation_dual(re);
		cout << "\n������������������LBFA1:\n" << lbfa1 << endl;
		cout << "\n������������������LBFA2:\n" << lbfa2 << endl;
		cout << "\n������������������RBFA1:\n" << rbfa1 << endl;
		cout << "\n������������������rBFA2:\n" << rbfa2 << endl;
		/**
	     LBFA1����������״̬ͼ��RE=((a | epsilon)+)b?cd*|(empty())
	     Q = [0,5) s = 4 F = { 2 3 }
	     Qmap_inverse = { 'a'->0  'b'->1  'c'->2  'd'->3  }
	     follow = 0->{ 0 1 2 }   1->{ 2 }  2->{ 3 }  3->{ 3 }  4->{ 0 1 2 }
	     current = {}
		 LBFA2����������״̬ͼ��RE=((a | epsilon)+)b?cd*|(empty())
		 Q = [0,5) s = 0 F = { 3 4 }
	     Qmap_inverse = { '$'->0  'a'->1  'b'->2  'c'->3  'd'->4  }
	     follow = 0->{ 1 2 3 }   1->{ 1  2  3 }  2->{ 3 }  3->{ 4 }  4->{ 4 }
	     current = {}
		 RBFA1����������״̬ͼ��RE=((a | epsilon)+)b?cd*|(empty())
		 Q = [0,5) s = { 0 1 2 } F = 4
	     Qmap_inverse = { 'a'->0  'b'->1  'c'->2  'd'->3  }
	     follow = 0->{ 0 1 2 }   1->{ 2 }  2->{ 3 4 }  3->{ 3 4 }  4->{}
	     current = {}
		 RBFA2����������״̬ͼ��RE=((a | epsilon)+)b?cd*|(empty())
		 Q = [0,5) s = { 4 } F = 4
	     Qmap_inverse = { 'a'->0  'b'->1  'c'->2  'd'->3  '$'->4 }
	     follow = 0->{ 0  1  2 }   1->{ 2 }  2->{ 3 4 }  3->{ 3 4 }  4->{}
	     current = {}
			 **/
		cout << "���·ֱ����lbfa1��lbfa2����ת����DFA��lbfa1ͨ������һ�ַ�ʽ�����DFA\n" << endl;
		DFA DFA1 = lbfa1.determinism();
		cout << "����������������DFA1_lbfa1:" << DFA1 << endl;//���������������������������������������������ɹ�ת����DFA
		DFA DFA2 = lbfa2.determinism();
		cout << "����������������DFA1_lbfa2:" << DFA2 << endl;//���������������������������������������������ɹ�ת����DFA
		
		DFA dfa = test.LBFA2DFA(lbfa1);
		cout << dfa << endl;
		/**
	     DFA����������״̬ͼ��RE=((a | epsilon)+)b?cd*|(empty())
	     Q = [0,5) 	S = { 0 } 	F = { 3 4 }
	     Transitions =
	     0->{ 'a'->1  'b'->2  'c'->3 }
	     1->{ 'a'->1  'b'->2  'c'->3 }
	     2->{ 'c'->3 }
	     3->{ 'd'->4 }
	     4->{ 'd'->4 }
	     current = -1
	      **/

		minTest(DFA1);
		minTest(DFA2);
		minTest(dfa);
	}
void BSTest()
{
	cout << "=====BSTest����11111=====\n";
	//BSTestClass test;//Reg_RE_Test()��������RE�����Ƿ���ȷ��
	//������������ΪRE����1-5
	//test.Reg_RE_Test();
	BSTest1();
	BSTest2();
	BSTest3();
	BSTest4();
	BSTest5();
}