/**************************************************************************
	Constructing a DFA
	Implementation class : DFA_components
	Files : DFA_components.h
	Uses : DTransRel, StatePool, StateSet
	Description : A DFA_components is a structure containing the essential parts of a DFA. 
	Class DFA has a constructor taking a DFA_components.It is used in the subset construction, as
	the return type of template function construct_components.
	Implementation : The class is implemented as a struct.
	Performance : The template function construc_components should really be a constructor template
	of DFA.This would avoid needing DFA_components, and the overhead of passing the structure by value.
*******************************************************************************/
#pragma once
#include "StatePool.h"
#include "StateSet.h"
#include "DTransRel.h"

struct DFA_components
{
	StatePool Q;
	StateSet S;
	DTransRel T;
	StateSet F;
};
