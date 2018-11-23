/****************************************************************************
Implementation class: StateEqRel
	Files: StateEqRel.h, StateEqRel.cpp
	Uses: StateSet, StateTo
Description: A StateEqRel is a binary equivalence relation on States. They are used mainly in
	DFA minimization algorithms. The argumentless constructor leaves the StateEqRel as the
	total relation. The identity member function makes the StateEqRel the identity relation.
	As with many other classes related to sets of States, the domain of the StateEqRel must be
	managed by the client(若干函数中，申请的堆内存没有被释放!!!，外部调用，使用完要删除，也可能在父类的析构函数中被自动删除). 
	Member functions are available for determining if two States are equivalent, for splitting 
	an equivalence class, and for determining the equivalence class (as	a StateSet) of a State. 
	Each equivalence class has a unique representative; if an equivalence class is split, one of the (at most two) resulting classes is guaranteed to have, as its unique.
	representative, the representative of the original class. Iteratar member functions can be
	used to iterate over the set of representatives, thereby iterating over the set of equivalence
	classes.
****************************************************************************/
#pragma once
#include<iostream>
// 去下行注释则禁用 assert()
// #define NDEBUG
#include <cassert>  // 必须包含
#include "StateSet.h"
#include "StateTo.h"

// Implement an equivalence relation on State's. These are used mainly in the DFA
// minimization algorithms. As with other State relations, the domain must be
// maintained explicitly.
class StateEqRel :protected StateTo<StateSet *>
{
public:
	// Some constructors etc :
	
	// Construct the total eq. relation of domain r.
	StateEqRel(const int r);
	inline StateEqRel(const StateEqRel& r);

	inline const StateEqRel& operator=(const StateEqRel& r);
	
	// Some members for changing the relation:
	
	// Make two States equivalent:
	StateEqRel& equivalize(const State p, const State q);
	
	// Split an equivalence class into two(assuming that r is entirely contained in a class):
	StateEqRel& split(const StateSet& r);
	
	// Make *this the identity relation:
	StateEqRel& identity();
		
	// Basic access members:
	
	// Are States p and q equivalent?
	inline int equivalent(const State p, const State q) const;
	
	// What is the equivalence class [p]?
	inline const StateSet& equiv_class(const State p) const;
	
	// What is the unique representative of eq. class [p]?
	inline State eq_class_representative(const State p) const;
	
	// What is the set of representatives of equivalence classes of *this?
	StateSet representatives() const;

	// Special members:
	
	// Domain setting stuff:
	void set_domain(int r);	
	inline int domain() const;

	friend std::ostream& operator<<(std::ostream& os, const StateEqRel& r );

	inline int class_invariant() const;
};

// Construct the total eq. relation of domain r.
inline StateEqRel::StateEqRel(const StateEqRel& r):StateTo<StateSet *>(r)
{
	assert(class_invariant());
}

inline const StateEqRel& StateEqRel::operator=(const StateEqRel& r)
{
	assert(class_invariant() && r.class_invariant());
	StateTo<StateSet *>::operator=(r);
	assert(class_invariant());
	return(*this);
}

// Are States p and q equivalent?
inline int StateEqRel::equivalent(const State p, const State q) const
{
	assert(class_invariant());
	assert(0 <= p && p < domain());
	assert(0 <= q && q < domain());
	return(lookup(p) == lookup(q));
}

// What is the equivalence class [p]?
inline const StateSet& StateEqRel::equiv_class(const State p) const
{
	assert(class_invariant());
	assert(0 <= p && p < domain());
	return(*lookup(p));
}

// What is the unique representative of eq. class [p]?
inline State StateEqRel::eq_class_representative(const State p) const
{
	assert(class_invariant());
	assert(0 <= p && p < domain());
	return(lookup(p)->smallest());
}

// Domain setting stuff:
inline int StateEqRel::domain() const
{
	return(StateTo<StateSet *>::domain());
}

inline int StateEqRel::class_invariant() const
{
	int result(1);
	for (int i = 0; i < domain() && result; i++)
	{
		result = (domain() == lookup(i)->domain());
		result = result && lookup(i)->class_invariant();
		// i's eq. class shoud contain i itself.
		result = result && lookup(i)->contains(i);
		// And that's all that lookup(i) should contain;
		// Iterator over lookup(i) and check that.
		State j;
		for (lookup(i)->iter_start(j); !lookup(i)->iter_end(j) && result; lookup(i)->iter_next(j))
		{
			result = (lookup(i) == lookup(j));
		}
	}
	return(result);
}

