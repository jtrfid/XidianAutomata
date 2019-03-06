/***********************************************************************
Implementation class: DSDeRemer
Files: DSDeRemer.h, DSDeRemer.cpp
Uses: CharRange, CRSet, ISImpl, RE

Description: Class DSDeRemer provides the full abstract state interface of an item set (see class ISImpl).
DSDeRemer inherits from ISImpl for implementation. It is used in DeRemer's construction [Wat93a, Construction 5.75J. 
DeRemer's construction can yield smaller DFAs than the item set construction.
***********************************************************************/
//#pragma once

#ifndef AUTOMATA_DSDREMER_H
#define AUTOMATA_DSDREMER_H




#include <iostream>
// 去下行注释则禁用 assert()
// #define NDEBUG
#include <cassert>  // 必须包含
#include "CharRange.h"
#include "CRSet.h"
#include "RE.h"
#include "ISImpl.h"

// This class is used to represent abstract States in a DFA that is still under
// construction.It represents the item sets in the DeRemer construction.
// See Construction [Wat93a, Construction 5.75].
// DSDeRemer inherits from ISImpl for implementation.
class DSDeRemer :protected ISImpl
{
public:
	// Must always have an argument-less constructor.
	inline DSDeRemer();

	// A special constructor:
	inline DSDeRemer(const RE *r);

	inline const DSDeRemer& operator=(const DSDeRemer& r);

	// The required member functions :
	inline int final() const;
	inline CRSet out_labels() const;
	DSDeRemer out_transition(const CharRange a) const;
	inline int operator==(const DSDeRemer& r) const;
	inline int operator!=(const DSDeRemer& r) const;

	friend std::ostream& operator<<(std::ostream& os, const DSDeRemer& r);
	inline int class_invariant() const;

private:
	// Helpers: the optimization function of the DeRemer construction.
	inline void opt();
	void traverse_opt(const RE& r, int& node_num);
};

// Must always have an argument-less constructor.
// The default constructor won't leave *this in a condition satisfying the
// class invariant.
inline DSDeRemer::DSDeRemer() :ISImpl()
{

}

inline DSDeRemer::DSDeRemer(const RE *r) : ISImpl(r)
{
	assert(r->class_invariant());
	// The ISImpl constructor will have closed beforel after, but not optimized yet.
	opt();
	assert(class_invariant());
}

inline const DSDeRemer& DSDeRemer::operator=(const DSDeRemer& r)
{
	assert(r.class_invariant());
	ISImpl::operator=(r);
	// *this may not satisfy the invariant until after the assignment.
	assert(class_invariant());
	return(*this);
}

// The required member functions :
inline int DSDeRemer::final() const
{
	assert(class_invariant());
	return(ISImpl::final());
}
inline CRSet DSDeRemer::out_labels() const
{
	assert(class_invariant());
	return(ISImpl::out_labels());
}

inline int DSDeRemer::operator==(const DSDeRemer& r) const
{
	assert(class_invariant() && r.class_invariant());
	return(ISImpl::operator==(r));
}

inline int DSDeRemer::operator!=(const DSDeRemer& r) const
{
	return(!operator==(r));
}

inline void DSDeRemer::opt()
{
	int i(0);
	traverse_opt(*e, i);
	assert(i == (e->num_operators()));
}

inline int DSDeRemer::class_invariant() const
{
	// Should really check that before and after are fully closed,
	// and that they are optimized.
	return(ISImpl::class_invariant());
}





#endif // !AUTOMATA_DSDREMER_H



