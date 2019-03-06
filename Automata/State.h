#pragma once
/***************************************************************************************************
 Files: State.h
 Uses :
 Description: In the FIRE engine, all finite automaton states are encoded as non-negative integers.
       The special value Invalid is used to flag an invalid state.

 Implementation : Not making State a class has the effect that no extra information can be stored
	   in a state, and a State can be silently converted to an into int.
*****************************************************************************************************/


#ifndef AUTOMATA_STATE_H
#define AUTOMATA_STATE_H


// Encode automata states as integers.
typedef signed int State;

// Invalid states mean something bad is about to happen.
const State Invalid = -1;

#endif // !AUTOMATA_STATE_H





