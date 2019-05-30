#include<iostream>
#include"FA.h"

using namespace std;

class FA_Add: protected FA
{
public:
    FA_Add();

	//set new domain
    void set_domain(const int r);
	
	//return present domain
	int domain();

	StateSet whatscurrent();

	//set start state
    void start(const int r);

	//set final state
    void final(const int r);

	//add transition QxVxQ
    void add_transition(State p,CharRange r,State q);

	//add epsilon-transition QxQ
	void add_epsilon(State p, State q);

    //void remove_transition(State p,CharRange r,State q);

	//void remove_epsilon(State p, State q);

	inline friend std::ostream& operator<<(std::ostream& os, const FA_Add& r);
};

FA_Add::FA_Add()
{
}

void FA_Add::set_domain(const int r)
{
	Q.reincarnate();

    for(int i = 0; i < r; i++)Q.allocate();

    S.set_domain(r);
    F.set_domain(r);
	E.set_domain(r);
	Transitions.set_domain(r);
	current.set_domain(r);
}

int FA_Add::domain()
{
	return(Q.size());
}

StateSet whatscurrent()
{
	return(current);
}

void FA_Add::start(const int r)
{
	assert(class_invariant());
    assert(0 <= r && r < Q.size());

	S.clear();
    S.add(r);

	assert(class_invariant());
}

void FA_Add::final(const int r)
{
	assert(0 <= r && r < Q.size());
	assert(0 <= r && r < Q.size());

	F.clear();
	F.add(r);

	assert(class_invariant());
}

void FA_Add::add_transition(State p,CharRange r,State q)
{
	assert(class_invariant());
	assert(0 <= p && p < domain());
	assert(0 <= q && q < domain());

	Transitions.add_transition(p, r, q);

	assert(class_invariant());
}

void FA_Add::add_epsilon(State p, State q)
{
	assert(class_invariant());
	assert(0 <= p && p < domain());
	assert(0 <= q && q < domain());

	E.union_cross(p, q);

	assert(class_invariant());
}

inline std::ostream& operator<<(std::ostream& os, const FA_Add& r)
{
	assert(r.class_invariant());
	os << "\nFA\n";
	os << "Q = " << r.Q << '\n';
	os << "S = " << r.S << '\n';
	os << "F = " << r.F << '\n';
	os << "Transitions = \n" << r.Transitions << '\n';
	os << "E = \n" << r.E << '\n';
	os << "current = " << r.current << '\n';
	return(os);
}

void FAAddTest()
{
	FA_Add ad;
	ad.set_domain(5);
	ad.start(0);
	ad.final(4);
	ad.add_transition(0, 'a', 1);
	ad.add_transition(1, 'b', 2);
	ad.add_transition(2, 'c', 3);
	ad.add_transition(2, 'd', 4);
	//ad.add_epsilon(1, 2);
	cout << "ad= " << ad << endl;

	cout << "States number: " << ad.num_states() << endl;

	ad.restart();
	char c[] = "abc";
	cout << ad.acceptable(c) << endl;
	ad.restart();
	ad.advance('a');
	cout << "is FA stucked? " << ad.stuck() << endl;
	ad.advance('b');
	ad.advance('d');
	cout << ad << endl;
	cout << "FA in final State? " << ad.in_final() << endl;
	
	ad.restart();
	ad.advance('a');
	ad.advance('b');
	ad.advance('c');
	
	cout << "whats current state? " << ad.whatscurrent() << endl;
	cout << "FA in final State? " << ad.in_final() << endl;
	cout << "is FA stucked? " << ad.stuck() << endl;

	ad.restart();
	ad.advance('a');
	ad.advance('b');
	ad.advance('c');
	ad.advance('e');
	
	cout << "whats current state? " << ad.whatscurrent() << endl;
	cout << "FA in final State? " << ad.in_final() << endl;
	cout << "is FA stucked? " << ad.stuck() << endl;
}