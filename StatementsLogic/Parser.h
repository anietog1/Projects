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
  AST* restexpression(AST* left);
  AST* multand();
  AST* restmultand(AST* left);
  AST* multor();
  AST* restmultor(AST* left);
  AST* statement();
   
  Scanner* scan;
};
