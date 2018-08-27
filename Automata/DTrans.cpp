/*************************************************************************************
	Implementation: DTrans inherits from TransImpl for implementation.Most member functions
	are simply calls to the corresponding TransImpl member.
	Performance : See the base class TransImpl.
***************************************************************************************/
#include "stdafx.h"
#include "DTrans.h"

// Map a char to the unique next state.
State DTrans::operator[](const char a) const
{
	assert(class_invariant());
	// Task first valid transition.
	for (int i = 0; i < in_use; i++)
	{
		if (transitions(i).transition_label.contains(a))
		{
			return(transitions(i).transition_destination);
		}
	}
	assert(class_invariant());
	return(Invalid);
}

// Map a CharRange to the corresponding State
// assuming that the CharRange is entirely contained in the label of a transition.
State DTrans::range_transition(const CharRange a) const
{
	assert(class_invariant());
	// Task first valid transition.
	for (int i = 0; i < in_use; i++)
	{
		if (a <= transitions(i).transition_label)
		{
			return(transitions(i).transition_destination);
		}
	}
	assert(class_invariant());
	return(Invalid);
}

// Is there a valid out-transition on a?
int DTrans::valid_out_transition(const CharRange a) const
{
	assert(class_invariant());
	for (int i = 0; i < in_use; i++)
	{
		if (a <= transitions(i).transition_label)
		{
			return(1);
		}
	}
	assert(class_invariant());
	return(0);
}

// What is the range(States) of this map?
// return a StateSet with domain dom.
StateSet DTrans::range(int dom) const
{
	assert(class_invariant());
	StateSet result;
	result.set_domain(dom);
	for (int i = 0; i < in_use; i++)
	{
		result.add(transitions(i).transition_destination);
	}
	assert(class_invariant());
	return(result);
	
}

std::ostream& operator<<(std::ostream& os, const DTrans& r)
{
	assert(r.class_invariant());
	// return(os << r);  // warning C4717: “operator<<”: 如递归所有控件路径，函数将导致运行时堆栈溢出
	return(os << (TransImpl&)r);  // 需要类型转换，否则引起递归调用
}
