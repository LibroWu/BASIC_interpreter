/*
 * File: evalstate.cpp
 * -------------------
 * This file implements the EvalState class, which defines a symbol
 * table for keeping track of the value of identifiers.  The public
 * methods are simple enough that they need no individual documentation.
 */

#include <string>
#include "evalstate.h"

#include "../StanfordCPPLib/map.h"
using namespace std;

/* Implementation of the EvalState class */

EvalState::EvalState() {
   /* Empty */
}

EvalState::~EvalState() {
   /* Empty */
}

void EvalState::setValue(string var, int value) {
   symbolTable.put(var, value);
}

int EvalState::getValue(string var) {
   return symbolTable.get(var);
}

bool EvalState::isDefined(string var) {
   return symbolTable.containsKey(var);
}

void EvalState::clear(){
    symbolTable.clear();
}

bool check_reserve(string s){
    if (s=="LET") return 1;
    if (s=="RUN") return 1;
    if (s=="LIST")return 1;
    if (s=="CLEAR")return 1;
    if (s=="QUIT")return 1;
    if (s=="HELP")return 1;
    if (s=="REM")return 1;
    if (s=="GOTO")return 1;
    if (s=="END")return 1;
    if (s=="PRINT")return 1;
    if (s=="INPUT")return 1;
    if (s=="")return 1;
    return 0;
}