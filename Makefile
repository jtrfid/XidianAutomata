#!/bin/bash
CCFLAG = -Wall -fexceptions -g -std=c++11
CC = g++

ALL = ./obj/Automata.o ./obj/BitVec.o ./obj/CharRange.o ./obj/Constrs.o ./obj/CRSet.o ./obj/Dconstrs.o ./obj/Deriv.o ./obj/DFA.o ./obj/DSIS.o \
	./obj/DSDeRemer.o ./obj/DSDFARev.o ./obj/DSFA.o ./obj/DSISopt.o ./obj/DSLBFA.o ./obj/DSRBFA.o ./obj/DSRE.o ./obj/DSREopt.o ./obj/DSRFA.o \
	./obj/DSRFA2.o ./obj/DTrans.o ./obj/DTransRel.o ./obj/FA.o ./obj/Iconstrs.o ./obj/ISImpl.o ./obj/LBFA.o ./obj/RBFA.o ./obj/RE.o ./obj/RFA.o \
	./obj/Sig-FA.o ./obj/Sig-re.o ./obj/Sig-RFA.o ./obj/StateEqRel.o ./obj/StateRel.o ./obj/StateSet.o ./obj/SymRel.o ./obj/Trans.o ./obj/TransImpl.o \
	./obj/TransRel.o ./obj/AutomataTest.o ./obj/CRSetTest.o ./obj/RFATest.o ./obj/StateRelTest.o ./obj/StateSetTest.o ./obj/"StateTo(StateSet)Test.o" \
	./obj/ThompsonTest.o ./obj/TransTest.o

Automata.exe: Automata.o BitVec.o CharRange.o Constrs.o CRSet.o Dconstrs.o Deriv.o DFA.o DSIS.o DSDeRemer.o DSDFARev.o DSFA.o \
 	DSISopt.o DSLBFA.o DSRBFA.o DSRE.o DSREopt.o DSRFA.o DSRFA2.o DTrans.o DTransRel.o \
 	FA.o Iconstrs.o ISImpl.o LBFA.o RBFA.o RE.o RFA.o Sig-FA.o Sig-re.o Sig-RFA.o StateEqRel.o \
 	StateRel.o StateSet.o SymRel.o Trans.o TransImpl.o TransRel.o AutomataTest.o CRSetTest.o \
	RFATest.o StateRelTest.o StateSetTest.o StateTo(StateSet)Test.o ThompsonTest.o TransTest.o
	$(CC) -o Automata.exe $(ALL)

Automata.o: Automata/Automata.cpp
	test -d obj || mkdir obj
	$(CC) $(CCFLAG) -c Automata/Automata.cpp -o obj/Automata.o

BitVec.o: Automata/BitVec.cpp
	$(CC) $(CCFLAG) -c Automata/BitVec.cpp -o obj/BitVec.o

CharRange.o: Automata/CharRange.cpp
	$(CC) $(CCFLAG) -c Automata/CharRange.cpp -o obj/CharRange.o

Constrs.o: Automata/Constrs.cpp
	$(CC) $(CCFLAG) -c Automata/Constrs.cpp -o obj/Constrs.o

CRSet.o: Automata/CRSet.cpp
	$(CC) $(CCFLAG) -c Automata/CRSet.cpp -o obj/CRSet.o

Dconstrs.o: Automata/Dconstrs.cpp
	$(CC) $(CCFLAG) -c Automata/Dconstrs.cpp -o obj/Dconstrs.o

Deriv.o: Automata/Deriv.cpp
	$(CC) $(CCFLAG) -c Automata/Deriv.cpp -o obj/Deriv.o

DFA.o: Automata/DFA.cpp
	$(CC) $(CCFLAG) -c Automata/DFA.cpp -o obj/DFA.o

DSDeRemer.o: Automata/DSDeRemer.cpp
	$(CC) $(CCFLAG) -c Automata/DSDeRemer.cpp -o obj/DSDeRemer.o

DSDFARev.o: Automata/DSDFARev.cpp
	$(CC) $(CCFLAG) -c Automata/DSDFARev.cpp -o obj/DSDFARev.o

DSFA.o: Automata/DSFA.cpp
	$(CC) $(CCFLAG) -c Automata/DSFA.cpp -o obj/DSFA.o

DSIS.o: Automata/DSIS.cpp
	$(CC) $(CCFLAG) -c Automata/DSIS.cpp -o obj/DSIS.o

DSISopt.o: Automata/DSISopt.cpp
	$(CC) $(CCFLAG) -c Automata/DSISopt.cpp -o obj/DSISopt.o

DSLBFA.o: Automata/DSLBFA.cpp
	$(CC) $(CCFLAG) -c Automata/DSLBFA.cpp -o obj/DSLBFA.o

DSRBFA.o: Automata/DSRBFA.cpp
	$(CC) $(CCFLAG) -c Automata/DSRBFA.cpp -o obj/DSRBFA.o
	
DSRE.o: Automata/DSRE.cpp
	$(CC) $(CCFLAG) -c Automata/DSRE.cpp -o obj/DSRE.o

DSREopt.o: Automata/DSREopt.cpp
	$(CC) $(CCFLAG) -c Automata/DSREopt.cpp -o obj/DSREopt.o

DSRFA.o: Automata/DSRFA.cpp
	$(CC) $(CCFLAG) -c Automata/DSRFA.cpp -o obj/DSRFA.o

DSRFA2.o: Automata/DSRFA2.cpp
	$(CC) $(CCFLAG) -c Automata/DSRFA2.cpp -o obj/DSRFA2.o

DTrans.o: Automata/DTrans.cpp
	$(CC) $(CCFLAG) -c Automata/DTrans.cpp -o obj/DTrans.o

DTransRel.o: Automata/DTransRel.cpp
	$(CC) $(CCFLAG) -c Automata/DTransRel.cpp -o obj/DTransRel.o

FA.o: Automata/FA.cpp
	$(CC) $(CCFLAG) -c Automata/FA.cpp -o obj/FA.o

Iconstrs.o: Automata/Iconstrs.cpp
	$(CC) $(CCFLAG) -c Automata/Iconstrs.cpp -o obj/Iconstrs.o

ISImpl.o: Automata/ISImpl.cpp
	$(CC) $(CCFLAG) -c Automata/ISImpl.cpp -o obj/ISImpl.o

LBFA.o: Automata/LBFA.cpp
	$(CC) $(CCFLAG) -c Automata/LBFA.cpp -o obj/LBFA.o

RBFA.o: Automata/RBFA.cpp
	$(CC) $(CCFLAG) -c Automata/RBFA.cpp -o obj/RBFA.o

RE.o: Automata/RE.cpp
	$(CC) $(CCFLAG) -c Automata/RE.cpp -o obj/RE.o

RFA.o: Automata/RFA.cpp
	$(CC) $(CCFLAG) -c Automata/RFA.cpp -o obj/RFA.o

Sig-FA.o: Automata/Sig-FA.cpp
	$(CC) $(CCFLAG) -c Automata/Sig-FA.cpp -o obj/Sig-FA.o

Sig-re.o: Automata/Sig-re.cpp
	$(CC) $(CCFLAG) -c Automata/Sig-re.cpp -o obj/Sig-re.o

Sig-RFA.o: Automata/Sig-RFA.cpp
	$(CC) $(CCFLAG) -c Automata/Sig-RFA.cpp -o obj/Sig-RFA.o

StateEqRel.o: Automata/StateEqRel.cpp
	$(CC) $(CCFLAG) -c Automata/StateEqRel.cpp -o obj/StateEqRel.o

StateRel.o: Automata/StateRel.cpp
	$(CC) $(CCFLAG) -c Automata/StateRel.cpp -o obj/StateRel.o

StateSet.o: Automata/StateSet.cpp
	$(CC) $(CCFLAG) -c Automata/StateSet.cpp -o obj/StateSet.o

SymRel.o: Automata/SymRel.cpp
	$(CC) $(CCFLAG) -c Automata/SymRel.cpp -o obj/SymRel.o

Trans.o: Automata/Trans.cpp
	$(CC) $(CCFLAG) -c Automata/Trans.cpp -o obj/Trans.o

TransImpl.o: Automata/TransImpl.cpp
	$(CC) $(CCFLAG) -c Automata/TransImpl.cpp -o obj/TransImpl.o

TransRel.o: Automata/TransRel.cpp
	$(CC) $(CCFLAG) -c Automata/TransRel.cpp -o obj/TransRel.o

AutomataTest.o: Automata/Test/AutomataTest.cpp
	$(CC) $(CCFLAG) -c Automata/Test/AutomataTest.cpp -o obj/AutomataTest.o

CRSetTest.o: Automata/Test/CRSetTest.cpp
	$(CC) $(CCFLAG) -c Automata/Test/CRSetTest.cpp -o obj/CRSetTest.o

RFATest.o: Automata/Test/RFATest.cpp
	$(CC) $(CCFLAG) -c Automata/Test/RFATest.cpp -o obj/RFATest.o

StateRelTest.o: Automata/Test/StateRelTest.cpp
	$(CC) $(CCFLAG) -c Automata/Test/StateRelTest.cpp -o obj/StateRelTest.o

StateSetTest.o: Automata/Test/StateSetTest.cpp
	$(CC) $(CCFLAG) -c Automata/Test/StateSetTest.cpp -o obj/StateSetTest.o
	
StateTo(StateSet)Test.o: Automata/Test/StateTo(StateSet)Test.cpp
	$(CC) $(CCFLAG) -c "Automata/Test/StateTo(StateSet)Test.cpp" -o "obj/StateTo(StateSet)Test.o"

ThompsonTest.o: Automata/Test/ThompsonTest.cpp
	$(CC) $(CCFLAG) -c Automata/Test/ThompsonTest.cpp -o obj/ThompsonTest.o

TransTest.o: Automata/Test/TransTest.cpp
	$(CC) $(CCFLAG) -c Automata/Test/TransTest.cpp -o obj/TransTest.o

clean:
	rm -rf Automata.exe obj