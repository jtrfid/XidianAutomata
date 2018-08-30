/***********************************************************************************
	Implementation class: REops
	Files: REops. h
	Uses:
	Description: The regular operators (of the ¦²-algebra -- see class Reg or [Wat93a, Definition
	3.12]) are encoded as elements of an enumeration. These are usually stored in a type-field in
	regular expressions. They play an important role in computing the homomorphic (¦²-algebra)
	image of a regular expression
	Implementation: REops is defined as an enum.
 ***********************************************************************************/
#pragma once

// Define the regular operators as an enumerated type.These correspond to the
// Sigma algebra operators(see Definition 3.12 of the Taxonomy, and Sigma.h).
enum REops
{
	EPSILON,
	EMPTY,
	SYMBOL,
	OR,
	CONCAT,
	STAR,
	PLUS,
	QUESTION
};