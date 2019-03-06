/************************************************************************************
 The Σ-algebra
	Template class Reg is used to define a client interface for the regular Σ-algebra (which is fully
	defined in [Wat93a, Section 3]). The template takes a single type parameter T which is used as
	the carrier set of the Σ-algebra. Class Reg<T> derives publicly from T, and so an Reg<T> can
	be used anywhere that a T can. The following member functions are provided:

	For any two carrier sets Tl and T2 , the Sigma-algebra operator definitions will have very little in
	common. For this reason, the operators of template class Reg are specially defined defined for
	each carrier set. Presently, the operators are only defined for three type parameters (carrier sets):
	Reg<RE>, Reg<FA>, and Reg<RFA>. (see files Sig-RE.cpp, Sig-FA.cpp, and Sig-RFA.cpp).

Implementation class: Reg
Files: Sigma.h
Uses: CharRange, RE, REops

Description: Reg implements the Σ-algebra as defined in [Wat93a, Section 3]. The single type
(or generic) parameter T is used to specify the carrier set of the Σ-algebra. The template Reg
is an abstract template, in the sense that it is only used to force a common interface between
the Σ-algebras. Most of the member functions are left undefined, with versions specific to the
carrier set being defined separately (see files Sig-re.cpp, Sig-fa.cpp, and Sig-rfa.cpp).
Regular expressions (class RE) are taken as the Σ-term algebra. 
A special member function is defined, taking a regular expression, and constructing the homomorphic image of the RE,
in the Σ-algebra of T. The Σ-algebra is the only way to construct regular expressions, and
it is particularly useful for constructing parts of a finite automaton separately. 
Reg<T> inherits publicly from a T, and since a Reg<T> contains nothing extra, it can be cast to a T
safely (no slicing occurs, and no information is lost). 
Presently, only Reg<RE>, Reg<FA>,and Reg<RFA> are available. (Each of RE, FA, and RFA also have constructors taking
a const reference to RE; for practical purposes, these constructors are much faster than
constructing the homomorphic image using Reg.)

Implementation: The template is used to force a common interface for Σ-algebras with different
carrier sets. Forcing an interface is commonly done using abstract base classes, although
this is not possible in this case, as the return types of many of the member functions would
not be correct.

Performance: The homomorphic image member function is recursive, and keeps partially constructed
results in local variables. Use-counting in the carrier class can improve performance.

===========================================================================================
Reg<RE>: (in Sig-RE.cpp)  Class RE is a regular expression(see[Wat93a, Section 3]
non-basis operator(epsilon,empty,symbol): this ==> left = right = 0
unary operator(star,plus,question): this ==> left = this, right = 0
binary operator(union(or),concat(dot)): this ==> left(this) operator right
Reg<RE>& Reg<RE>::epsilon(); Reg<RE>& Reg<RE>::empty();Reg<RE>& Reg<RE>::symbol(const CharRange r);
Reg<RE>& Reg<RE>::Or(const Reg<RE>& r); Reg<RE>& Reg<RE>::concat(const Reg<RE>& r);
Reg<RE>& Reg<RE>::star();Reg<RE>& Reg<RE>::plus();Reg<RE>& Reg<RE>::question();
---------------------------------------------------------------------------------------------
Reg<FA>: (in Sig-FA.cpp)  Class FA implements finite automata as defined in [Wat93a, Definition 2.1]
Reg<FA>& Reg<FA>::epsilon(); Reg<FA>& Reg<FA>::empty();Reg<FA>& Reg<FA>::symbol(const CharRange r);
Reg<FA>& Reg<FA>::Or(const Reg<FA>& r); Reg<FA>& Reg<FA>::concat(const Reg<FA>& r);
Reg<FA>& Reg<FA>::star();Reg<FA>& Reg<FA>::plus();Reg<FA>& Reg<FA>::question();
---------------------------------------------------------------------------------------------
Reg<RFA>: (in Sig-RFA.cpp) Class RFA implements reduced finite automata, as defined in [Wat93a, Definition 4.24].
Reg<RFA>& Reg<RFA>::epsilon(); Reg<RFA>& Reg<RFA>::empty();Reg<RFA>& Reg<RFA>::symbol(const CharRange r);
Reg<RFA>& Reg<RFA>::Or(const Reg<RFA>& r); Reg<RFA>& Reg<RFA>::concat(const Reg<RFA>& r);
Reg<RFA>& Reg<RFA>::star();Reg<RFA>& Reg<RFA>::plus();Reg<RFA>& Reg<RFA>::question();
 ************************************************************************************/
//#pragma once


#ifndef AUTOMATA_SIGMA_H
#define AUTOMATA_SIGMA_H



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
// algebra Reg<T> of some regular expression. (Regular expressions are the Sigma-term algebra)

template<class T>
class Reg :public T {
public:
	// Some constructors

	// An argumentless constructor, a copy constructor, and an assignment operator 
	// (assuming that T has all three).Usually pass control back to the base class.
	Reg() :T()
	{ }

	// An argumentless constructor, a copy constructor, and an assignment operator 
	// (assuming that T has all three).Usually pass control back to the base class.
	Reg(const Reg<T>& r) :T(r)
	{ }

	// An argumentless constructor, a copy constructor, and an assignment operator 
	// (assuming that T has all three).Usually pass control back to the base class.
	inline const Reg<T>& operator=(const Reg<T>& r)
	{
		// Call through to the base-class's operato=
		T::operator=(r);
		return(*this);
	}

	// Construction 4.3 (Thompson): Thompson's construction is the (unique) homomorphism Th(The operators (with subscript Th, for Thompson))
	// from RE to Thompson's Sigma-algebra of FA's.
	// C(epsilon,Th),C(empty,Th),C(a,Th),C(.,Th([M0],[M1])),C(union,Th([M0],[M1])),C(star,Th([M])),C(star,Th([M])),C(plus,Th([M])),C(question,Th([M]))
	// Construct the homomorphic image of regular expression r, using the Sigma-algebra operators
	// (corresponding to the operators of the regular expression).
	// A constructor from RE (a regular expression). Given that regular expressions are the Sigma-term algebra, 
	// this constructor constructs the homomorphic image of the regular expression in the Sigma-algebra of T.
	// Definition 2.6 (Isomorphism of FA's)
	// Definition 3.7 (Sigma-homomorphism): Given E-a1gebras (V,F) and (W,G), a Sigma-homomorphism from(V, F) to(W, G)
	Reg(const RE& r)
	{
		assert(r.class_invariant());
		homomorphic_image(r);
		assert(T::class_invariant());
	}

	// Default destructor falls through to the ~T()

	// Now the Sigma-algebra signature:

	// Sigma-algebra basis
	// epsilon makes *this accept the empty word only.
	// ==> thist -> op = EPSILON, this->left = this->right = 0
	Reg<T>& epsilon();
	// empty makes *this accept the empty language.
	// ==> thist -> op = EMPTY, this->left = this->right = 0
	Reg<T>& empty();

	//symbol takes a CharRange and makes *this accept the set of chars denoted by the CharRange.
	// 与RE::symbol()同名，Reg<RE>对象仅能调用symbol(const CharRange r)函数
	// ==> thist -> op = SYMBOL, this->symbol = r, this->left = this->right = 0
	Reg<T>& symbol(const CharRange r);

	// Sigma-algebra binary ops,原文为or,与C++关键字冲突，改为Or
	// or takes another Reg<T> r, and makes *this accept the language of *this union the language of r.
	// ==> thist = (shallow_copy(this) union r)
	Reg<T>& Or(const Reg<T>& r);
	// concat takes another Reg<T> r, and makes *this accept the language of *this concatenated (on the right) with the language of r.  
	// ==> thist = (shallow_copy(this) concat r)
	Reg<T>& concat(const Reg<T>& r);

	// Sigma-algebra unary ops
	// star makes *this accept the Kleene closure of the language of *this.
	// ==> this->left = shallow_copy(this), this->op = STAR, this->right = 0;
	Reg<T>& star();

	// plus makes *this accept the plus closure of the language of *this.
	// in Sig-RE.cpp, define Reg<RE>, plus = question
	// ==> this->left = shallow_copy(this), this->op = PLUS, this->right = 0;
	Reg<T>& plus();

	// question adds the empty word (epsilon), to the language accepted by *this.
	// in Sig-RE.cpp, define Reg<RE>, plus = question
	// ==> this->left = shallow_copy(this), this->op = QUESTION, this->right = 0;
	Reg<T>& question();

protected:
	// Helper for constructing the homomorphic image of a regular expression.
	// (Can also be used as a type of copy constructor for RE's.)
	// T is carrier set: RE,FA,RFA，执行各自的操作，分别在Sig-RE.cpp,Sig-FA.cpp,Sig-RFA.cpp中定义
	inline void homomorphic_image(const RE& r);
};

// Helper for constructing the homomorphic image of a regular expression.
// Definition 3.7 (Sigma-homomorphism): Given E-a1gebras (V,F) and (W,G), a Sigma-homomorphism from(V, F) to(W, G)
// (Can also be used as a type of copy constructor for RE's.)
// T is carrier set: RE,FA,RFA，执行各自的操作，分别在Sig-RE.cpp,Sig-FA.cpp,Sig-RFA.cpp中定义
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


#endif // !AUTOMATA_SIGMA_H
