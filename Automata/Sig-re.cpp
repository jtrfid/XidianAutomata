/************************************************************************
	The ¦²-term algebra Reg<RE>
	Implementation class: Reg<RE>
	Files: Sig-re. cpp
	Uses: CharRange, Reg, RE, REops
	Description: The template instantiation Reg<RE> can be used to construct regular expressions
	(see the documentation on template class Reg(in Sigma.h)).
	Implementation: The implementation consists of straight-forward expression tree manipulations.
	The implementation of RE is declared protected to give Reg<RE> access to it.
	Performance: These member functions would benefit from use-counting of class RE.
 ************************************************************************/
#include "stdafx.h"
#include "CharRange.h"
#include "RE.h"
#include "REops.h"
#include "Sigma.h"

// Implementations of the Sigma-algebra operators, with RE as the carrier.
// This is the Sigma-term algebra(see the Taxonomy, Section 3).

Reg<RE>& Reg<RE>::epsilon() {
	// This may have been something in a previous life.
	reincarnate();
	set_root_operator(EPSILON);
	assert(class_invariant());
	return(*this);
}

Reg<RE>& Reg<RE>::empty() {
	// See epsilon() case.
	reincarnate();
	set_root_operator(EMPTY);
	assert(class_invariant());
	return(*this);
}

Reg<RE>& Reg<RE>::symbol(const CharRange r) {
	// See epsilon case.
	reincarnate();
	set_root_operator(SYMBOL);
	set_symbol(r);
	assert(class_invariant());
	return(*this);
}
Reg<RE>& Reg<RE>::Or(const Reg<RE>& r) {
	assert(class_invariant());
	assert(r.class_invariant());
	RE *const lft(new RE);
	// Make a copy of *this.
	shallow_copy(lft);
	RE *const rt(new RE(r));
	op = OR;
	left = lft;
	right = rt;
	assert(class_invariant());
	return(*this);
}

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