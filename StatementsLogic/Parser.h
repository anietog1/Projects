#pragma once

#include "ast.h"
#include "scanner.h"

class Parser {
 public:
   Parser(istream* in);
   ~Parser();

   AST* parse();

 private:
   AST* prog();
   AST* expr();
   AST* restExpr(AST* e);
   AST* term();
   AST* restTerm(AST* t);
   AST* storable();
   AST* factor();

   Scanner* scan;
};
/*
Grammar LL
 {
  {EOF, number, R, S, +, -, *, /,},
  {Prog, Expr, RestExpr, Term,
   RestTerm, Storable, Factor},
  {
   Prog -> Expr EOF,
   Expr -> Term RestExpr,
   RestExpr -> + Term RestExpr
              |- Term RestExpr
	      |,
   Term -> Storable RestTerm,
   RestTerm -> * Storable RestTerm
              |/ Storable RestTerm
	      |,
   Storable -> Factor S
              |Factor,
   Factor -> number
            |R
	    |(Expr)
  },
  Prog
 }
 */

/*
Grammar LALR(Previous):
{
 {EOF, num, R, S, +, -, +, /, (, )},
 {Prog, Expr, Term, Storable, Factor},
 {
  Prog -> Expr EOF,
  Expr -> Expr + Term
         |Expr - Term
	 |Term,
  Term -> Term * Storable
         |Term / Storable
	 |Storable,
  Storable -> Factor S
             |Factor,
  Factor -> number
           |R
	   |(Expr)
 },
 Prog
}
 */
