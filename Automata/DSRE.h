/************************************************************************
Derivatives of regular expressions
Implementation class: DSRE
Files: DSRE.h, DSRE.cpp
Uses: CharRange, CRSet, RE
Description: A DSRE represents a derivative of a regular expression. A derivative of a regular
expression is again a regular expression; a DSRE simply provides an abstract state interface
to the derivatives.
 ************************************************************************/
#pragma once
#include <iostream>
 // 去下行注释则禁用 assert()
 // #define NDEBUG
#include <cassert>  // 必须包含
#include "CharRange.h"
#include "CRSet.h"
#include "RE.h"

// This class is used to represent abstract States in a DFA that is still under
// construction.It is used in the construction of a DFA from an RE(using
// Brzozowski's construction). Most member functions are calls through to the
// corresponding RE members.
// DSRE inherits from RE for implementation.
class DSRE  :protected RE
{
public:
	// Must always have an argument-less constructor.
	inline DSRE();

	// A special constructor:
	inline DSRE(const RE& r);

	inline const DSRE& operator=(const DSRE& r);

	// The required member functions:
	inline int final() const;
	inline CRSet out_labels() const;
	inline DSRE out_transition(const CharRange a) const;
	inline int operator==(const DSRE& r) const;
	inline int operator!=(const DSRE& r) const;

	friend std::ostream& operator<<(std::ostream& os, const DSRE& r);
	
	inline int class_invariant() const;
};

// Must always have an argument-less constructor.
inline DSRE::DSRE() :RE()
{
	assert(class_invariant());
}

// A special constructor:
inline DSRE::DSRE(const RE& r) :RE(r)
{
	assert(r.class_invariant());
	// They must always be in similarity normal form SNF(see deriv.cpp)
	RE::snf();
	assert(class_invariant());
}

inline const DSRE& DSRE::operator=(const DSRE& r)
{
	assert(r.class_invariant());
	RE::operator=(r);
	assert(class_invariant());
	return(*this);
}

// The required member functions:
inline int DSRE::final() const
{
	assert(class_invariant());
	return(RE::Null());
}

inline CRSet DSRE::out_labels() const
{
	assert(class_invariant());
	return(RE::First());
}

inline DSRE DSRE::out_transition(const CharRange a) const
{
	assert(class_invariant());
	return(RE::derivative(a));
}

inline int DSRE::operator==(const DSRE& r) const
{
	assert(class_invariant() && r.class_invariant());
	return(RE::operator==(r));
}

inline int DSRE::operator!=(const DSRE& r) const
{
	return(!operator==(r));
}

inline int DSRE::class_invariant() const
{
	return(RE::class_invariant() && RE::in_snf());
}

