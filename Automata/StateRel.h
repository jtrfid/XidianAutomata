/****************************************************************************
	Implementation class: StateRel
	Files: StateRel.h, StateRel.cpp
	Uses: State, StateSet, StateTo
	Description: A StateRel is a binary relation on States. The class is used in the implementation
	of the ε-transition relation for class FA [Wat93a, Definition 2.1] and the follow relation
	[Wat93a, Definition 4.24] in classes RFA, LBFA and RBFA. Many relation operators are
	available, including taking the image of a State or a StateSet, and the star-closure of a
	StateSet. In order to easily construct StateRels, a member function union_cross is provided,
	which performs the following operation (where l, r are either States or StateSets):
	                            *this := *this ∪ (l x r)
	Standard union is available, as is disjointing_union which operates analogously to the member
	function in StateSet and StateTo (incoming States are renamed to avoid a collision). As with
	StateSet, the domain must be explicitly maintained by the client. Those member functions
	which take a StateSet or StateRel as parameter expect the parameter to have the same
	domain as *this.
****************************************************************************/
#pragma once
#include<iostream>
// 去下行注释则禁用 assert()
// #define NDEBUG
#include <cassert>  // 必须包含
#include "State.h"
#include "StateSet.h"
#include "StateTo.h"

// Implement binary relations on States.This is most often used for epsilon transitions
// and follow relations.
class StateRel :protected StateTo<StateSet>
{
public:
	// Constructors, destructors) operator=:
	
	// Default argument-less constructor calls to the base class.
	inline StateRel();
	
	// Copy constructor does too.
	inline StateRel(const StateRel& r);
	
	// Default destructor is okay
		
	inline const StateRel& operator=(const StateRel& r);
	
	// Some relational operators:
	
	// Compute the image of r under *this.
	StateSet image(const StateSet& r) const;
	
	// Or, compute the image of a single State.
	inline const StateSet& image(const State r) const;

	// Compute the reflexive and transitive closure of r under *this.
	StateSet closure(const StateSet& r) const;

	// Some functions updating *this:
	
	// Member functions union_cross(A,B) makes *this the union (relation-wise) of *this 
	// with A times B(Cartesian cross product).
	inline StateRel& union_cross(State p, State q);
	inline StateRel& union_cross(State st, const StateSet& S);
	StateRel& union_cross(const StateSet& S, State st);
	StateRel& union_cross(const StateSet& A, const StateSet& B);

	// Remove a pair of States from the relation.
	inline StateRel& remove_pair(const State p, const State q);
	StateRel& remove_pairs(const StateSet& P, const StateSet& Q);
	
	// Clear out this relation, without changing the domain.
	void clear();
	
	// Perform normal union of two relations.
	StateRel& set_union(const StateRel& r);
	
	// Some domain members:
	
	// What is the domain of this relation.
	inline int domain() const;
	
	// Change the domain of this relation.
	void set_domain(const int r);
	
	// Recycle this entire relation.
	void reincarnate();

	// Union relation r into *this, while adjusting r.
	StateRel& disjointing_union(const StateRel& r);
	
	// Some special members:

	// 修改为inline, 并在.h文件中定义，否则连接器找不到StateTo<StateRel>
	inline friend std::ostream& operator<<(std::ostream& os, const StateRel& r);
	
	inline int class_invariant() const;
};

// Default argument-less constructor calls to the base class.
inline StateRel::StateRel():
	StateTo<StateSet>()
{
	assert(class_invariant());
}

// Copy constructor does too.
inline StateRel::StateRel(const StateRel& r):
	StateTo<StateSet>(r)
{
	assert(class_invariant());
}

inline const StateRel& StateRel::operator=(const StateRel& r)
{
	assert(r.class_invariant());
	// call back to the base class
	StateTo<StateSet>::operator=(r);
	assert(class_invariant());
	return(*this);
}

// Or, compute the image of a single State.
inline const StateSet& StateRel::image(const State r) const
{
	assert(class_invariant());
	assert(0 <= r && r < domain());
	// call back to the base class
	return(lookup(r));
}

// Member functions union_cross(A,B) makes *this the union (relation-wise) of *this 
// with A times B(Cartesian cross product).
inline StateRel& StateRel::union_cross(State p, State q)
{
	assert(class_invariant());
	assert(0 <= p && p < domain());
	map(p).add(q);
	assert(class_invariant());
	return(*this);
}

// Map a st also to StateSet S.
inline StateRel& StateRel::union_cross(State st, const StateSet& S)
{
	assert(class_invariant());
	assert(S.class_invariant());
	assert(0 <= st && st < domain() && S.domain() == domain());
	map(st).set_union(S);
	assert(class_invariant());
	return(*this);
}

// Remove a pair of States from the relation.
inline StateRel& StateRel::remove_pair(const State p, const State q)
{
	assert(class_invariant());
	assert(0 <= p && p < domain());
	assert(0 <= q && q < domain());
	map(p).remove(q);
	map(q).remove(p);
	assert(class_invariant());
	return(*this);
}

// What is the domain of this relation.
inline int StateRel::domain() const
{
	return(StateTo<StateSet>::domain());
}

inline int StateRel::class_invariant() const
{
	// First, we must satisfy the base class_invariant()
	int ret = StateTo<StateSet>::class_invariant();
	for (int i = 0; i < domain() && ret; i++)
	{
		ret = ret && lookup(i).class_invariant() && (lookup(i).domain() == domain());
	}
	return ret;
}

// 修改为inline, 并在.h文件中定义，否则连接器找不到StateTo<StateRel>
inline std::ostream& operator<<(std::ostream& os, const StateRel& r)
{
	assert(r.class_invariant());
	return(os << (const StateTo<StateSet>&)r);
}

