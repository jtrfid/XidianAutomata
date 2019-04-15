/******************************************************************************************************************
	Derivatives
	Two functions on regular expressions, Null and First (see [Wat93a, Definiton 3.20, Property 3.21, Definition 4.60]
- both used in computing derivatives of regular expressions), are defined as recursive member
functions in file deriv.cpp. Function Null returns 1 if the empty word (ε) is in the language
denoted by the regular expression, and 0 otherwise. Function First returns a CRSet denoting the
characters which can occur as the first character of a word in the language denoted by the regular
expression.
	Member function derivative takes a CharRange and returns the derivative of the regular expression
with respect to the CharRange. The derivative is computed recursively according to the
definition given in [Wat93a, Definition 5.23]. It is used in the implementation of Brzozowski's
construction.
	• All of its OR operators are left-associative; for example (E0 ∪ El ) ∪ E2 is left-associative,
	  while E0 ∪ (El ∪ E2) is not.
	• The OR regular expression is in one of two forms (where ≦ is the total ordering on regular
	  expressions): either (E0 ∪ El ) ∪ E2 where El < E2 and (E0 ∪ E1 is in ONF, or E0 ∪ El
	  where E0 < El. (The use of < instead of ≦ implies that if the subexpressions of an OR
	  expression are equal (under the total ordering), then they are collapsed into one expression,
	  implementing the idempotence of OR.)

	The ONF is used to provide the equivalent of a multi-ary OR operator, implementing the associativity,
commutativity and idempotence of the OR operator, as detailed in [Wat93a, Definition 5.26].
	The member function in_snf returns 1 if the RE is in SNF, and 0 otherwise. The member snf puts the RE in SNF,
using function onf as a helper. Member function reduce optimizes an RE, removing any redundant subexpressions.
It implements rules 1 to 5 of [Wat93a, Remark 5.32]. The function performs a bottom-up traversal of the regular expression,
making such transformations as φ. E ----> φ and 0* ----> ε.
	All of these members (including the total ordering) are defined in file Deriv.cpp.
 ******************************************************************************************************************/

#include <iostream>
#include <iomanip>
#include "RE.h"
#include "Sigma.h"

 // Some derivatives(Brzozowski's) related member functions:

 /********************************************************
 // Does * this accept epsilon?
 // This is from Definition 3.20 and Property 3.21
 The nullable sigma-algebra: We define the nullable sigma-algebra as follows:
 * The carrier set is {true,false}.
 * The constants are: true,flase,and false(corresponding respectively to epsilon,empty,and a:a in V).
 * Here the constant false corresponds to empty and to all a in V.
 * The operators are: ∨(析取disjunction,"OR"),∧(conjunction合取,"AND"), the constant function true, the identity function, and (again) the constant
 * function true (corresponding respectively to uion,concat,start,plus,and question).
 * The operators corresponding to star and to qustion are interesting because they map their argument to the constant true.
 *********************************************************/
int RE::Null() const
{
	assert(class_invariant());
	int ret;  //warning: 'ret' may be used uninitialized in this function [-Wmaybe-uninitialized]|
	switch (op)
	{
	case EPSILON:
		ret = 1; break; // epsilon: true
	case EMPTY:
	case SYMBOL:
		ret = 0; break; // empty,symbol: false
	case OR:
		ret = left->Null() || right->Null(); // ∨(disjunction析取,"或")
		break;
	case CONCAT:
		ret = left->Null() && right->Null(); // ∧(conjunction合取,"与")
		break;
	case STAR:
		ret = 1; break; // star: true
	case PLUS:
		ret = left->Null(); //  the identity function
		break;
	case QUESTION: // L union {epsilon}
		ret = 1; break; // question: true
	}
	return(ret);
}

/************************************************
// What is the First of *this?
// This is from Definition 4.60
We define First in RE --> P(V) recursively
First(empty) = Fisrt(empty) = empty
First(a) = {a}
First(E concat F) = First(E) union if (Null(E)) then First(F) else empty fi
First(E or F) = First(E) union First(F)
First(E star) = First(E plus) = First(E qustion) = First(E)
**************************************************/
CRSet RE::First() const
{
	assert(class_invariant());
	CRSet a;
	switch (op)
	{
	case EPSILON:
	case EMPTY:
		break;
	case SYMBOL:
		a.append(sym);
		break;
	case OR:
		a = left->First().combine(right->First());
		break;
	case CONCAT:
		a = left->First();
		if (left->Null())
		{
			a.combine(right->First());
		}
		break;
	case STAR:
	case PLUS:
	case QUESTION:
		a = left->First();
		break;
	}
	return(a);
}

//Is *this in similarity normal form(SNF) ?
int RE::in_snf() const
{
	assert(class_invariant());
	// SNF means that all OR nodes are left-associative,and in the two case:
	// A OR B that A < B, or
	// (A OR B) OR C that B < C and (A OR B) is in SNF.
	int ret;  //warning: 'ret' may be used uninitialized in this function [-Wmaybe-uninitialized]|
	switch (op)
	{
	case EPSILON:
	case EMPTY:
	case SYMBOL:
		// The base are always in SNF.
		ret = 1; break;
	case OR:
		if (right->op == OR || !right->in_snf())
		{
			// This can't be in SNF.
			ret = 0;
		}
		else
		{
			if (left->op == OR)
			{
				// Second case.
				ret = (*(left->right) < *right) && left->in_snf();
			}
			else
			{
				// First case.
				ret = (*left < *right) && left->in_snf();
			}
		}
		break;
	case CONCAT:
		// A CONCAT is in SNF if the subexpressions are in SNF.
		ret = left->in_snf() && right->in_snf();
		break;
	case STAR:
	case PLUS:
	case QUESTION:
		// A unary subexpr. is in SNF if it's subexpressions are too.
		ret = left->in_snf();
		break;
	}
	return(ret);
}

// Put *this into similarity normal form.
RE& RE::snf()
{
	assert(class_invariant());
	switch (op)
	{
	case EPSILON:
	case EMPTY:
	case SYMBOL:
		// Already in SNF.
		break;
	case OR:
		// While the right is an OR,rotate them.
		// Note: this is not a true rotate,since we get
		// E | (F | G) -> (F | E) | G instead of (E | F) | G
		// but, by commutativity it's okay.
		while (right->op == OR)
		{
			RE *temp(left);
			left = right;
			right = left->right;
			left->right = temp;
			assert(class_invariant());
		}
		assert(right->op != OR);
		left->snf();
		assert(class_invariant());
		assert((left->in_snf()));
		right->snf();
		assert(class_invariant());
		assert((right->in_snf()));
		onf();
		assert(class_invariant());
		break;
	case CONCAT:
		left->snf();
		assert(class_invariant());
		assert((left->in_snf()));
		right->snf();
		assert(class_invariant());
		assert((right->in_snf()));
		break;
	case STAR:
	case PLUS:
	case QUESTION:
		left->snf();
		assert(class_invariant());
		assert((left->in_snf()));
		break;
	}
	assert(in_snf());
	assert(class_invariant());
	return(*this);
}

// Reduce(optimize) *this by removing useless information.
// Implement rules 1-4 of Remark 5.32 of the Taxonomy.
RE& RE::reduce()
{
	assert(class_invariant());
	switch (op)
	{
	case EPSILON:
	case EMPTY:
	case SYMBOL:
		// These basis operators cannot be reduce further.
		break;
	case OR:
		left->reduce();
		assert(class_invariant());
		right->reduce();
		assert(class_invariant());
		if (left->op == EMPTY)
		{
			// EMPTY OR E == E
			delete left;
			assimilate_node(right);
			assert(class_invariant());
		}
		else if (right->op == EMPTY)
		{
			delete right;
			assimilate_node(left);
			assert(class_invariant());
		}
		// The case where left and right are both EMPTY is handled correctly.
		break;
	case CONCAT:
		left->reduce();
		assert(class_invariant());
		right->reduce();
		assert(class_invariant());
		if (left->op == EMPTY)
		{
			// EMPTY CONCAT E == EMPTY
			delete right;
			assimilate_node(left);
			assert(class_invariant());
		}
		else if (right->op == EMPTY)
		{
			delete left;
			assimilate_node(right);
			assert(class_invariant());
		}
		else if (left->op == EPSILON)
		{
			// EPSILON CONCAT E == E
			delete left;
			assimilate_node(right);
			assert(class_invariant());
		}
		else if (right->op == EPSILON)
		{
			delete right;
			assimilate_node(left);
			assert(class_invariant());
		}
		break;
	case STAR:
		left->reduce();
		assert(class_invariant());
		if (left->op == EPSILON)
		{
			// EPSILON* == EPSILON
			assimilate_node(left);
			assert(class_invariant());
		}
		else if(left->op == EMPTY)
		{
			// EMPTY* == EPSILON
			delete left;
			op = EPSILON;
			left = right = 0;
			assert(class_invariant());
		}
		break;
	case PLUS:
		left->reduce();
		assert(class_invariant());
		if (left->op == EPSILON)
		{
			// EPSILON + == EPSILON
			assimilate_node(left);
			assert(class_invariant());
		}
		else if (left->op == EMPTY)
		{
			// EMPTY + == EMPTY
			assimilate_node(left);
			assert(class_invariant());
		}
		break;
	case QUESTION:
		left->reduce();
		assert(class_invariant());
		if (left->op == EPSILON)
		{
			// EPSILON ? == EPSILON
			assimilate_node(left);
			assert(class_invariant());
		}
		else if (left->op == EMPTY)
		{
			// EMPTY? == EPSILON
			delete left;
			op = EPSILON;
			left = right = 0;
			assert(class_invariant());
		}
		break;
	}
	assert(class_invariant());
	return(*this);
}

// What is the derivative of *this (w.r.t. r)
// Implement Definition 5.23
RE RE::derivative(const CharRange& r) const
{
	assert(class_invariant());
	// Duplicate some of the knowledge appearing in Sig-re.cpp
	RE e;
	switch (op)
	{
	case EPSILON:
	case EMPTY:
		assert(e.op == EMPTY);
		break;
	case SYMBOL:
		if (r <= sym) // if (a = b) then epsilon else 0 fi
		{
			e.op = EPSILON;
			assert(e.class_invariant());
		}
		else
		{
			// else, it should be EMPTY.
			assert(e.op == EMPTY);
		}
		break;
	case OR:
		e.op = OR;
		e.left = new RE(left->derivative(r));
		e.right = new RE(right->derivative(r));
		assert(e.class_invariant());
		break;
	case CONCAT:
		if (left->Null())
		{
			e.op = OR;
			e.right = new RE(right->derivative(r));
			e.left = new RE;
			e.left->op = CONCAT;
			e.left->left = new RE(left->derivative(r));
			e.left->right = new RE(*right);
			assert(e.class_invariant());
		}
		else
		{
			e.op = CONCAT;
			e.left = new RE(left->derivative(r));
			e.right = new RE(*right);
			assert(e.class_invariant());
		}
		break;
	case STAR:
		e.op = CONCAT;
		e.left = new RE(left->derivative(r));
		e.right = new RE(*this);
		assert(e.class_invariant());
		break;
	case PLUS:
		e.op = CONCAT;
		e.left = new RE(left->derivative(r));
		e.right = new RE;
		e.right->op = STAR;
		e.right->right = 0;
		e.right->left = new RE(*left);
		assert(e.class_invariant());
		break;
	case QUESTION:
		e = left->derivative(r);
		break;
	// By the class_invariant(),the default: cannot occur.
	}
	assert(e.class_invariant());
	return(e);
}

// Some ordering members(largely used in similarity and comparisons)
int RE::ordering(const RE& r) const
{
	assert(class_invariant() && r.class_invariant());
	if (op != r.op) return(op - r.op);
	else
	{
		assert(op == r.op);
		int ret; //warning: 'ret' may be used uninitialized in this function [-Wmaybe-uninitialized]|
		switch (op)
		{
		case EPSILON:
		case EMPTY:
			// These two are unordered(equal).
			ret = 0;
			break;
		case SYMBOL:
			// Both are symbols,so order on the sym.
			ret = sym.ordering(r.sym);
			break;
		case OR:
		case CONCAT:
			ret = left->ordering(r.left_subexpr());
			if (ret != 0) { } // Do nothing.
			else
			{
				// Compare the right subexprs,since the left ones are equal.
				ret = right->ordering(r.right_subexpr());
			}
			break;
		case STAR:
		case PLUS:
		case QUESTION:
			ret = left->ordering(r.left_subexpr());
			break;
		}
		return(ret);
	}
}

// Put *this into OR normal form(ONF) (used in the snf functions)
// The ONF is used to provide the equivalent of a multi-ary OR operator, implementing the associativity,
// commutativity and idempotence of the OR operator, as detailed in [Wat93a, Definition 5.26]
RE& RE::onf()
{
	assert(class_invariant());
	assert(op == OR);
	assert(right->op != OR);
	// Two possibilities: (A OR B) OR C, A OR B.
	if (left->op == OR)
	{
		// Fist one.
		// Figure out which order B,C should be in:
		int ord(left->right->ordering(*right));
		if (ord == 0)
		{
			// B == C, destroy C.
			delete right;
			assimilate_node(left);
		}
		else if (ord > 0)
		{
			// B > C, Need to swap B,C
			// Just do it with pointers:
			RE *const temp(right); // const修饰指针本身
			right = left->right;
			left->right = temp;
			// Also make sure that(what's now) (A OR C) is also in ONF.
			left->onf();
		}
		// else,it's already in OR NF.
	}
	else
	{
		// Second case.
		// Figure out the order of A,B:
		int ord(left->ordering(*right));
		if (ord == 0)
		{
			// A == B
			// Wipe out one of the two nodes,and make *this equal to the remaining one.
			delete right;
			assimilate_node(left);
		}
		else if (ord > 0)
		{
			// A > B, Need to swap A,B(left and right);
			RE *const temp(right);
			right = left;
			left = temp;
		}
		// else,it's already in OR NF
	}
	assert(class_invariant());
	assert(in_snf());
	return(*this);
}

// Destroy node *r, moving its data into *this.
void RE::assimilate_node(RE *const r)
{
	// We can't assert(class_invariant());
	// This just delays catching any potential invariant violations.
	assert(r->class_invariant());
	op = r->op;
	left = r->left;
	right = r->right;
	sym = r->sym;
	assert(class_invariant());
	r->op = EMPTY;
	r->left = r->right = 0;
	delete r;
}

