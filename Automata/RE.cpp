/**********************************************************************************
	Implementation: Regular expressions are implemented as expression trees. The comparison of
regular expressions is defined recursively and uses a depth-first traversal.

	Performance: Use-counting could avoid the deep-tree copies that are performed. An RE could
be stored as a prefix-form string, as in [RW93J; this could give some problems with the heavy
use of members such as left_subexpr and right_subexpr.
 **********************************************************************************/

#include <iostream>
#include <iomanip>
#include "RE.h"

RE::RE(const RE& e) :op(e.op),right(0) // Only the right on purpose.
{
	assert(e.class_invariant());
	switch (e.root_operator())
	{
	case EPSILON:
	case EMPTY:
		left = 0;
		break;
	case SYMBOL:
		left = 0;
		// Now it's safe to copy the sym.
		sym = e.sym;
		break;
	case OR:
	case CONCAT:
		right = new RE(e.right_subexpr());
	case STAR:
	case PLUS:
	case QUESTION:
		left = new RE(e.left_subexpr());
		break;
	default:
		// Shold throw() something!
		break;
	}
	assert(class_invariant());
}

RE::~RE()
{
	delete left;
	delete right;
}

const RE& RE::operator=(const RE& e)
{
	assert(e.class_invariant());
	op = e.op;
	right = 0;
	switch (e.root_operator())
	{
	case EPSILON:
	case EMPTY:
		left = 0; break;
	case SYMBOL:
		left = 0;
		// Now it's safe to copy the sym.
		// In no other case is it safe to copy the sym.
		sym = e.sym;
		break;
	case OR:
	case CONCAT:
		delete right;
		right = new RE(e.right_subexpr());
	case STAR:
	case PLUS:
	case QUESTION:
		delete left;
		left = new RE(e.left_subexpr());
		break;
	default:
		// Shold throw() something!
		break;
	}
	assert(class_invariant());
	return(*this);
}

// How many SYMBOL nodes in this regular expression?
// Mainly for use in constructing RFA's.
// How many symbols are there in *this RE?
int RE::num_symbols() const
{
	assert(class_invariant());
	int ret;  //warning: 'ret' may be used uninitialized in this function [-Wmaybe-uninitialized]|
	switch (op)
	{
	case EPSILON:
	case EMPTY:
		ret = 0; break;
	case SYMBOL:
		ret = 1; break;
	case OR:
	case CONCAT:
		ret = left->num_symbols() + right->num_symbols();
		break;
	case STAR:
	case PLUS:
	case QUESTION:
		ret = left->num_symbols();
		break;
	default:
		// Shold throw() something!
		break;
	}
	return(ret);
}

// How many operators in this RE?
// Used in ISImpl(the item set stuff).
int RE::num_operators() const
{
	assert(class_invariant());
	int ret;
	switch (op)
	{
	case EPSILON:
	case EMPTY:
	case SYMBOL:
		ret = 1; break;
	case OR:
	case CONCAT:
		ret = left->num_operators() + right->num_operators() +1;
		break;
	case STAR:
	case PLUS:
	case QUESTION:
		ret = left->num_operators() +1;
		break;
	default:
		// Shold throw() something!
		break;
	}
	return(ret);
}

// Output in prefix notion.
// Part of this could be REops,if enums could be used for overload resolution.
std::ostream& operator<<(std::ostream& os, const RE& r)
{
	switch (r.root_operator())
	{
	case EPSILON:
		os << '1'; break;
	case EMPTY:
		os << '0'; break;
	case SYMBOL:
		os << r.symbol(); break;
	case OR:
		os << "| " << r.left_subexpr() << ' ' << r.right_subexpr();
		break;
	case CONCAT:
		os << ". " << r.left_subexpr() << ' ' << r.right_subexpr();
		break;
	case STAR:
		os << "* " << r.left_subexpr();
		break;
	case PLUS:
		os << "+ " << r.left_subexpr();
		break;
	case QUESTION:
		os << "? " << r.left_subexpr();  //convert "？"   to "?"
		break;
	default:
		// Shold throw() something!
		break;
	}
	return(os);
}

// Input,in prefix notion. Not muach error checking is done!
std::istream& operator>>(std::istream& is, RE& r)
{
	// Wipse out anything that used to be in r.
	delete r.left;
	delete r.right;
	// if something gones wrong try to leaver r as the EMPTY regular expression.
	r.left = r.right = 0;
	r.op = EMPTY;
	char c;
	// If could be that there is nothing in th input.
	if (!(is >> c))
	{
		is.clear(std::ios::badbit | is.rdstate());
	}
	else
	{
		switch (c)
		{
		case '1':
			r.op = EPSILON; break;
		case '0':
			r.op = EMPTY; break;
		case '[':
			// This stuff should really be as the extraction operator
			// in class CharRange.
			is >> c;
			if (c != '\'') {
				std::cerr << "First CharRange incorrect\n";
				is.clear(std::ios::badbit | is.rdstate());
			}
			else {
				// Input first character of the range
				is >> c;
				char c2;
				is >> c2;
				if (c2 != '\'') {
					std::cerr << "Fist CharRange not terminated properly\n";
					is.clear(std::ios::badbit | is.rdstate());
				}
				else {
					is >> c2;
					if (c2 != '\'') {
						std::cerr << "Second CharRange incorrect\n";
						is.clear(std::ios::badbit | is.rdstate());
					}
					else {
						// Input first char of second range.
						is >> c2;
						r.sym = CharRange(c, c2);
						r.op = SYMBOL;
						is >> c;
						if (c != '\'') {
							std::cerr << "Second CharRange not "
								<< "terminated properly\n";
							is.clear(std::ios::badbit | is.rdstate());
						}
						is >> c;
						if (c != ']') {
							std::cerr << "Close block not found\n";
							is.clear(std::ios::badbit | is.rdstate());
						}
					}
				}
			}
			break;
		case '\'':
			is >> c;
			r.sym = CharRange(c);
			r.op = SYMBOL;
			is >> c;
			if (c != '\'')
			{
				std::cerr << "Single character terminated incorrectly\n";
				is.clear(std::ios::badbit | is.rdstate());
			}
			break;
		case '|':
			r.op = OR;
			r.left = new RE;
			r.right = new RE;
			is >> *r.left;
			is >> *r.right;
			break;
		case '.':
			r.op = CONCAT;
			r.left = new RE;
			r.right = new RE;
			is >> *r.left;
			is >> *r.right;
			break;
		case '*':
		case '+':
		case '?':
			if (c == '*')
			{
				r.op = STAR;
			}
			else if (c == '+')
			{
				r.op = PLUS;
			}
			else if (c == '?')
			{
				r.op = QUESTION;
			}
			r.left = new RE;
			is >> *r.left;
			break;
		default:
			std::cerr << "Something went wrong\n";
			is.clear(std::ios::badbit | is.rdstate());
		}
		assert(r.class_invariant());
	}
	return(is);
}

// Make a copy of *this into *r
void RE::shallow_copy(RE *const r) const
{
	r->op = op;
	r->left = left;
	r->right = right;
	r->sym = sym;
}

// recycle
// op = EMPTY, left = right = 0
void RE::reincarnate()
{
	if (left != 0)
	{
		// This is a non-basic operator for reincarnation.
		// Delete left;
		delete left;
		left = 0;
		if (right != 0)
		{
			// This is a binary operator for reincarnation.
			delete right;
			right = 0;
		}
	}
	op = EMPTY;
	assert(class_invariant());
}
