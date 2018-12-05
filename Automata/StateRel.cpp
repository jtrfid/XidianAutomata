/**********************************************************************************
	Implementation: StateRelinherits for implementation from StateTo<StateSet>. Many member
functions are simply calls to the corresponding member of StateTo. Member functions such
as reincarnate first reincarnates all of the StateSets, followed by the StateTo.
 **********************************************************************************/
#include "stdafx.h"
#include "StateRel.h"

// Compute(Lookup) the image of r under *this. precondition: this.domain() = r.domain()
// Note: map: states -> states(images)
StateSet StateRel::image(const StateSet& r) const
{
	assert(class_invariant() && r.class_invariant());
	assert(r.domain() == domain());
	// result is, by default,the emptyset.
	StateSet result;
	result.set_domain(domain());
	State st;
	for (r.iter_start(st); !r.iter_end(st); r.iter_next(st))
	{
		result.set_union(lookup(st));
	}
	return(result);
}

// Compute the reflexive and transitive closure of r under *this.
// return r union { image }, Note: map: states -> states(images)
StateSet StateRel::closure(const StateSet& r) const
{
	assert(class_invariant() && r.class_invariant());
	assert(r.domain() == domain());
	// Use an iterative method to compute the Kleene closure.
	StateSet result(r);
	StateSet intermediate(image(r));
	assert(intermediate.domain() == result.domain());
	while (!result.contains(intermediate))
	{
		result.set_union(intermediate);
		intermediate = image(result);
	}
	return(result);
}

// Member functions union_cross(A,B) makes *this the union (relation-wise) of *this 
// with A times B(Cartesian cross product).
// Map all members of S to st as well. precondition: this.domain() == S.domain(), st = [0,this.domain())
// S X {st}
StateRel& StateRel::union_cross(const StateSet& S, State st)
{
	assert(class_invariant());
	assert(S.class_invariant());
	assert(S.domain() == domain() && 0 <= st && st < domain());
	State i;
	for (S.iter_start(i); !S.iter_end(i); S.iter_next(i))
	{
		map(i).add(st);
	}
	assert(class_invariant());
	return(*this);
}

// Member functions union_cross(A,B) makes *this the union (relation-wise) of *this 
// with A times B(Cartesian cross product).
// Map A to B . precondition: this.domain() == A.domain() == B.domain()
// This could probably have made use of union_cross(State,StateSet).
// A X B
StateRel& StateRel::union_cross(const StateSet& A, const StateSet& B)
{
	assert(class_invariant());
	assert(A.class_invariant() && B.class_invariant());
	assert(A.domain() == domain() && B.domain() == domain());
	State i;
	for (A.iter_start(i); !A.iter_end(i); A.iter_next(i))
	{
		map(i).set_union(B);
	}
	assert(class_invariant());
	return(*this);
}

// Remove a pair of States from the relation.
StateRel& StateRel::remove_pairs(const StateSet& P, const StateSet& Q)
{
	assert(class_invariant());
	assert(P.domain() == domain());
	assert(Q.domain() == domain());
	State i;
	for (P.iter_start(i); !P.iter_end(i); P.iter_next(i))
	{
		map(i).remove(Q);
	}
	assert(class_invariant());
	return(*this);
}

// Clear out this relation, without changing the domain.
void StateRel::clear()
{
	assert(class_invariant());
	for (int i = 0; i < domain(); i++) map(i).clear();
	assert(class_invariant());
}

// Perform normal union of two relations.
// *this X r
StateRel& StateRel::set_union(const StateRel& r)
{
	assert(class_invariant() && r.class_invariant());
	assert(domain() == r.domain());
	State i;
	for (i = 0; i < r.domain(); i++) 
	{
		map(i).set_union(r.lookup(i));
		// Could also have been done with
		// union_cross(i,r.lkkoup(i));
	}
	assert(class_invariant());
	return(*this);
} 

// Change the domain of this relation.
void StateRel::set_domain(const int r)
{
	assert(class_invariant());
	assert(r >= domain());
	StateTo<StateSet>::set_domain(r);
	for (int i = 0; i < domain(); i++) map(i).set_domain(r);
	assert(class_invariant());
}

// Recycle this entire relation. domain() = 0
void StateRel::reincarnate()
{
	assert(class_invariant());
	for (int i = 0; i < domain(); i++) map(i).reincarnate();
	StateTo<StateSet>::reincarnate();
	assert(class_invariant());
}

// Union relation r into *this, while adjusting r.调整domain + r.domain, 确保无交集
StateRel& StateRel::disjointing_union(const StateRel& r)
{
	assert(class_invariant() && r.class_invariant());
	int olddom(domain());
	StateTo<StateSet>::disjointing_union(r); // 调整domain + r.domain, 确保无交集
	// domain() is the new one,olddom is the old one:
	assert(domain() == olddom + r.domain());

	// Just adjust the domains of those StateSet's that were already in *this.
	int i = 0;
	for (; i < olddom; i++) map(i).set_domain(domain());
	// Got to rename the incoming ones.
	for (; i < domain(); i++) map(i).st_rename(olddom);
	assert(class_invariant());
	return(*this);
}

// 修改为inline, 并在.h文件中定义，否则连接器找不到StateTo<StateRel>
//inline std::ostream& operator<<(std::ostream& os, const StateRel& r)
//{
//	assert(r.class_invariant());
//	return(os << (const StateTo<StateSet>&)r);
//}
