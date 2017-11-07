#pragma once

#include "AST.h"
#include "Scanner.h"

class Parser {
 public:
   Parser(ifstream* in);
   ~Parser();
   AST* nextEvaluation();
 private:
   AST* exe();
   AST* inits();
   AST* init();
   AST* funcs();
   AST* func();
   AST* statement();
   AST* operator();
   
   Scanner* scan;
};
