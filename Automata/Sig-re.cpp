/************************************************************************
	The Σ-term algebra Reg<RE>
	Implementation class: Reg<RE>
	Files: Sig-RE.cpp
	Uses: CharRange, Reg, RE, REops
	Description: The template instantiation Reg<RE> can be used to construct regular expressions
	(see the documentation on template class Reg(in Sigma.h)).
	Implementation: The implementation consists of straight-forward expression tree manipulations.
	The implementation of RE is declared protected to give Reg<RE> access to it.
	Performance: These member functions would benefit from use-counting of class RE.

	no-basis operator(epsilon,empty,symbol): this ==> left = right = 0
	unary operator(star,plus,question): this ==> left = this, right = 0
	binary operator(union(or),concat): this ==> left(this) operator right
 ************************************************************************/
#include "stdafx.h"
#include "CharRange.h"
#include "RE.h"
#include "REops.h"
#include "Sigma.h"

// Implementations of the Sigma-algebra operators, with RE as the carrier.
// This is the Sigma-term algebra(see the Taxonomy, Section 3).

// epsilon makes *this accept the empty word only.
// ==> thist -> op = EPSILON, this->left = this->right = 0
Reg<RE>& Reg<RE>::epsilon() {
	// This may have been something in a previous life.
	reincarnate();
	set_root_operator(EPSILON);
	assert(class_invariant());
	return(*this);
}

// empty makes *this accept the empty language.
// ==> thist -> op = EMPTY, this->left = this->right = 0
Reg<RE>& Reg<RE>::empty() {
	// See epsilon() case.
	reincarnate();
	set_root_operator(EMPTY);
	assert(class_invariant());
	return(*this);
}

//symbol takes a CharRange and makes *this accept the set of chars denoted by the CharRange.
// ==> thist -> op = SYMBOL, this->symbol = r, this->left = this->right = 0
Reg<RE>& Reg<RE>::symbol(const CharRange r) {
	// See epsilon case.
	reincarnate();
	set_root_operator(SYMBOL);
	set_symbol(r);
	assert(class_invariant());
	return(*this);
}

// or takes another Reg<T> r, and makes *this accept the language of *this union the language of r.
// ==> thist = (shallow_copy(this) union r)
Reg<RE>& Reg<RE>::Or(const Reg<RE>& r) {
	assert(class_invariant());
	assert(r.class_invariant());
	RE *const lft(new RE);
	// Make a copy of *this into lft.
	shallow_copy(lft);
	RE *const rt(new RE(r));
	op = OR;
	left = lft;
	right = rt;
	assert(class_invariant());
	return(*this);
}

// concat takes another Reg<T> r, and makes *this accept the language of *this concatenated
// (on the right) with the language of r.
// ==> thist = (shallow_copy(this) concat r)
Reg<RE>& Reg<RE>::concat(const Reg<RE>& r) {
	assert(class_invariant());
	assert(r.class_invariant());
	RE *const lft(new RE);
	shallow_copy(lft);
	RE *const rt(new RE(r));
	op = CONCAT;
	left = lft;
	right = rt;
	assert(class_invariant());
	return(*this);
}

// star makes *this accept the Kleene closure of the language of *this.
// ==> this->left = shallow_copy(this), this->op = STAR, this->right = 0;
Reg<RE>& Reg<RE>::star() {
	assert(class_invariant());
	RE *const d(new RE);
	shallow_copy(d);
	op = STAR;
	left = d;
	right = 0;
	assert(class_invariant());
	return(*this);
}

// plus makes *this accept the plus closure of the language of *this.
// in Sig-RE.cpp, define Reg<RE>, plus = question
// ==> this->left = shallow_copy(this)), this->op = PLUS, this->right = 0;
Reg<RE>& Reg<RE>::plus()
{
	assert(class_invariant());
	RE *const d(new RE);
	shallow_copy(d);
	op = PLUS;
	left = d;
	right = 0;
	assert(class_invariant());
	return(*this);
}

// question adds the empty word (epsilon), to the language accepted by *this.
// in Sig-RE.cpp, define Reg<RE>, plus = question
// ==> this->left = shallow_copy(this), this->op = QUESTION, this->right = 0;
Reg<RE>& Reg<RE>::question() {
	assert(class_invariant());
	RE *const d(new RE);
	shallow_copy(d);
	op = QUESTION;
	left = d;
	right = 0;
	assert(class_invariant());
	return(*this);
}