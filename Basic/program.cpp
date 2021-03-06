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
#include "../StanfordCPPLib/error.h"

using namespace std;

Program::Program() {
    list_of_program.clear();
}

Program::~Program() {
    clear();
}

void Program::clear() {
    auto iter = list_of_program.begin();
    while (iter != list_of_program.end()) {
        delete iter->second.sta;
        ++iter;
    }
    list_of_program.clear();
}

void Program::addSourceLine(int lineNumber, string line) {
    if (list_of_program.count(lineNumber)) {
        Statement *tmp= nullptr;
        try {
            tmp = parseState(line, 1);
        } catch (ErrorException err) {
            if (tmp!= nullptr) delete tmp;
            throw err;
        }
        delete list_of_program[lineNumber].sta;
        list_of_program[lineNumber].line=line;
        setParsedStatement(lineNumber, tmp);
    } else {
        try {
            if (lineNumber <= 0) error("LINE NUMBER ERROR");
            list_of_program[lineNumber].line = line;
            setParsedStatement(lineNumber, parseState(line, 1));
        } catch (ErrorException err) {
            cout << err.getMessage() << endl;
            delete list_of_program[lineNumber].sta;
            list_of_program.erase(lineNumber);
        }
    }
}

void Program::removeSourceLine(int lineNumber) {
    auto iter = list_of_program.find(lineNumber);
    if (iter != list_of_program.end()) {
        delete iter->second.sta;
        list_of_program.erase(lineNumber);
    }
}

string Program::getSourceLine(int lineNumber) {
    auto iter = list_of_program.find(lineNumber);
    return iter->second.line;
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    list_of_program[lineNumber].sta = stmt;
}

Statement *Program::getParsedStatement(int lineNumber) {
    auto iter = list_of_program.find(lineNumber);
    return iter->second.sta;
}

int Program::getFirstLineNumber() {
    if (list_of_program.empty()) return end_line;
    return list_of_program.begin()->first;
}

int Program::getNextLineNumber(int lineNumber) {
    auto iter = list_of_program.find(lineNumber);
    iter++;
    if (iter == list_of_program.end()) return end_line;
    return iter->first;
}

void Program::run_program(EvalState &state) {
    int num = getFirstLineNumber();
    while (num != end_line) {
        try {
            getParsedStatement(num)->execute(state);
        } catch (ControlClass C) {
            if (C.type == 0) { break; }
            if (C.type == 1) {
                if (list_of_program.count(C.line_number)) {
                    num = C.line_number;
                    continue;
                } else cout << "LINE NUMBER ERROR" << endl;
            }
        }
        catch (ErrorException err) {
            cout << err.getMessage() << endl;
        }
        catch (...) {

        }
        num = getNextLineNumber(num);
    }
}

void Program::show_list() {
    int num = getFirstLineNumber();
    while (num != end_line) {
        cout << getSourceLine(num) << '\n';
        num = getNextLineNumber(num);
    }
}

void Program::show_help() {
    cout<<"Now you are using the Minimal BASIC Interpreter extended by Libro\n"
          "Here are tips to use it\n"
          "Use command HELP to get help\n"
          "Use command LIST to show the program which has been stored\n"
          "Use command RUN to run the program\n"
          "Use command CLEAR to clear the program and the variable table\n"
          "Lines without numbers can be executed immediately\n"
          "Now you have learned how to write a program\n"
          "Have a try\n";
}