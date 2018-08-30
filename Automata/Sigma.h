/************************************************************************************
 The Σ-algebra
	The Σ-algebra (as defined in [Wat93a, Section 3]) is defined as a template class.
Implementation class: Reg
Files: Sigma.h
Uses: CharRange, RE, REops

Description: Reg implements the Σ-algebra as defined in [Wat93a, Section 3]. The single type
(or generic) parameter T is used to specify the carrier set of the Σ-algebra. The template Reg
is an abstract template, in the sense that it is only used to force a common interface between
the Σ-algebras. Most of the member functions are left undefined, with versions specific to the
carrier set being defined separately (see files Sig-re.cpp, Sig-fa.cpp, and Sig-rfa.cpp).
Regular expressions (class RE) are taken as the Σ-term algebra. A special member function
is defined, taking a regular expression, and constructing the homomorphic image of the RE,
in the Σ-algebra of T. The Σ-algebra is the only way to construct regular expressions, and
it is particularly useful for constructing parts of a finite automaton separately. Reg< T>
inherits publicly from a T, and since a Reg< T> contains nothing extra, it can be cast to a T
safely (no slicing occurs, and no information is lost). Presently, only Reg<RE>, Reg<FA>,
and Reg<RFA> are available. (Each of RE, FA, and RFA also have constructors taking
a const reference to RE; for practical purposes, these constructors are much faster than
constructing the homomorphic image using Reg.)

Implementation: The template is used to force a common interface for Σ-algebras with different
carrier sets. Forcing an interface is commonly done using abstract base classes, although
this is not possible in this case, as the return types of many of the member functions would
not be correct.

Performance: The homomorphic image member function is recursive, and keeps partially constructed
results in local variables. Use-counting in the carrier class can improve performance.
 ************************************************************************************/
#pragma once
#include<iostream>
 // 去下行注释则禁用 assert()
 // #define NDEBUG
#include <cassert>  // 必须包含
#include "CharRange.h"
#include "REops.h"
#include "RE.h"

// The signature of the Sigma-algebra is defined as template Reg. It is only
// an interface template, with most of the member functions being filled in as
// specialized versions. Given class T, the class Reg<T> is a Sigma-algebra with
// T as the carrier set. Reg is the only template required, since the regular
// expression Sigma algebra only has one sort : Reg.
// The Reg of a class T is also publicly derived from T, meaning that once
// a Reg<T> is constructed (perhaps using the Sigma-algebra operators), it can
// be used as a regular T(without slicing).
// A special constructor is provided, which constructs the homomorphic image in
// algebra Reg<T> of some regular expression. (Regular expressions are the Sigma-term algebra')

template<class T>
class Reg :public T {
public:
	// Some constructors. Usually pass control back to the base class.
	Reg() :T()
	{ }

	Reg(const Reg<T>& r) :T(r) // Just pass back to the base class
	{ }

	// Construct the homomorphic image of regular expression using the Sigma-algebra 
	// operators(corresponding to the operators of the regular expression).
	Reg(const RE& r)
	{
		assert(r.class_invariant());
		homomorphic_image(r);
		assert(T::class_invariant());
	}
	
	// Default destructor falls through to the ~T()

	inline const Reg<T>& operator=(const Reg<T>& r) 
	{
		// Call through to the base-class's operato=
		T::operator=(r);
		return(*this);
	}

	// Now the Sigma-algebra signature:

	// Sigma-algebra basis
	Reg<T>& epsilon();
	Reg<T>& empty();
	Reg<T>& symbol(const CharRange r);
	
	// Sigma-algebra binary ops,原文为or,与C++关键字冲突，改为Or
	Reg<T>& Or(const Reg<T>& r);
	Reg<T>& concat(const Reg<T>& r);
	
	// Sigma-algebra unary ops
	Reg<T>& star();
	Reg<T>& plus();
	Reg<T>& question();

protected:
	// Helper for constructing the homomorphic image of a regular expression.
	// (Can also be used as a type of copy constructor for RE's.)
	inline void homomorphic_image(const RE& r);
};

// Helper for constructing the homomorphic image of a regular expression.
// (Can also be used as a type of copy constructor for RE's.)
template<class T>
void Reg<T>::homomorphic_image(const RE& r)
{
	assert(r.class_invariant());

	// Construct the homomorphic image of r in *this.
	switch (r.root_operator())
	{
	case EMPTY:
		// Default constuctor T() should already leave *this accepting the empty language.
		// The following call is redundant.
		empty();
		break;
	case EPSILON:
		// Make *this accept epsilon.
		epsilon();
		break;
	case SYMBOL:
		// Make *this accept the specified symbol.
		symbol(r.symbol());
		break;
	case OR:
		// First make *this accept the language of the left side of the OR
		// by constructing a T for the right subexpression.
		homomorphic_image(r.left_subexpr());
		// Make *this accept the (left or right) language.
		Or(Reg<T>(r.right_subexpr())); 
		break;
	case CONCAT:
		// See OR case
		homomorphic_image(r.left_subexpr());
		concat(Reg<T>(r.right_subexpr()));
		break;
	case STAR:
		// See OR case
		homomorphic_image(r.left_subexpr());
		star();
		break;
	case PLUS:
		// See OR case
		homomorphic_image(r.left_subexpr());
		plus();
		break;
	case QUESTION:
		// See OR case
		homomorphic_image(r.left_subexpr());
		question();
		break;
	}
}
