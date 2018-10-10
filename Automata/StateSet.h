/************************************************************************
Implementation class: StateSet

Files: StateSet.h, StateSet.cpp

Uses: BitVec, State

Description: A StateSet is a set of States with a certain capacity. The capacity (called the
domain) is one more than the greatest State that the set can contain. It can easily be
enlarged, but it can only be shrunk (to zero) through the reincarnate member function.
   The maintainance of the domain is the responsibility of the client. Normal set operations are
available, including iterators.
   Most member functions taking another StateSet expect it to have the same domain as *this(with
catastrophic results if this is not true).
   The States in the set can also be renamed, so that they do not clash with the States of a certain StatePool.
It is possible to take the union of two StateSets containing States from different StatePools.
In this case, the States in the incoming StateSet are renamed during the union; this is done
with the disjointing_union member function.
 ************************************************************************/
#pragma once
#include<iostream>
 // 去下行注释则禁用 assert()
 // #define NDEBUG
#include <cassert>  // 必须包含
#include "State.h"
#include "BitVec.h"

/************************************************************************
	Implement a set of State's. Normal set operations are available. The StateSet
	is normally associated (implicitly) with a particular StatePool; whenever a StuteSet
	is to interact with another (from a different StatePool), its States must be renamed
	(to avoid a name clash). The capacity of a StateSet must be explicitly managed; many
	set operations are not bounds-checked when assert() is turned off.
 ************************************************************************/
class StateSet :protected BitVec
{
public:
	// Constructors, destructors, operator=;

	// Default constructor creates the emptyset, with little effort.
	// This assumes that delete[]0 a is okay.
	inline StateSet();

	// Normal copy constructor.
	inline StateSet(const StateSet& r);

	// Normal non-virtual destructor, default will call the base.

	// Needs a special operator=.
	inline const StateSet& operator=(const StateSet& r);

	// Tests :

	// A special equality operator.
	inline int operator == (const StateSet& r) const;

	// Inequality operator.
	inline int operator != (const StateSet& r) const;

	// Is this set empty?
	inline int empty() const;

	// What is the size of this set(cardinality) ?
	inline int size() const;

	// Set operators(may affect *this):

	// complement *this.
	inline StateSet& complement();

	// inserts a State.
	inline StateSet& add(const State r);

	// remove a State from the set.
	inline StateSet& remove(const State r);
	
	// Set union.
	inline StateSet& set_union(const StateSet& r);

	// Set intersection.
	inline StateSet& intersection(const StateSet& r);

	// Set difference
	inline StateSet& remove(const StateSet& r);

	// Set containment.
	inline int contains(const StateSet& r) const;

	// Is a State in the set?
	inline int contains(const State r) const;

	// Does this set have something in common with r?
	inline int not_disjoint(const StateSet& r) const;

	// Make this set the emptyset.
	inline void clear();

	// What is the smallest element of *this?
	inline State smallest() const;

	// Some domain related members:

	// How many States can this set contain?
	// [O, domain()) can be contained in *this.
	inline int domain() const;

	// set How many States can this set contain.
	// [O, domain()) can be contained in *this.
	inline void set_domain(const int r);

	// Recycle this StateSet.
	inline void reincarnate();

	// Rename the elements of this StateSet so that they don't fall within
	// StatePool r.
	inline StateSet& st_rename(const int r);

	// Include another State Set into this one, renaming all the States.
	inline StateSet& disjointing_union(const StateSet& r);

	// Iterators:

	// Place the first State in the iteration in reference r.
	// r == Invalid if there is no first one.
	inline State iter_start(State& r) const;

	// Is r the last State in an iteration sequence.
	inline int iter_end(State r) const;

	// Place the next State, after r(in the iteration sequence), in reference r.
	inline State iter_next(State& r) const;

	// Other special members :
	friend std::ostream& operator<<(std::ostream& as, const StateSet& r);

	// Structural invariant on the StateSet, just the class invariant of the base.
	inline int class_invariant() const;
};

// Default constructor creates the emptyset, with little effort.
// This assumes that delete[]0 a is okay.
inline StateSet::StateSet() :BitVec()
{

}

// Normal copy constructor.
inline StateSet::StateSet(const StateSet& r) :BitVec(r)
{

}

// Needs a special operator=.
inline const StateSet& StateSet::operator=(const StateSet& r)
{
	BitVec::operator=(r);
	return(*this);
}

// A special equality operator.
inline int StateSet::operator == (const StateSet& r) const
{
	return(BitVec::operator==(r));
}

// Inequality operator.
inline int StateSet::operator != (const StateSet& r) const
{
	return(!operator==(r));
}

// Is this set empty?
inline int StateSet::empty() const
{
	return(BitVec::something_set());
}

// What is the size of this set(cardinality) ?
inline int StateSet::size() const
{
	return(BitVec::bits_set());
}

// complement *this.
inline StateSet& StateSet::complement()
{
	assert(class_invariant());
	BitVec::bitwise_complement();
	assert(class_invariant());
	return(*this);
}

// inserts a State.
inline StateSet& StateSet::add(const State r)
{
	BitVec::set_bit(r);
	return(*this);
}

// remove a State from the set.
inline StateSet& StateSet::remove(const State r)
{
	BitVec::unset_bit(r);
	return(*this);
}

// Set difference
inline StateSet& StateSet::remove(const StateSet& r)
{
	BitVec::bitwise_unset(r);
	return(*this);
}

// Set union.
inline StateSet& StateSet::set_union(const StateSet& r)
{
	BitVec::bitwise_or(r);
	return(*this);
}

// Set intersection.
inline StateSet& StateSet::intersection(const StateSet& r)
{
	BitVec::bitwise_and(r);
	return(*this);
}

// Set containment.
inline int StateSet::contains(const StateSet& r) const
{
	return(BitVec::contains(r));
}

// Is a State in the set?
inline int StateSet::contains(const State r) const
{
	return(BitVec::contains(r));
}

// Does this set have something in common with r?
inline int StateSet::not_disjoint(const StateSet& r) const
{
	return(BitVec::something_common(r));
}

// Make this set the emptyset.
inline void StateSet::clear()
{
	BitVec::clear();
}

// What is the smallest element of *this?
inline State StateSet::smallest() const
{
	return(BitVec::smallest());
}

// How many States can this set contain?
// [O, domain()) can be contained in *this.
inline int StateSet::domain() const
{
	return(BitVec::width());
}

// set How many States can this set contain.
// [O, domain()) can be contained in *this.
inline void StateSet::set_domain(const int r)
{
	assert(r >= BitVec::width());
	BitVec::set_width(r);
}

// Recycle this StateSet.
inline void StateSet::reincarnate()
{
	BitVec::reincarnate();
}

// Rename the elements of this StateSet so that they don't fall within
// StatePool r.
inline StateSet& StateSet::st_rename(const int r)
{
	BitVec::left_shift(r);
	return(*this);
}

// Include another State Set into this one, renaming all the States.
inline StateSet& StateSet::disjointing_union(const StateSet& r)
{
	BitVec::append(r);
	return(*this);
}

// Place the first State in the iteration in reference r.
// r == Invalid if there is no first one.
inline State StateSet::iter_start(State& r) const
{
	return(BitVec::iter_start(r));
}

// Is r the last State in an iteration sequence.
inline int StateSet::iter_end(State r) const
{
	return(BitVec::iter_end(r));
}

// Place the next State, after r(in the iteration sequence), in reference r.
inline State StateSet::iter_next(State& r) const
{
	return(BitVec::iter_next(r));
}

// Structural invariant on the StateSet, just the class invariant of the base.
inline int StateSet::class_invariant() const
{
	// The Invalid stuff is a required definition.
	return(BitVec::class_invariant() && Invalid == -1);
}
