/**********************************************************************************
	Implementation class : DTransRel
	Files : dtransre.h, dtransre.cpp
	Uses : CharRange, CRSet, DTrans, State, StateSet, StateTo RELATIONS
	Description : A DTransRel maps a State and a character(or a CharRange) to a State.It is used
	to implement the deterministic transition relation in the class DFA(see[Wat93a, Property 2.25]).
	The domain of the relation must be maintained explicitly by the client.Transitions
	can be added to the relation, but not removed.The client must ensure that the relation
	remains deterministic.
****************************************************************************************/
#pragma once
#include<iostream>
// 去下行注释则禁用 assert()
// #define NDEBUG
#include <cassert>  // 必须包含
#include "DTrans.h"
#include "StateTo.h"

// Implement a deterministic transition relation, as a function from States time
// char to State.This is used for transition relations in DFA's.
class DTransRel :public StateTo<DTrans>
{
public:
	// Constructors, destructors, operator= :
	
	// Argument-less constructor:
	inline DTransRel();

	inline DTransRel(const DTransRel& r);
	
	// Default destructor is okay :
	
	inline const DTransRel& operator=(const DTransRel& r);
	
	// Some relational operators :
	
	// Compute the image of r, and a under *this. [image = T(r,a)]
	inline State image(const State r, const char a) const;
	
	// Compute the image of r, and CharRange it under *this.
	inline State transition_on_range(const State r, const CharRange a) const;
	
	// Compute the reverse transition on a range under *this:
	StateSet reverse_transition(const State r, const CharRange a) const;

	// What are the transition labels between some State rand StateSet s?
	inline CRSet labels_between(const State r, const StateSet& s) const;

	// Given State r, what are the labels on transitions out of r?
	inline CRSet out_labels(const State r) const;

	// What are all States reverse reachable from r?
	StateSet reverse_closure(const StateSet& r) const;
	
	// Some functions updating *this:
	inline DTransRel& add_transition(const State p, const CharRange a, const State q);

	// Some domain members:
	// What is the domain of this relation.
	inline int domain() const;
	
	// Change the domain of this relation.
	inline void set_domain(const int r);
	
	// Recycle this entire structure.
	void reincarnate();
	
	// Some special members:
	friend std::ostream& operator<<(std::ostream& os, const DTransRel& r);

	inline int class_invariant() const;
};

// Argument-less constructor:
inline DTransRel::DTransRel() :StateTo<DTrans>()
{
	assert(class_invariant());
}

inline DTransRel::DTransRel(const DTransRel& r) :StateTo<DTrans>(r)
{
	assert(class_invariant());
}

inline const DTransRel& DTransRel::operator=(const DTransRel& r)
{
	assert(r.class_invariant());
	// Call back to the base class
	StateTo<DTrans>::operator=(r);
	assert(class_invariant());
	return(*this);
}

// Compute the image of r, and a under *this. [image = T(r,a)]
inline State DTransRel::image(const State r, const char a) const
{
	assert(class_invariant());
	assert(0 <= r && r < domain());
	return(lookup(r)[a]);
}

// Compute the image of r, and CharRange it under *this.
inline State DTransRel::transition_on_range(const State r, const CharRange a) const
{
	assert(class_invariant());
	assert(0 <= r && r < domain());
	return(lookup(r).range_transition(a));
}

// What are the transition labels between some State rand StateSet s?
inline CRSet DTransRel::labels_between(const State r, const StateSet& s) const
{
	assert(class_invariant());
	assert(s.class_invariant());
	assert(domain() == s.domain());
	assert(0 <= r && r <= domain());
	return(lookup(r).labels_into(s));
}

// Given State r, what are the labels on transitions out of r?
inline CRSet DTransRel::out_labels(const State r) const
{
	assert(class_invariant());
	return(lookup(r).out_labels());
}

// Some functions updating *this:
inline DTransRel& DTransRel::add_transition(const State p, const CharRange a, const State q)
{
	assert(class_invariant());
	map(p).add_transition(a, q);
	assert(class_invariant());
	return(*this);
}

// Some domain members :
// What is the domain of this relation.
inline int DTransRel::domain() const
{
	return(StateTo<DTrans>::domain());
}

// Change the domain of this relation.
inline void DTransRel::set_domain(const int r)
{
	assert(class_invariant());
	StateTo<DTrans>::set_domain(r);
	assert(class_invariant());
}

inline int DTransRel::class_invariant() const
{
	// First,we must satisfy the base class_invariant();
	int i(StateTo<DTrans>::class_invariant());
	for (int k = 0; k < domain() && i; k++)
	{
		i = i && lookup(k).class_invariant();
	}
	return(i);
}

// Some special members:
inline std::ostream& operator<<(std::ostream& os, const DTransRel& r)
{
	assert(r.class_invariant());
	return(operator<<(os, (const StateTo<DTrans>&)r));
}
