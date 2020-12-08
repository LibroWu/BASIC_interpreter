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

Statement *parseState(string line, bool flag) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);
    string first_token, token;
    if (flag) {
        first_token = scanner.nextToken();
    }
    Statement *sta = nullptr;
    Expression *exp = nullptr;
    Expression *exp1 = nullptr;
    Expression *exp2 = nullptr;
    first_token = scanner.nextToken();
    if (first_token == "LET") {
        try {
            sta = new StateLet(scanner);
            return sta;
        }
        catch (ErrorException err) {
            if (sta != nullptr) delete sta;
            throw err;
        } catch (...) {

        }
    } else if (first_token == "PRINT") {
        try {
            exp = parseExp(scanner);
            if (exp->getType()==COMPOUND)
                if (((CompoundExp*)exp)->getOp()=="=") error("SYNTAX ERROR");
            sta = new StatePrint(exp);
            return sta;
        } catch (ErrorException err) {
            if (exp != nullptr) delete exp;
            if (sta != nullptr) delete sta;
            throw err;
        }
    } else if (first_token == "INPUT") {
        try {
            exp = parseExp(scanner);
            if (exp->getType() != IDENTIFIER) throw invalid_argument("");
            return new StateInput(exp);
        } catch (...) {
            if (exp != nullptr) delete exp;
        }
    } else if (first_token == "REM") {
        return new StateRem;
    } else if (first_token == "END") {
        return new StateEnd;
    } else if (first_token == "IF") {
        if (line.find("=") == string::npos) {
            exp1 = readE(scanner);
            string cmp = scanner.nextToken();
            exp2 = readE(scanner);
            string tmp = scanner.nextToken();
            tmp = scanner.nextToken();
            int line_number = stringToInteger(tmp);
            if ((cmp != "=" && cmp != "<" && cmp != ">") || scanner.hasMoreTokens()) {
                delete exp1;
                delete exp2;
                error("SYNTAX ERROR");
            }
            return new StateIf(exp1, cmp, exp2, line_number);
        }else {
            string token,s1,s2;
            while (scanner.hasMoreTokens()){
                token=scanner.nextToken();
                if (token=="=") break;
                s1+=token+' ';
            }
            while (scanner.hasMoreTokens()){
                token=scanner.nextToken();
                if (token=="THEN") break;
                s2+=token+' ';
            }
            if (scanner.hasMoreTokens())
                token=scanner.nextToken();
            else throw invalid_argument("");
            scanner.setInput(s1);
            exp1=parseExp(scanner);
            scanner.setInput(s2);
            exp2=parseExp(scanner);
            int line_number=stringToInteger(token);
            return new StateIf(exp1,"=",exp2,line_number);
        }
    } else if (first_token == "GOTO") {
        string s = scanner.nextToken();
        if (scanner.hasMoreTokens()) throw invalid_argument("");
        int lineNumber = stringToInteger(s);
        return new StateGoto(lineNumber);
    } else error("SYNTAX ERROR");
}

StateRem::StateRem() {}

StateRem::~StateRem() {}

void StateRem::execute(EvalState &state) {}

StateLet::StateLet(TokenScanner &scanner) {
    exp = parseExp(scanner);
    if (exp->getType()!=COMPOUND) error("SYNTAX ERROR");
    if (((CompoundExp*)exp)->getOp()!="=") error("SYNTAX ERROR");
}

StateLet::~StateLet() {
    delete exp;
}

void StateLet::execute(EvalState &state) {
    exp->eval(state);
}

StateIf::StateIf(Expression *exp_1, string cmp_, Expression *exp_2, int line_num) {
    exp1 = exp_1;
    exp2 = exp_2;
    cmp = cmp_;
    Goto_lineNumber = line_num;
}

StateIf::~StateIf() {
    delete exp1;
    delete exp2;
}

void StateIf::execute(EvalState &state) {
    if (cmp == "=") {
        if (exp1->eval(state) == exp2->eval(state))
            throw ControlClass(1, Goto_lineNumber);
        else throw ControlClass(2);
    } else if (cmp == ">") {
        if (exp1->eval(state) > exp2->eval(state))
            throw ControlClass(1, Goto_lineNumber);
        else throw ControlClass(2);
    } else if (cmp == "<") {
        if (exp1->eval(state) < exp2->eval(state))
            throw ControlClass(1, Goto_lineNumber);
        else throw ControlClass(2);
    }
}

StateInput::StateInput(Expression *ptr) {
    exp = ptr;
}

StateInput::~StateInput() {
    delete exp;
}

void StateInput::execute(EvalState &state) {
    int val;
    while (true) {
        try {
            val = stringToInteger(getLine(" ? "));
        } catch (...) {
            cout<<"INVALID NUMBER"<<endl;
            continue;
        }
        break;
    }
    state.setValue(((IdentifierExp *) exp)->getName(), val);
}

StatePrint::StatePrint(Expression *ptr) {
    exp = ptr;
}

StatePrint::~StatePrint() {
    delete exp;
}

void StatePrint::execute(EvalState &state) {
    cout << exp->eval(state) << endl;
}

StateEnd::StateEnd() {}

StateEnd::~StateEnd() {}

void StateEnd::execute(EvalState &state) {
    throw ControlClass(0);
}

StateGoto::StateGoto(int Number) {
    lineNumber = Number;
}

StateGoto::~StateGoto() {}

void StateGoto::execute(EvalState &state) {
    throw ControlClass(1, lineNumber);
}