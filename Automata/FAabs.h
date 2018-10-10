/***********************************************************************
Abstract finite automata
Implementation class: FAabs
Files: FAabs.h
Uses: DFA (mentioned)

Description: FAabs is an abstract class, used to provide a common interface to the different types
of finite automata (which are FA, DFA, RFA, LBFA, and RBFA). The following operations
are provided via member functions:
	1. determine how many states there are in the concrete实际的 finite automaton;
	2. restart the finite automaton in its start states;
	3. advance to a new set of states (make a transition) on a character;
	4. determine if the automaton is in accepting states;
	5. determine if the automaton is stuck被卡住 (unable to make further transitions);
	6. determine if a string is in the language of the automaton, and
	7. return a deterministic finite automaton (a DFA) which accepts the same language.

	By convention, the argumentless constructor of a class inheriting from FAabs must construct
an object of that class that accepts the empty language (i.e. the object does not accept anything).
	
	The different types of concrete finite automata is FA, RFA, LBFA, RBFA, and DFA (their interfaces are 
defined in files FA.h, RFA.h, LRFA.h, RBFA.h, and DFA.h respectively). The classes (respectively) represent 
general, reduced, left-biased, right-biased, and deterministic finite automata. They are all concrete because 
they inherit from abstract class FAabs, and do not leave any of the member functions as pure virtual member functions
(each of the classes implements the client interface defined in class FAabs).

Implementation: Since it is an abstract base class (pure virtual), all except one of the member
functions are pure virtual; the acceptable member function is defined.
 ***********************************************************************/
#pragma once

// Just mention DFA here, since circularity would be a problem if we include DFA.h.
class DFA;

// Abstract finite automaton. All other automaton types are derived from this one.
// Basic FA operations are supported.
class FAabs
{
public:
	// Return the number of stales(or some reasonably close measure).
	virtual int num_states() const = 0;
	
	// Reset the current state (to start stsates) before beginning to process a string.
	// This is not the default condition for most of the derived classes.
	virtual void restart() = 0;
	
	// Advance the current state by processing a character.
	// advance the automaton by one char in the input string
	virtual void advance(char a) = 0;
	
	// Is the current state an accepting(final) one?
	virtual int in_final() const = 0;
	
	// Is the automaton stuck(unable to make further transitions)?
	virtual int stuck() = 0;
	
	// the string w acceptable?
	virtual int acceptable(const char *w)
	{
		for (restart(); !stuck() && *w; advance(*(w++)))
		{
		}
	    // It's acceptable if *this is final, and the whole of w was consumed.
		return(in_final() && !*w);
	}
	
	// Return a DFA accepting the same language as *this.
	virtual DFA determinism() const = 0;
};

