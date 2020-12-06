/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"
using namespace std;

Program::Program() {
    list_of_program.clear();
   setParsedStatement(end_line,parseState("END",0));
}

Program::~Program() {
   // Replace this stub with your own code
    clear();
    delete list_of_program[end_line].sta;
}

void Program::clear() {
    auto iter=list_of_program.begin();
    while (iter!=list_of_program.end()){
        delete iter->second.sta;
    }
    list_of_program.clear();
    setParsedStatement(end_line,parseState("END",0));
}

void Program::addSourceLine(int lineNumber, string line) {
    if (list_of_program.count(lineNumber)){
        delete list_of_program[lineNumber].sta;
        list_of_program[lineNumber].line=line;
        setParsedStatement(lineNumber,parseState(line,1));
    }
    else {
        list_of_program[lineNumber].line=line;
        setParsedStatement(lineNumber,parseState(line,1));
    }
}

void Program::removeSourceLine(int lineNumber) {
    auto iter=list_of_program.find(lineNumber);
    delete iter->second.sta;
    list_of_program.erase(lineNumber);
}

string Program::getSourceLine(int lineNumber) {
   auto iter=list_of_program.find(lineNumber);
   return iter->second.line;
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
   list_of_program[lineNumber].sta=stmt;
}

Statement *Program::getParsedStatement(int lineNumber) {
   auto iter=list_of_program.find(lineNumber);
   return iter->second.sta;
}

int Program::getFirstLineNumber() {
    return list_of_program.begin()->first;
}

int Program::getNextLineNumber(int lineNumber) {
    auto iter=list_of_program.find(lineNumber);
    iter++;
    if (iter==list_of_program.end()) return end_line;
    return iter->first;
}

void Program::run_program(EvalState& state) {
    int num=getFirstLineNumber();
    while (num!=end_line){
        try {
            getParsedStatement(num)->execute(state);
        } catch (...) {

        }
        num=getNextLineNumber(num);
    }
}
void Program::show_list() {
    int num=getFirstLineNumber();
    while (num!=end_line){
        cout<<getSourceLine(num)<<'\n';
        num=getNextLineNumber(num);
    }
}
void Program::show_help() {}