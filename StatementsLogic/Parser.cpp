#include "Parser.h"
#include "Exceptions.h"

using namespace std;

AST* Parser::executable() {
  Token* t = scanner->getToken();
  AST* ret;
  
  if(t->getType() == _EOL)
    ret = new StatementNode(false);
  else {
    scanner->putBackToken();
    ret = line();
    t = scanner->getToken();
    if(t->getType() != _EOL){
      cerr << "Expected EOL." << endl;
      throw PARSE_ERROR;
    }
  }
  return ret;
}

AST* Parser::line() {
  Token* t = scanner->getToken();
  AST* ret;
  
  if(t->getType() == QUERY)
    ret = new QueryNode(expression());
  else{
    scanner->putBackToken();
    ret = declaration();
  }
  
  return ret;
}

AST* Parser::declaration() {
  AST* ret;
  Token* t = scanner->getToken();
  
  if(t->getType() == ID){
    string& idname = t->getLex();
    t = scanner->getToken();
    
    if(t->getType() == ASSIGN){
      ret = new AssignNode(idname, expression());
    } else {
      cerr << "Expected '='" << endl;
      throw PARSE_ERROR;
    }
  } else {
    cerr << "Expected ID" << endl;
    throw ParseError;
  }
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
      ret = new IdNode(t->getLex());
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
	cerr << "Invalid keyword: \"" << kw << "\", at line "
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
	 << " and column " << t->getColumn() << ". Expected ID | ( | ! | true | false" << endl;
    break;
  }

  return ret;
}
