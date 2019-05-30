/**********************************************************************************
	Implementation: DTransRel inherits for implementation from StateTo<DTrans>. Many of the
member functions are simply calls to the members of State To or DTrans.
 **********************************************************************************/

#include "DTransRel.h"


// Compute the reverse transition on a range under *this:
StateSet DTransRel::reverse_transition(const State r, const CharRange a) const
{
	assert(class_invariant());
	assert(0 <= r && r < domain());
	StateSet ret;
	ret.set_domain(domain());
	// Iterate over all of the States, and see which have transitions to r.
	for (State p = 0; p < domain(); p++)
	{
		if (transition_on_range(p, a) == r) ret.add(p);
	}
	return(ret);
}

// What are all States reverse reachable from r ?
StateSet DTransRel::reverse_closure(const StateSet& r) const
{
	assert(class_invariant() && r.class_invariant());
	assert(domain() == r.domain());
	StateSet result(r);
	StateSet intermediate;
	intermediate.set_domain(domain());
	assert(intermediate.empty());
	do {
		result.set_union(intermediate);
		intermediate.clear();

		// Go through the State's to see which can reach set result on some transition.
		for (State st = 0; st < domain(); st++)
		{
			if (result.not_disjoint(lookup(st).range(domain()))) intermediate.add(st);
		}
	} while (!result.contains(intermediate));
	return(result);
}

// add by hushuangpu
// What are all States reachable from r?
StateSet DTransRel::closure(const StateSet& r) const
{
	StateSet result(r);
	StateSet intermediate;
	StateSet temp;
	intermediate.set_domain(domain());
	temp.set_domain(domain());

	int n = 0;

	do
	{
		result.set_union(intermediate);
		intermediate.set_union(result);
		//intermediate.clear();
		State st;
		for (result.iter_start(st); !result.iter_end(st); result.iter_next(st))
		{
			StateSet temp = lookup(st).range(domain());
			intermediate.set_union(temp);
			temp.clear();
		}
		/*std::cout << "result: " << result << std::endl;
		std::cout << "interm: " << intermediate << std::endl;*/
		n++;
	} while (result != intermediate);
	//std::cout << result << std::endl;
	return(result);
}

// Recycle this entire structure.
void DTransRel::reincarnate()
{
	assert(class_invariant());
	// Don't reset the domain()
	for (int i = 0; i < domain(); i++) map(i).reincarnate();
	StateTo<DTrans>::reincarnate();
	assert(class_invariant());
}

