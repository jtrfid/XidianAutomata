/****************************************************************************
	Implementation class: TransRel
	Files: TransRel.h, TransRel.cpp
	Uses: CharRange, CRSet, State, StateSet, StateTo, Trans
	Description: A TransRel maps a StateSet and a character (or a CharRange) to a StateSet. It is
	used to implement the transition relation in the class FA (see [Wat93a, Definition 2.1]). The
	responsibility of maintaining the domain of the relation lies with the client. Transitions can
	be added, but not removed.
****************************************************************************/
#pragma once
#include<iostream>
// 去下行注释则禁用 assert()
// #define NDEBUG
#include <cassert>  // 必须包含
#include "StateTo.h"
#include "Trans.h"

// Implement a transition relation, using a function from States to Trans(which, in turn are char -> State).
// This is used for transition relations in normal FA's.
class TransRel :public StateTo<Trans>
{
public:
	// Constructors, destructors, operutor=:
	
	// Default argument-less constructor is okay.
	inline TransRel();
	inline TransRel(const TransRel& r);
	
	// Default destructor is okay

	inline const TransRel& operator=(const TransRel& r);
	
	// Some relational operators:
	// Compute the image of r, and a under *this. return T(r,a) = { image }
	StateSet image(const StateSet& r, const char a) const;

	// Transitioning on a CharRange? (Same idea as above.)
	StateSet transition_on_range(const StateSet& r, const CharRange a) const;
	
	// On which labels can we transition?
	CRSet out_labels(const StateSet& r) const;
	
	// Some functions updating *this:  T(p) = {(r,q)}
	inline TransRel& add_transition(const State p, const CharRange r, const State q);
	
	// Some domain related members:
	
	// What is the domain of this relation.
	inline int domain() const;
	
	// Change the domain of this relation.
	void set_domain(const int r);
	
	// Recycle this entire structure.
	void reincarnate();
	
	// Union relation r into *this, while adjusting r.
	TransRel& disjointing_union(const TransRel& r);
	
	// Some special members:
	
	// 必须类内定义
	friend std::ostream& operator<<(std::ostream& os, const TransRel& r);

	inline int class_invariant() const;
};

// Default argument-less constructor is okay.
inline TransRel::TransRel():StateTo<Trans>()
{
	assert(class_invariant());
}
inline TransRel::TransRel(const TransRel& r):StateTo<Trans>(r)
{
	assert(class_invariant());
}

// Default destructor is okay
inline const TransRel& TransRel::operator = (const TransRel& r)
{
	assert(r.class_invariant());
	// Call back to the base class
	StateTo<Trans>::operator=(r);
	assert(class_invariant());
	return(*this);
}

// Some functions updating *this:  T(p) = {(r,q)}
inline TransRel& TransRel::add_transition(const State p, const CharRange r, const State q)
{
	assert(class_invariant());
	assert(0 <= p && p < domain());
	assert(0 <= q && q < domain());
	map(p).add_transition(r, q);
	assert(class_invariant());
	return(*this);
}

// What is the domain of this relation.
inline int TransRel::domain() const
{
	return(StateTo<Trans>::domain());
}

inline int TransRel::class_invariant() const
{
	// First, we must satisfy the base class_invariant().
	int res(StateTo<Trans>::class_invariant());
	for (int i = 0; i < domain() && res; i++)
	{
		res = lookup(i).class_invariant() && (lookup(i).range() == domain());
	}
	return(res);
}

// 修改为inline,否则连接器找不到StateTo<Trans>,但是std::cout<<出现同样的错误,再把StateTo<Trans>移入它所在的类内定义，ok
inline std::ostream& operator<<(std::ostream& os, const TransRel& r)
{
	assert(r.class_invariant());
	return(os << (const StateTo<Trans>&)r);
	//return(os << r); // 引起递归
}

