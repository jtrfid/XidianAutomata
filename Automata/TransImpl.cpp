/*************************************************************************
	Implementation: A Translmpl contains a pointer to a dynamically allocated array of TransPair,
an integer indicating the size of the array, and an integer indicating how much of the array is in use.

	Performance: Use-counting this class would bring a great benefit to Trans, DTrans, TransRel, and D TransRel.
 *************************************************************************/

#include "TransImpl.h"


// Copy constructor allocates more memory.Should use(use-counting) for efficiency.
TransImpl::TransImpl(const TransImpl& r):
	howmany(r.in_use + expansion_extra),
	in_use(r.in_use),
	data(new TransPair[r.in_use + expansion_extra])
{
	assert(r.class_invariant());
	for (int i = 0; i < in_use; i++) data[i] = r.data[i];
	assert(class_invariant());
}

// Destructor is virtual, simple.
TransImpl::~TransImpl()
{
	assert(class_invariant());
	delete[]data;
}

// operator=() must copy the memory.
const TransImpl& TransImpl::operator=(const TransImpl& r)
{
	assert(class_invariant() && r.class_invariant());
	if (this == &r) return(*this);

	// Don't use ensure_min_size() here due to excessive copying.
	if (howmany < r.in_use)
	{
		TransPair *d(new TransPair[howmany = r.in_use + expansion_extra]);
		/*delete data;*/  //allocated with 'new[]' in line 15,   data(new TransPair[r.in_use + expansion_extra])
		delete[]data;  
		data = d;
	}
	assert(howmany >= r.in_use);
	for (int i = 0; i < r.in_use; i++) data[i] = r.data[i];
	in_use = r.in_use;
	assert(class_invariant());
	return(*this);
}

// What are all of the labels on transitions in *this?
CRSet TransImpl::out_labels() const
{
	CRSet a;
	for (int i = 0; i < in_use; i++) a.add(data[i].transition_label);
	return(a);
}

// What are all transition labels with destination in r?
CRSet TransImpl::labels_into(const StateSet& r) const
{
	assert(class_invariant() && r.class_invariant());
	CRSet a;
	for (int i = 0; i < in_use; i++)
	{
		assert(data[i].transition_destination <= r.domain());
		if (r.contains(data[i].transition_destination)) 
		{
			a.add(data[i].transition_label);
		}
	}
	assert(class_invariant());
	return(a);
}

// Add a transition to the set.
TransImpl& TransImpl::add_transition(const CharRange a, const State q)
{
	assert(a.class_invariant());
	assert(0 <= q);

	// Can the transition be merged with an already existing one.
	for (int i = 0; i < in_use; i++)
	{
		// They're mergeable if they go to the same place and the labels are adjacent.
		if ((data[i].transition_destination == q) && (data[i].transition_label.overlap_or_adjacent(a)))
		{
			data[i].transition_label.merge(a);
			return(*this);
		}
	}
	// The transition really must be added,since it wasn't merged.

	// Is there a need to grow the data[].
	ensure_min_size(in_use + 1);
	assert(in_use < howmany);
	data[in_use].transition_label = a;
	data[in_use++].transition_destination = q;
	return(*this);
}

// Helpers
void TransImpl::ensure_min_size(int w)
{
	assert(class_invariant());
	assert(0 <= w);
	if (howmany < w)
	{
		TransPair *d(new TransPair[howmany = w + expansion_extra]);
		for (int i = 0; i < in_use; i++) d[i] = data[i];
		// Assume that delete[]0 is okay.
		delete[]data;
		data = d;
	}
	assert(howmany >= w);
	assert(class_invariant());
}

// Output the transitions.
std::ostream& operator<<(std::ostream& os, const TransImpl& r)
{
	assert(r.class_invariant());
	os << '{';
	for (int i = 0; i < r.in_use; i++)
	{
		os << ' ' << r.data[i].transition_label << "->" << r.data[i].transition_destination << ' ';
	}
	return(os << '}');
}
