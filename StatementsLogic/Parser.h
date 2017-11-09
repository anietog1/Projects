#pragma once

#include "AST.h"
#include "Scanner.h"

class Parser {
 public:
   Parser(ifstream* in);
   ~Parser();
   AST* nextEvaluation();
 private:
   AST* func();
   AST* statement();
   AST* operate();
   
   Scanner* scan;
};
