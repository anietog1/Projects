#include "Parser.h"
#include "Exceptions.h"

using namespace std;

AST* Parser::executable() {
}

AST* Parser::lines() {
}

AST* Parser::line() {
  
}

AST* Parser::declaration() {
  bool isGood = true;
  string idname;
  AST* ret;

  Token* t = scanner->getToken();
  
  if(t->getType() == ID){
    idname = t->getLex();
    t = scanner->getToken();
    
    if(t->getType() == ASSIGN){
      ret = new AssignNode(expression(), idname);
    }else
      isGood = false;
  }else
    isGood = false;

  if(!isGood)
    //Throw anything
    throw ParseError;
  else
    return ret;
}

AST* Parser::expression() {
  return restExpression(statement());
}

AST* Parser::restExpression(AST* left) {
  Token* t = scanner->getToken();
  AST* ret;
  
  switch (t->getType()) {
  case AND:
    ret = new AndNode(left, multAnd());
    break;
  case OR:
    ret = new OrNode(left, multOr());
    break;
  case IMPL:
    ret = new ImplNode(left, statement());
    break;
  case EQUIV:
    ret = new EquivNode(left, statement());
    break;
  default:
    scanner->putBackToken();
    ret = left;
    break;
  }
  
  return ret;
}

AST* Parser::multAnd() {
  return restMultAnd(statement());
}

AST* Parser::restMultAnd(AST* left) {
  Token* t = scanner->getToken();
  AST* ret;
  
  if(t->getType() == AND){
    ret = new AndNode(left, multAnd());
  }else{
    ret = left;
    scanner->putBackToken();
  }
  
  return ret;
}

AST* Parser::multOr() {
  return restMultOr(statement());
}

AST* Parser::restMultOr(AST* left) {
  Token* t = scanner->getToken();
  AST* ret;
  
  if(t->getType() == OR){
    ret = new OrNode(left, multOr());
  }else{
    ret = left;
    scanner->putBackToken();
  }

  return ret;
}

AST* Parser::statement() {
  Token* t = scanner->getToken();
  AST* ret;
  
  switch(t->getType()){
  case ID:
    {
      string idname = t->getLex();
    
      if(calc->contains(idname))
	ret = new StatementNode(calc->getValue(idname));
      else{
	cerr << "Variable with name \"" << idname
	     << "\" doesn't exists." << endl;

	throw PARSE_ERROR;
      }
    }
    break;
  case KEYWORD:
    {
      string kw = t->getLex();
      if(kw == "true")
	ret = new StatementNode(true);
      else if(kw == "false")
	ret = new StatementNode(false);
      else{
	cerr << "Unrecognized keyword: \"" << kw << "\", at line "
	     << t->getLine() << " and column " << t->getColumn() << "." << endl;

	throw PARSE_ERROR;
      }
    }
    break;
  case LPAREN:
    ret = expression();
    t = scanner->getToken();

    if(t->getType != RPAREN){
      cerr << "Expected ')' at line " << t->getLine()
	   << " and column " << t->getColumn() << "." << endl;
    }
    break;
  case NEG:
    ret = new NegNode(statement());
    break;
  default:
    cerr << "Parse error at line " << t->getLine()
	 << " and column " << t->getColumn() << "." << endl;
    break;
  }

  return ret;
}
