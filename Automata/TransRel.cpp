/*********************************************************************************
	Implementation: TransRel inherits for implementation from StateTo< Trans>. Many of the
	member functions simply call the corresponding members functions of StateTo or Trans.
 *********************************************************************************/
#include "stdafx.h"
#include "TransRel.h"

// Compute the image of r, and a under *this. return T(r,a) = { image }
StateSet TransRel::image(const StateSet& r, const char a) const
{
	assert(class_invariant() && r.class_invariant());
	assert(r.domain() == domain());
	// result is, by default,the emptyset.
	StateSet result;
	result.set_domain(domain());
	State st;
	for (r.iter_start(st); !r.iter_end(st); r.iter_next(st))
	{
		// Here we assume that the Trans in the TransRel have the same domain too.
		result.set_union(lookup(st)[a]);
	}
	return(result);
}

// Transitioning on a CharRange? (Same idea as above.)
StateSet TransRel::transition_on_range(const StateSet& r, const CharRange a) const
{
	assert(class_invariant() && r.class_invariant());
	assert(r.domain() == domain());
	StateSet result;
	result.set_domain(domain());
	// Go through all of the States to see which transitions happen.
	State st;
	for (r.iter_start(st); !r.iter_end(st); r.iter_next(st))
	{
		result.set_union(lookup(st).range_transition(a));
	}
	return(result);
}

// On which labels can we transition?
CRSet TransRel::out_labels(const StateSet& r) const
{
	assert(class_invariant());
	CRSet result;
	State st;
	// Go through all of r's States.
	for (r.iter_start(st); !r.iter_end(st); r.iter_next(st))
	{
		result.combine(lookup(st).out_labels());
	}
	return(result);
}

// Change the domain of this relation.
void TransRel::set_domain(const int r)
{
	assert(class_invariant());
	StateTo<Trans>::set_domain(r);
	for (int i = 0; i < domain(); i++)
	{
		map(i).set_range(r);
	}
	assert(class_invariant());
}

// Recycle this entire structure.
void TransRel::reincarnate()
{
	assert(class_invariant());
	// First reincarnate() all of the componets before *this
	for (int i = 0; i < domain(); i++)
	{
		map(i).reincarnate();
	}
	StateTo<Trans>::reincarnate();
	assert(class_invariant());
}

// Union relation r into *this, while adjusting r.
TransRel& TransRel::disjointing_union(const TransRel& r)
{
	assert(class_invariant() && r.class_invariant());
	int olddom(domain());
	StateTo<Trans>::disjointing_union(r);
	assert(StateTo<Trans>::domain() == r.domain() + olddom);
	int i;
	for (i = 0; i < olddom; i++) map(i).set_range(domain());
	for (; i < domain(); i++) map(i).st_rename(olddom);
	assert(class_invariant());
	return(*this);
}
