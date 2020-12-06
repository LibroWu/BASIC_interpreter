/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"

using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
    /* Empty */
}

Statement::~Statement() {
    /* Empty */
}

Statement *parseState(string line,bool flag) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);
    string first_token,token;
    if (flag){
        first_token=scanner.nextToken();
    }
    Statement *sta = nullptr;
    Expression *exp = nullptr;
    first_token=scanner.nextToken();
    if (first_token=="LET") {
        try {
            sta=new StateLet(scanner);
            return sta;
        }
        catch (...) {
            if (sta != nullptr)
                delete sta;
        }
    }
    else if (first_token=="PRINT"){
        try {
            exp=parseExp(scanner);
            if (exp->getType() == COMPOUND) throw invalid_argument("");
            sta=new StatePrint(exp);
            return sta;
        } catch (...) {
            if (exp != nullptr)
                delete exp;
            if (sta != nullptr)
                delete sta;
        }
    }
    else if (first_token=="INPUT"){
        try {
            exp=parseExp(scanner);
            if (exp->getType()!=IDENTIFIER) throw invalid_argument("");
            sta=new StateInput(exp);
        } catch (...) {

        }

    }
    else if (first_token=="REM"){

    }
    else if (first_token=="END"){

    }
    else if (first_token=="IF"){

    }
    else if (first_token=="GOTO"){

    }else throw invalid_argument("...");
}

StateRem::StateRem() {}

StateRem::~StateRem() {}

void StateRem::execute(EvalState &state) {}

StateLet::StateLet(TokenScanner& scanner) {
    exp = parseExp(scanner);
}

StateLet::~StateLet() {
    delete exp;
}

void StateLet::execute(EvalState &state) {
    exp->eval(state);
}

StateIf::StateIf() {}

StateIf::~StateIf() {}

void StateIf::execute(EvalState &state) {}

StateInput::StateInput(Expression* ptr) {
    exp=ptr;
}

StateInput::~StateInput() {
    delete exp;
}

void StateInput::execute(EvalState &state) {
    int a=stringToInteger(getLine("?"));
}

StatePrint::StatePrint(Expression* ptr) {
    exp=ptr;
}

StatePrint::~StatePrint() {
    delete exp;
}

void StatePrint::execute(EvalState &state) {
    cout<<exp->eval(state);
}

StateEnd::StateEnd() {}

StateEnd::~StateEnd() {}

void StateEnd::execute(EvalState &state) {}

StateGoto::StateGoto() {}

StateGoto::~StateGoto() {}

void StateGoto::execute(EvalState &state) {}