/***********************************************************************************
	Implementation class: REops
	Files: REops.h
	Uses:
	Description: The regular operators (of the ¦²-algebra -- see class Reg(Sigma.h) or [Wat93a, Definition
	3.12]) are encoded as elements of an enumeration. These are usually stored in a type-field in
	regular expressions. They play an important role in computing the homomorphic (¦²-algebra)
	image of a regular expression.

	Definition 3.12 (Regular expressions): We define regular expressions (over alphabet V) as
	the ¦²-term algebra over signature ¦² = (S,0) where
	   S consists of a single sort Reg (for regular expression),
	   O is a set of several constants: ¦Å,¦Õ,a1,...,an; Reg(where V = {al, ... ,an }) and 
	     and five operators ¡¤: Reg x Reg --> Reg (the dot operator), U : Reg x Reg --> Reg, * : Reg --> Reg,
	     + : Reg ----> Reg, and ? : Reg ----> Reg.

	Implementation: REops is defined as an enum.
 ***********************************************************************************/
//#pragma once

#ifndef AUTOMATA_REOPS_H
#define AUTOMATA_REOPS_H

// Define the regular operators as an enumerated type.These correspond to the
// Sigma algebra operators(see Definition 3.12 of the Taxonomy, and Sigma.h).
enum REops
{
	EPSILON, // constant, epsilon
	EMPTY,   // constant, empty
	SYMBOL,  // constant, CharRange, a1,a2,...,an
	OR,      // binary operator, |: or(union) operator,Reg x Reg --> Reg 
	CONCAT,  // binary operator, dot operator, Reg x Reg --> Reg
	STAR,    // unary operator, *: Reg --> Reg 
	PLUS,    // unary operator, +: Reg --> Reg
	QUESTION // unary operator, ?: Reg --> Reg
};

#endif // !AUTOMATA_REOPS_H


