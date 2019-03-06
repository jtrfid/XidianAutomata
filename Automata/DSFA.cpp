/**********************************************************************************
Implementation: A DSFA contains a StateSet, representing the set of FA States that make up
a DFA state in the subset construction (see [Wat93a, p. 12-13] for an explanation of the
subset construction). The implementation follows directly from the way in which an FA
processes an input string.
 **********************************************************************************/

#include "DSFA.h"

// A special constructor:
DSFA::DSFA(const StateSet& rq,
	const TransRel *fT,
	const StateRel *rE,
	const StateSet *rF)
{
	assert(class_invariant());
}

CRSet DSFA::out_labels() const
{
	assert(class_invariant());
	return(T->out_labels(which));
}
DSFA DSFA::out_transition(const CharRange a) const
{
	assert(class_invariant());
	// Construct the abstract State on the way out of here:
	// Assume that which is already E closed, then transition on CharRange a; 
	// the StateSet gets E closed again in the constructor.
	return(DSFA(T->transition_on_range(which, a), T, E, F));
}

