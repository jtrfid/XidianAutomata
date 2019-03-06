/****************************************************************************
	Implementation class: SymRel
	Files: SymRel.h, SymRel.cpp
	Uses: State, StateSet, StateRel
	Description: A SymRel is a binary symmetrical relation on States. They are used mainly in
	DFA minimization algorithms. Member functions are provided to add and remove pairs of
	States from the relation, as well as to test for membership in the relation.
****************************************************************************/
//#pragma once


#ifndef AUTOMATA_SYMREL_H
#define AUTOMATA_SYMREL_H


#include<iostream>
// 去下行注释则禁用 assert()
// #define NDEBUG
#include <cassert>  // 必须包含
#include "State.h"
#include "StateSet.h"
#include "StateRel.h"

// Implement symmetrical binary relations on States.Class SymRel inherits from
// StateRel for implementation.
class SymRel :protected StateRel
{
public:
	// Constructors etc.
	inline SymRel();
	inline SymRel(const SymRel& r);

	inline const SymRel& operator=(const SymRel& r);

	// Some relation operators.

	// Make *this into the identity relation.
	SymRel& identity();

	// What is the image of a State under *this
	inline const StateSet& image(const State p) const;

	// Add a pair of States.
	inline SymRel& add_pair(const State p, const State q);
	inline SymRel& add_pairs(const StateSet& P, const StateSet& Q);

	// Remove a pair of States.
	inline SymRel& remove_pair(const State p, const State q);
	inline SymRel& remove_pairs(const StateSet& P, const StateSet& Q);

	// Are a pair of States present?
	inline int contains_pair(const State p, const State q) const;

	// Complement *this.
	SymRel& complement();

	// Some domain related members.
	inline int domain() const;
	inline void set_domain(const int r);

	// Special members.
	friend std::ostream& operator<<(std::ostream& os, const SymRel& r);

	inline int class_invariant() const;
};

// Constructors etc.
inline SymRel::SymRel() :StateRel()
{
	assert(class_invariant());
}

inline SymRel::SymRel(const SymRel& r) : StateRel(r)
{
	assert(class_invariant());
}

inline const SymRel& SymRel::operator=(const SymRel& r)
{
	assert(r.class_invariant());
	StateRel::operator=(r);
	assert(class_invariant());
	return(*this);
}

// What is the image of a State under *this
inline const StateSet& SymRel::image(const State p) const
{
	assert(class_invariant());
	return(StateRel::image(p));
}

// Add a pair of States.
inline SymRel& SymRel::add_pair(const State p, const State q)
{
	assert(class_invariant());
	StateRel::union_cross(p, q);
	StateRel::union_cross(q, p);
	assert(class_invariant());
	return(*this);
}
inline SymRel& SymRel::add_pairs(const StateSet& P, const StateSet& Q)
{
	assert(class_invariant());
	StateRel::union_cross(P, Q);
	StateRel::union_cross(Q, P);
	assert(class_invariant());
	return(*this);
}

// Remove a pair of States.
inline SymRel& SymRel::remove_pair(const State p, const State q)
{
	assert(class_invariant());
	StateRel::remove_pair(p, q);
	StateRel::remove_pair(q, p);
	assert(class_invariant());
	return(*this);

}
inline SymRel& SymRel::remove_pairs(const StateSet& P, const StateSet& Q)
{
	assert(class_invariant());
	StateRel::remove_pairs(P, Q);
	StateRel::remove_pairs(Q, P);
	assert(class_invariant());
	return(*this);
}

// Are a pair of States present?
inline int SymRel::contains_pair(const State p, const State q) const
{
	assert(class_invariant());
	return(StateRel::image(p).contains(q));
}

// Some domain related members.
inline int SymRel::domain() const
{
	assert(class_invariant());
	return(StateRel::domain());
}
inline void SymRel::set_domain(const int r)
{
	StateRel::set_domain(r);
	assert(class_invariant());
}

inline int SymRel::class_invariant() const
{
	// This should also assert symmetry of the reation.
	return(StateRel::class_invariant());
}


#endif // !AUTOMATA_SYMREL_H
