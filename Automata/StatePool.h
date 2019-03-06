/************************************************************************
	Implementation class: StatePool
	Files: StatePool.h
	Uses: State
	Description: A StatePool is a dispenser of States (beginning with 0). A member function size()
	returns the number of States allocated so far. Two StatePools can be combined into one,
	with the result that the StatePool being combined into *this must be renamed to not clash
	with the States already allocated from *this.

	Implementation: An integer counter is maintained, indicating the next State to be allocated.
	The class is really too simple to have a class invariant.
 ************************************************************************/
//#pragma once



#ifndef AUTOMATA_STATEPOOL_H
#define AUTOMATA_STATEPOOL_H


#include<iostream>
 // 去下行注释则禁用 assert()
 // #define NDEBUG
#include <cassert>  // 必须包含
#include "State.h"

/*************************************************************************
	All states in an automaton are allocated from a StatePool. StatePool's can be
	merged together to form a larger one. (Care must be taken to rename any relations
	or sets (during merging) that depend on the one StatePool.)
	State is in [0,next)
 *************************************************************************/
class StatePool
{
public:
	// By default, start allocating states at 0:
	inline StatePool();

	// A copy-constructed StatePool starts at the same point.
	inline StatePool(const StatePool& r);

	// Default destructor and operator= are okay.

	// How many states are already allocated(one more than that last allocated one,
	// since it begins at 0).
	inline int size() const;

	// Incorporate another StatePool by making it disjoint.Anything
	// associated with the other pool must be renamed explicitly.
	inline StatePool& incorporate(const StatePool r);

	// Allocate a new state.
	inline State allocate();

	// Clear all states that were allocated; start again at O.
	inline StatePool& reincarnate();

	// Does this State Pool contain State r. i.e it's in [0,next)
	inline int contains(const State r) const;

	// Output a StatePool.
	friend std::ostream& operator<<(std::ostream& os, const StatePool& r);

private:
	// The next one to be allocated.
	int next;
};

// By default, start allocating states at 0:
inline StatePool::StatePool() :next(0)
{

}

// A copy-constructed StatePool starts at the same point.
inline StatePool::StatePool(const StatePool& r) :next(r.next)
{

}

// How many states are already allocated(one more than that last allocated one,
// since it begins at 0).
inline int StatePool::size() const
{
	return(next);
}

// Incorporate another StatePool by making it disjoint.Anything
// associated with the other pool must be renamed explicitly.
inline StatePool& StatePool::incorporate(const StatePool r)
{
	next += r.size();
	return(*this);
}

// Allocate a new state.
inline State StatePool::allocate()
{
	return(next++);
}

// Clear all states that were allocated; start again at O.
inline StatePool& StatePool::reincarnate()
{
	next = 0;
	return(*this);
}

// Does this State Pool contain State r. i.e it's in [0,next)
inline int StatePool::contains(const State r) const
{
	return(0 <= r && r < next);
}

// Output a StatePool.
inline std::ostream& operator<<(std::ostream& os, const StatePool& r)
{
	return(os << "[0," << r.next << ")");
}



#endif // !AUTOMATA_STATEPOOL_H
