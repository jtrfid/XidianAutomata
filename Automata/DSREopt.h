/***********************************************************************
Implementation class: DSREopt
Files: DSREopt.h, DSREopt.cpp
Uses: CharRange, CRSet, RE

Description: This class is identical to DSRE, with one addition: the underlying regular expression
(the derivative) is reduced -- redundant subexpressions are eliminated. This makes it
more likely that two derivatives (denoting the same language) will be found to be equal (using
the DSREopt equality operator) in template function construct_components, thus giving
a DFA with fewer States.
 ***********************************************************************/
//#pragma once

#ifndef AUTOMATA_DSREOPT_H
#define AUTOMATA_DSREOPT_H


#include <iostream>
 // 去下行注释则禁用 assert()
 // #define NDEBUG
#include <cassert>  // 必须包含
#include "CharRange.h"
#include "CRSet.h"
#include "RE.h"

// This class is used to represent abstract States in a DFA that is still under
// construction.It is used in the construction of a DFA from an RE(using
// Brzozowski's optimized construction). It differs from DSRE in that the derivatives
// are optimized(redundant information is removed - see deriv.cpp)
// Most member functions are calls through to the corresponding RE members.
// DSREopt inherits from RE for implementation.
class DSREopt : protected RE
{
public:
	// Must always have an argument-less constructor.
	inline DSREopt();

	// A special constructor:
	inline DSREopt(const RE& r);

	inline const DSREopt& operator=(const DSREopt& r);

	// The required member functions:
	inline int final() const;
	inline CRSet out_labels() const;
	inline DSREopt out_transition(const CharRange a) const;
	inline int operator==(const DSREopt& r) const;
	inline int operator!=(const DSREopt& r) const;

	friend std::ostream& operator<<(std::ostream& os, const DSREopt& r);

	inline int class_invariant() const;
};

// Must always have an argument-less constructor.
inline DSREopt::DSREopt() :RE()
{
	assert(class_invariant());
}

// A special constructor:
inline DSREopt::DSREopt(const RE& r) :RE(r)
{
	assert(r.class_invariant());
	// They must always be in similarity normal form SNF(see deriv.cpp)
	RE::snf();
	// They must also be reduced.
	RE::reduce();
	assert(class_invariant());
}

inline const DSREopt& DSREopt::operator=(const DSREopt& r)
{
	assert(r.class_invariant());
	RE::operator=(r);
	//RE::operator=((const RE&)r);
	assert(class_invariant());
	return(*this);
}

// The required member functions:
inline int DSREopt::final() const
{
	assert(class_invariant());
	return(RE::Null());
}

inline CRSet DSREopt::out_labels() const
{
	assert(class_invariant());
	return(RE::First());
}

inline DSREopt DSREopt::out_transition(const CharRange a) const
{
	assert(class_invariant());
	return(RE::derivative(a));
}

inline int DSREopt::operator==(const DSREopt& r) const
{
	assert(class_invariant() && r.class_invariant());
	return(RE::operator==(r));
}

inline int DSREopt::operator!=(const DSREopt& r) const
{
	return(!operator==(r));
}

inline int DSREopt::class_invariant() const
{
	return(RE::class_invariant() && RE::in_snf());
}



#endif // !AUTOMATA_DSREOPT_H



