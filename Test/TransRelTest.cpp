#include<iostream>
#include"TransRel.h"

using namespace std;

class TransRelTestClass
{
public:

	/*
	1.set_domian
	*/
	void SetDomainTest()
	{
		TransRel tr;
		tr.set_domain(5);

		cout << "tr domain: " << tr.domain() << endl;//5
	}

	/*
	1.add_transition(State p, CharRange r, State q)  T(p,r)=q
	*/
	void AddTransitionTest()
	{
		TransRel tr;
		tr.set_domain(5);

		tr.add_transition(0, 'a', 1);//此处State不能超过Domain
		tr.add_transition(1, 'b', 2);
		tr.add_transition(2, 'c', 3);

		cout << "tr: " << endl << tr << endl;//0->{'a'->1} 1->{'b'->2} 2->{'c'->3}
	}

	/*
	1.image(const StateSet& r, const char a) 返回T(r,a)
	*/
	void ImageTest()
	{
		TransRel tr;
		StateSet s;
		tr.set_domain(5);
		s.set_domain(5);//对于image()而言，TranRel domain = StateSet domain

		tr.add_transition(0, 'a', 1);//此处State不能超过Domain
		tr.add_transition(0, 'a', 2);
		tr.add_transition(1, 'b', 2);
		tr.add_transition(2, 'c', 3);

		s.add(0);//s = {0}

		cout << "tr: " << endl << tr << endl;//0->{'a'->1 'a'->2} 1->{'b'->2} 2->{'c'->3}
		cout << "T(0,'a') = " << tr.image(s, 'a') << endl;//{1,2}

		s.remove(0);
		s.add(1);//s = {1}

		cout << "T(1,'b') = " << tr.image(s, 'b') << endl;//{2}
		cout << "T(1,'a') = " << tr.image(s, 'a') << endl;//{}
	}

	/*
	1.transition_on_range  功能与image类似
	*/
	void TransRangesTest()
	{
		TransRel tr;
		StateSet s;
		CharRange c('b', 'c');

		tr.set_domain(8);
		s.set_domain(8);

		tr.add_transition(0, 'a', 1);
		tr.add_transition(0, 'a', 2);
		tr.add_transition(0, 'b', 1);
		tr.add_transition(1, 'b', 2);
		tr.add_transition(0, 'c', 1);
		tr.add_transition(1, 'c', 2);

		cout << "tr = " << endl << tr << endl;//0->{['a','c']->1 'a'->2} 1->{['b','c']->2}
		
		s.add(0);//s = {0}

		cout << "T(0,['a','b']) = " << tr.transition_on_range(s, CharRange('a','b')) << endl;//{1}

		s.add(1); //s = {1,2}

		cout << "T((0,1),['b','c']) = " << tr.transition_on_range(s, c) << endl;//{1,2}
	}

	/*
	1.out_labels(const StateSet& r) 举例来说,若有T(r,v)=q,则此处返回v
	*/
	void OutlabelTest()
	{
		TransRel tr;
		StateSet s;

		tr.set_domain(5);
		s.set_domain(5);

		tr.add_transition(0, 'a', 1);
		tr.add_transition(0, 'b', 2);
		tr.add_transition(1, 'c', 3);
		s.add(0);

		cout << "tr = " << endl << tr << endl;//0->{'a'->1} 0->{'b'->2} 1->{'c'->3}
		cout << tr.out_labels(s);//{'a','b'}
	}

	/*
	1.:disjointing_union(const TransRel& r) 转移关系的合并
	*/
	void Disjointing_UnionTest()
	{
		TransRel tr1, tr2;
		
		tr1.set_domain(5);
		tr2.set_domain(10);

		tr1.add_transition(0, 'a', 1);
		tr1.add_transition(0, 'b', 2);
		tr1.add_transition(1, 'c', 3);

		tr2.add_transition(3, 'd', 4);
		tr2.add_transition(5, 'e', 6);
		tr2.add_transition(6, 'f', 7);

		cout << "tr1 = " << endl << tr1 << endl;
		cout << "tr1 domain = " << tr1.domain() << endl;//5
		cout << "tr2 = " << endl << tr2 << endl;
		cout << "tr2 domain = " << tr2.domain() << endl;//10

		cout << "tr1 disjointing union with tr2..." << endl;
		cout << tr1.disjointing_union(tr2) << endl;
		cout << "tr1 domian = " << tr1.domain() << endl;//15
	}

	/*
	1.reincarnate() 回收*this
	*/
	void ReincarnateTest()
	{
		TransRel tr;

		tr.set_domain(5);

		tr.add_transition(0, 'a', 1);
		tr.add_transition(1, 'b', 2);
		tr.add_transition(2, 'c', 3);

		cout << "tr = " << endl << tr;
		cout << "tr domain = " << tr.domain() << endl;//5
		cout << "reincarnate tr..." << endl;

		tr.reincarnate();

		cout << "tr = " << endl << tr;//null
		cout << "tr domain = " << tr.domain() << endl;//0
	}
};

void TransRelTest()
{
	TransRelTestClass t;
	//t.SetDomainTest();
	//t.AddTransitionTest();
	//t.ImageTest();
	t.TransRangesTest();
	//t.OutlabelTest();
	//t.Disjointing_UnionTest();
	//t.ReincarnateTest();
}