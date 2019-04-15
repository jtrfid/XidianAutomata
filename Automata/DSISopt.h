/***********************************************************************
Implementation class: DSISopt
Files: DSISopt.h, DSISopt.cpp
Uses: CharRange, CRSet, ISImpl, RE

Description: Class DSISopt provides the full abstract state interface of an item set (see class ISImpl).
DSISopt inherits from ISImpl for implementation. It is used in the optimized
item set construction [Wat93a, Construction 5.82J. The optimized item set construction
(called Oconstr in [Wat93a]) can yield much smaller DFAs than either the normal item set
construction or DeRemer's construction.
***********************************************************************/
//#pragma once


#ifndef AUTOMATA_DSISOPT_H
#define AUTOMATA_DSISOPT_H


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
// See Construction [Wat93a, Construction 5.82].
// DSISopt inherits from ISImpl for implementation.
class DSISopt :protected ISImpl
{
public:
	// Must always have an argument-less constructor.
	inline DSISopt();

	// A special constructor:
	inline DSISopt(const RE *r);

	inline const DSISopt& operator=(const DSISopt& r);

	// The required member functions :
	inline int final() const;
	inline CRSet out_labels() const;
	DSISopt out_transition(const CharRange a) const;
	inline int operator==(const DSISopt& r) const;
	inline int operator!=(const DSISopt& r) const;

	friend std::ostream& operator<<(std::ostream& os, const DSISopt& r);
	inline int class_invariant() const;

private:
	// Helpers: the optimization function of the DeRemer construction.
	inline void opt();
	void traverse_opt(const RE& r, int& node_num);
};

// Must always have an argument-less constructor.
// The default constructor won't leave *this in a condition satisfying the
// class invariant.
inline DSISopt::DSISopt() :ISImpl()
{

}

inline DSISopt::DSISopt(const RE *r) : ISImpl(r)
{
	assert(r->class_invariant());
	// The ISImpl constructor will have closed beforel after, but not optimized yet.
	opt();
	assert(class_invariant());
}

inline const DSISopt& DSISopt::operator=(const DSISopt& r)
{
	assert(r.class_invariant());
	ISImpl::operator=(r);
	// *this may not satisfy the invariant until after the assignment.
	assert(class_invariant());
	return(*this);
}

// The required member functions :
inline int DSISopt::final() const
{
	assert(class_invariant());
	return(ISImpl::final());
}
inline CRSet DSISopt::out_labels() const
{
	assert(class_invariant());
	return(ISImpl::out_labels());
}

inline int DSISopt::operator==(const DSISopt& r) const
{
	assert(class_invariant() && r.class_invariant());
	return(ISImpl::operator==(r));
}

inline int DSISopt::operator!=(const DSISopt& r) const
{
	return(!operator==(r));
}

inline void DSISopt::opt()
{
	// Remember if there's a dot after the root.
	int par(after.contains(0));
	after.clear();
	int i(0);
	traverse_opt(*e, i);
	assert(i == (e->num_operators()));
	// The dot after the root may have been removed,so it can be put back.
	if (par) after.set_bit(0);
}

inline int DSISopt::class_invariant() const
{
	// Should really check that before and after are fully closed,
	// and that they are optimized.
	return(ISImpl::class_invariant());
}





#endif // !AUTOMATA_DSISOPT_H



