/************************************************************************************
	Implementation class : RE
	Files : RE.h, RE.cpp
	Uses : CharRange, CRSet, REops
	Description : An RE is a regular expression(see[Wat93a, Section 3] for the definition of regular
		expressions).The argument-less constructor constructs the regular expression φ(the regular
		expression denoting the empty language).It is not possible to construct more complex regular
		expressions with the member functions(see the template class Reg<RE> for information
		on constructing regular expressions).Class RE is the implementation of the carrier set of
		the Σ-term algebra(an RE is a term in the Σ-term algebra).
		A member function returns the operator type of the main(or root) operator of the regular
		expression. (The operator types are enumerated in REops.) Other member functions can
		be used to determine additional information about the main(root) operator of the regular
		expression: the associated CharRange (for a SYMBOL basis operator), and the subexpressions
		(for non-basis[epsilon,empty,symbol], binary[union(or),concat] and unary[star,plus,question] operators). 
		A very basic istream extraction (input) operator is provided, expecting the input to be 
		a regular expression in prefix notation; the operator does little error checking.

		non-basis operator(epsilon,empty,symbol): this ==> left = right = 0
		unary operator(star,plus,question): this ==> left = this, right = 0
		binary operator(union(or),concat(dot)): this ==> left(this) operator right
******************************************************************************************/
#pragma once
#include<iostream>
// 去下行注释则禁用 assert()
// #define NDEBUG
#include <cassert>  // 必须包含
#include "CharRange.h"
#include "CRSet.h"
#include "REops.h"

// Regular expressions.
// This class is not too useful for actually constructing them(for that, see
// the Sigma-algebra class in Sigma.h). Class RE functions as the terms of the
// Sigma-term algebra.Some members for manipulating them are provided.
class RE
{
public:
	// Some constructors, destructors, and operator=:

	// By default, create the RE denoting the empty language.
	inline RE();

	RE(const RE& e);

	virtual ~RE();

	const RE& operator = (const RE& e);

	// Some basic access member functions:

	// How many SYMBOL nodes in this regular expression?
	// Mainly for use in constructing RFA's.
	int num_symbols() const;

	// How many operators in this RE?
	// Used in ISImpl(the item set stuff).
	int num_operators() const;

	// What is the main operator of this regular expression?
	// op = r
	inline REops root_operator() const;

	// What is the CharRange of this RE, if it is a SYMBOL regular expression.
	inline CharRange symbol() const;

	// What is the left RE of this RE operator (if it is a higher operator).
	// Assume that *this is higher(non-basis) regular operator.
	inline const RE& left_subexpr() const;

	// What is the right RE of this RE operator (if it a binary operator).
	inline const RE& right_subexpr() const;

	//////////////////////////////////////////////////  Those methd's implementation is in deriv.cpp
	// Some derivatives(Brzozowski's) related member functions:
	// Does *this accept epsilon?
	// This is from Definition 3.20 and Property 3.21
	int Null() const;

	// What is the First of *this?
	// This is from Definition 4.60
	CRSet First() const;

	//Is *this in similarity normal form(SNF) ?
	int in_snf() const;

	// Put *this into similarity normal form.
	RE& snf();

	//Reduce(optimize) *this by removing useless information.
	RE& reduce();

	// What is the derivative of *this (w.r.t. r)
	RE derivative(const CharRange& r) const;

	// Some ordering members(largely used in similarity and comparisons)
	int ordering(const RE& r) const;
	///////////////////////////////////////////////////

	// Some comparisons:
	inline int operator==(const RE& r) const;
	inline int operator!=(const RE& r) const;
	inline int operator<(const RE& r) const;
	inline int operator>=(const RE& r) const;
	inline int operator>(const RE& r) const;
	inline int operator<=(const RE& r) const;

	// Some extras:
	friend std::ostream& operator<<(std::ostream& os, const RE& r);
	friend std::istream& operator>>(std::istream& is, RE& r);
	inline int class_invariant() const;

protected:
	//////////// Some protected helpers, mainly for Reg<RE>:

	// set the main operator of this regular expression?
	// op = r
	inline void set_root_operator(REops r);

	// set symbol (a1,...,an) of this regular expression?
	inline void set_symbol(const CharRange r);

	// Make a copy of *this into *r
	void shallow_copy(RE *const r) const;

	// recycle
	// op = EMPTY, left = right = 0
	void reincarnate();

	////////////////////////////////////////////// Those methd's implementation is in deriv.cpp
	// Put *this into OR normal form(ONF) (used in the snf functions)
	RE& onf();

	// Destroy node *r, moving its data into *this.
	void assimilate_node(RE *const r);
	////////////////////////////////////////////

	// Some implementation details.

	// a set of several constants: ε,φ,a1,...,an; Reg(where V = {al, ... ,an }),
	// and five operators · : Reg x Reg--> Reg(the dot operator), U : Reg x Reg--> Reg, *: Reg--> Reg,
	//	+: Reg----> Reg, and ? : Reg----> Reg.
	REops op;

	// non-basis operator(epsilon, empty, symbol) : this == > left = right = 0
	// unary operator(star, plus, question) : this == > left = this, right = 0
	// binary operator(union(or), concat(dot)) : this == > left(this) operator right
	RE *left, *right;

	// symbol: a1,...,an in this RE
	CharRange sym;
};

// By default, create the RE denoting the empty language.
RE::RE() :op(EMPTY),left(0),right(0)
{
	assert(class_invariant());
}

// What is the main operator of this regular expression?
inline REops RE::root_operator() const
{
	return(op);
}

// What is the CharRange of this RE, if it is a SYMBOL regular expression.
inline CharRange RE::symbol() const
{
	assert(op == SYMBOL);
	return(sym);
}

// What is the left RE of this RE operator (if it is a higher operator).
// Assume that *this is higher(non-basis) regular operator.
// left RE of unary operator: *,+,? operator
inline const RE& RE::left_subexpr() const
{
	assert(op != EMPTY && op != EPSILON && op != SYMBOL);
	return(*left);
}

// What is the right RE of this RE operator (if it a binary operator).
inline const RE& RE::right_subexpr() const
{
	assert(op == OR || op == CONCAT);
	return(*right);
}

// Some comparisons:
inline int RE::operator==(const RE& r) const
{
	return(ordering(r) == 0);
}
inline int RE::operator!=(const RE& r) const
{
	return(ordering(r) != 0);
}
inline int RE::operator<(const RE& r) const
{
	return(ordering(r) < 0);
}
inline int RE::operator>=(const RE& r) const
{
	return(ordering(r) >= 0);
}
inline int RE::operator>(const RE& r) const
{
	return(ordering(r) > 0);
}
inline int RE::operator<=(const RE& r) const
{
	return(ordering(r) <= 0);
}

// Some extras:
inline int RE::class_invariant() const
{
	switch (op)
	{
	case EPSILON:
	case EMPTY:
	case SYMBOL:
		return(left == 0 && right == 0);
	case OR:
	case CONCAT:
		return(left != 0 && right != 0 && left_subexpr().class_invariant()
			&& right_subexpr().class_invariant());
	case STAR:
	case PLUS:
	case QUESTION:
		return(left != 0 && right == 0 && left_subexpr().class_invariant());
	default:
		return(0);
	}
}

// Some protected helpers, mainly for Reg<RE>:
inline void RE::set_root_operator(REops r)
{
	// No class assertion here,since *this is still being constructed.
	op = r;
}
inline void RE::set_symbol(const CharRange r)
{
	assert(op == SYMBOL);
	sym = r;
}

