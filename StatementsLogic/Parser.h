#pragma once

#include "AST.h"
#include "Scanner.h"

class Parser {
 public:
  Parser(std::istream* in);
  ~Parser();
  AST* parse();
 private:
  AST* executable();
  AST* lines();
  AST* line();
  AST* declaration();
  AST* expression();
  AST* restExpression(AST* left);
  AST* multAnd();
  AST* restMultAnd(AST* left);
  AST* multOr();
  AST* restMultOr(AST* left);
  AST* statement();
   
  Scanner* scan;
};
