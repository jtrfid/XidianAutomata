/***********************************************************************
	Implementation: StateEqRelinherits for implementation from StateTo<StateSet *>. Two equivalent
States are mapped by the StateTo to pointers to the same StateSet.
 ***********************************************************************/
#include "stdafx.h"
#include "StateEqRel.h"


// Construct the total eq. relation of domain r.
StateEqRel::StateEqRel(const int r):StateTo<StateSet *>()
{ 
	StateTo<StateSet *>::set_domain(r);
	// Now construct a StateSet representing the total relation.
	StateSet *const t(new StateSet);
	t->set_domain(r);
	t->complement();
	for (State p = 0; p < r; p++)
	{
		StateTo<StateSet *>::map(p) = t;
	}
	// Do not delete t!! // 没有删除，外部调用，使用完要删除
	assert(class_invariant());
}

// Make two States equivalent:
StateEqRel& StateEqRel::equivalize(const State p, const State q)
{
	assert(class_invariant());
	if (!equivalent(p, q))
	{
		// This is dangerous if they point to the same thing.
		assert(lookup(p) != lookup(q));
		// Include q's eq. class in p's
		map(p)->set_union(*lookup(q));

		// Get q's eq. class relating to the p's
		StateSet *oldq(lookup(q));
		StateSet *newp(lookup(p));
		assert(oldq != newp);
		State i;
		for (oldq->iter_start(i); !oldq->iter_end(i); oldq->iter_end(i))
		{
			map(i) = newp;
		}
		assert(equivalent(p, q));
		delete oldq;
		assert(lookup(p) == lookup(q));
	}
	assert(class_invariant());
	return(*this);
}

// Split an equivalence class into two(assuming that r is entirely contained in a class):
StateEqRel& StateEqRel::split(const StateSet& r)
{
	assert(class_invariant());
	assert(domain() == r.domain());
	// Only split it if there's actually some splitting to do.
	// Chose first State in r for starers.
	State(i);
	r.iter_start(i);
	// Only do the splitting if r is wholly contained in the eg. class of it's
	// smallest element, and if the splitting will actually produce a new eq. class.
	if (lookup(i)->contains(r) && *lookup(i) != r)
	{
		// Split it.
		// Make all of not(r)'s States equivalent.
		map(i)->remove(r);
		// Make all of r's States equivalent.
		// Build a new StateSet for the new class.
		StateSet *n(new StateSet(r));  // 何处delete n; // 外部调用，使用完要删除，也可能在父类的析构函数中被自动删除
		// i is already the first State in r.
		for (; !r.iter_end(i); r.iter_next(i)) map(i) = n;
	}
	assert(class_invariant());
	return(*this);
}

// Make *this the identity relation:
StateEqRel& StateEqRel::identity()
{
	assert(class_invariant());
	// We'll need the reprentatives later.
	StateSet repr(representatives());
	// Wipse out all previous stuff.
	for (State st = 0; st < domain(); st++)
	{
		// There may be something to wipe out here.
		// To avoid double delete[] of the same memory, only do the delete
		// when st is the representative of it's eq. class.
		if (repr.contains(st))
		{
			// 目前什么也没做！
		}
		// Assign the new StateSet.
		map(st) = new StateSet; // 没有删除，外部调用，使用完要删除，也可能在父类的析构函数中被自动删除
		// It's the emptyset,and set the domain.
		lookup(st)->set_domain(domain());
		assert(lookup(st)->empty());
		lookup(st)->add(st);
	}
	assert(class_invariant());
	return(*this);
}

// What is the set of representatives of equivalence classes of *this?
StateSet StateEqRel::representatives() const
{
	assert(class_invariant());
	// Keep track of the States to consider.
	StateSet consider;
	consider.set_domain(domain());
	consider.complement();
	StateSet ret;
	ret.set_domain(domain());
	State st;
	// Iterate over all States that must be considered.
	// starting with all of the States.
	for (consider.iter_start(st); !consider.iter_end(st); consider.iter_next(st))
	{
		ret.add(eq_class_representative(st));
		// No need to look at the rest of eq. class [st].
		consider.remove(equiv_class(st));
	}
	assert(class_invariant());
	return(ret);
}

// Domain setting stuff:
void StateEqRel::set_domain(int r)
{
	assert(class_invariant());
	StateTo<StateSet *>::set_domain(r);
	assert(class_invariant());
}

std::ostream& operator<<(std::ostream& os, const StateEqRel& r)
{
	assert(r.class_invariant());
	os << "\nStateEqRel\n";
	// Print out all of the equivalence class(each only once).
	for (State st = 0; st < r.domain(); st++)
	{
		// If i is the reprensentative of its eq. class, then print the class.
		if (st == r.eq_class_representative(st))
		{
			os << *r.lookup(st) << "\n";
		}
	}
	return(os);
}
