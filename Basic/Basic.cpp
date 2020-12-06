/*
 * File: Basic.cpp
 * ---------------
 * Name: [TODO:Libro]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);

/* Main program */

int main() {
   EvalState state;
   Program program;
   cout << "Stub implementation of BASIC" << endl;
   while (true) {
      try {
         processLine(getLine(), program, state);
      } catch (ErrorException & ex) {
         cerr << "Error: " << ex.getMessage() << endl;
      }
   }
   return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program & program, EvalState & state) {
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(line);
   string token;
   if (scanner.hasMoreTokens()) token=scanner.nextToken();
   TokenType token_Type=scanner.getTokenType(token);
   if (token_Type == NUMBER) {
       int line_number=stringToInteger(token);
       if (scanner.hasMoreTokens())
           program.addSourceLine(line_number,line);
       else program.removeSourceLine(line_number);
   }
   else if (!scanner.hasMoreTokens()) {
       if (token == "LIST") {program.show_list();}
       else
       if (token == "RUN") {program.run_program(state);}
       else
       if (token == "CLEAR") { program.clear(); }
       else
       if (token == "HELP") {Program::show_help();}
       else
       if (token == "QUIT") {exit(0);}
       else throw invalid_argument("");
   }else {
       try {
           if (token=="IF") throw invalid_argument("");
           if (token=="GOTO") throw invalid_argument("");
           Statement *sta = parseState(line, 0);
           sta->execute(state);
           delete sta;
       } catch (...) {

       }
   }
/*
   Expression *exp = parseExp(scanner);
   int value = exp->eval(state);
   cout << value << endl;
   delete exp;
*/
}
