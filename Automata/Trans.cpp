/******************************************************************************
	Implementation: Trans inherits from Translmpl for implementation. It also maintains the
	range, as an integer. Most member functions are simply calls to the corresponding Translmpl
	member.
	Performance: See the base class Translmpl.
 ******************************************************************************/

#include "Trans.h"


// Some member functions for making transitions:
// Map a char to the corresponding StateSet.
StateSet Trans::operator[](const char a) const
{
	assert(class_invariant());
	StateSet result;
	result.set_domain(range());
	for (int i = 0; i < in_use; i++)
	{
		if (transitions(i).transition_label.contains(a))
		{
			result.add(transitions(i).transition_destination);
		}
	}
	return(result);
}

// Map a CharRange to the corresponding StateSet
// assuming that the CharRange is entirely contained in the label of a transition.
StateSet Trans::range_transition(const CharRange a) const
{
	assert(class_invariant());
	StateSet result;
	result.set_domain(range());
	for (int i = 0; i < in_use; i++)
	{
		if (a <= transitions(i).transition_label)
		{
			result.add(transitions(i).transition_destination);
		}
	}
	return(result);
}

// Do normal set union.
// The following member does not change the range.  
Trans& Trans::set_union(const Trans& r)
{
	assert(class_invariant() && class_invariant());
	assert(range() == r.range());
	if (r.in_use != 0)
	{
		// May need to expand here:
		ensure_min_size(in_use + r.in_use);
		for (int i = 0; i < r.in_use; i++)
		{
			transitions(i + in_use) = r.transitions(i);
		}
		in_use += r.in_use;
	}
	assert(class_invariant());
	return(*this);
}

// Incorporate another Trans, while renaming all of the states.
Trans& Trans::disjointing_union(const Trans& r)
{
	assert(class_invariant());
	// Don't do any useless work.
	if (r.in_use != 0)
	{
		ensure_min_size(in_use + r.in_use);
		assert(howmany >= in_use + r.in_use);
		for (int i = 0; i < r.in_use; i++)
		{
			transitions(i + in_use).transition_label = r.transitions(i).transition_label;
			transitions(i + in_use).transition_destination = r.transitions(i).transition_destination + destination_range;
		}
		in_use += r.in_use;
		destination_range += r.destination_range;
	}
	assert(class_invariant());
	return(*this);
}

// Rename all of the States(that are destinations of some transition)
// such that none of them fall in the range[0,r).
// Rename all states in thi.s Trans, so that they don't clash with
// those in the range[0,r).
Trans& Trans::st_rename(const int r)
{
	assert(class_invariant());
	// Don't do anything useless:
	if (r != 0)
	{
		for (int i = 0; i < in_use; i++)
		{
			transitions(i).transition_destination += r;
		}
		destination_range += r;
	}
	assert(class_invariant());
	return(*this);
}

// Output the transitions.
std::ostream& operator<<(std::ostream& os, const Trans& r)
{
	assert(r.class_invariant());
	return(os << (TransImpl&)r);
}
