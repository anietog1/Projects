#include "Parser.h"
#include "Exceptions.h"

using namespace std;

Parser::Parser(istream* in){
  scan = new Scanner(in);
}

Parser::~Parser(){
  try {
    delete scan;
  }catch(...){}
  
  scan = nullptr;
}

AST* Parser::parse(){
  return executable();
}

AST* Parser::executable() {
  Token* t = scan->getToken();
  AST* ret;
  
  if(t->getType() == _EOL) {
    ret = new StatementNode(false);
    delete t;
  } else {
    scan->putBackToken();
    ret = line();
    t = scan->getToken();

    if(t->getType() != _EOL){
      cerr << "Expected EOL." << endl;
      delete t;
      throw PARSE_ERROR;
    } else {
      delete t;
    }
  }
  
  return ret;
}

AST* Parser::line() {
  Token* t = scan->getToken();
  AST* ret;
  
  if(t->getType() == QUERY) {
    ret = new QueryNode(expression());
    delete t;
  } else {
    scan->putBackToken();
    ret = declaration();
  }
  
  return ret;
}

AST* Parser::declaration() {
  AST* ret;
  Token* t = scan->getToken();
  
  if(t->getType() == ID){
    string idname = t->getLex();
    delete t;
    t = scan->getToken();
    
    if(t->getType() == ASSIGN){
      ret = new AssignNode(idname, expression());
      delete t;
    } else {
      cerr << "Expected '='" << endl;
      delete t;
      throw PARSE_ERROR;
    }
  } else {
    cerr << "Expected ID" << endl;
    delete t;
    throw PARSE_ERROR;
  }
  
  return ret;
}

AST* Parser::expression() {
  return restExpression(statement());
}

AST* Parser::restExpression(AST* left) {
  Token* t = scan->getToken();
  AST* ret;
  
  switch (t->getType()) {
  case AND:
    delete t;
    ret = new AndNode(left, multAnd());
    break;
  case OR:
    delete t;
    ret = new OrNode(left, multOr());
    break;
  case IMPL:
    delete t;
    ret = new ImplNode(left, statement());
    break;
  case EQUIV:
    delete t;
    ret = new EquivNode(left, statement());
    break;
  default:
    scan->putBackToken();
    ret = left;
    break;
  }
  
  return ret;
}

AST* Parser::multAnd() {
  return restMultAnd(statement());
}

AST* Parser::restMultAnd(AST* left) {
  Token* t = scan->getToken();
  AST* ret;
  
  if(t->getType() == AND){
    delete t;
    ret = new AndNode(left, multAnd());
  }else{
    ret = left;
    scan->putBackToken();
  }
  
  return ret;
}

AST* Parser::multOr() {
  return restMultOr(statement());
}

AST* Parser::restMultOr(AST* left) {
  Token* t = scan->getToken();
  AST* ret;
  
  if(t->getType() == OR){
    delete t;
    ret = new OrNode(left, multOr());
  }else{
    ret = left;
    scan->putBackToken();
  }

  return ret;
}

AST* Parser::statement() {
  Token* t = scan->getToken();
  AST* ret;
  
  switch(t->getType()){
  case ID:
    {
      ret = new IdNode(t->getLex());
      delete t;
    }
    break;
  case KEYWORD:
    {
      string kw = t->getLex();
      
      if(kw == "true"){
	ret = new StatementNode(true);
        delete t;
      }else if(kw == "false") {
	ret = new StatementNode(false);
        delete t;
      }else{
	cerr << "Invalid keyword: \"" << kw << "\", at line "
	     << t->getLine() << " and column " << t->getCol() << "." << endl;
        delete t;
	throw PARSE_ERROR;
      }
    }
    break;
  case LPAREN:
    delete t;
    ret = expression();
    t = scan->getToken();

    if(t->getType() != RPAREN){
      cerr << "Expected ')' at line " << t->getLine()
	   << " and column " << t->getCol() << "." << endl;
      delete t;
      throw PARSE_ERROR;
    }
    break;
  case NEG:
    ret = new NegNode(statement());
    delete t;
    break;
  default:
    cerr << "Parse error at line " << t->getLine()
	 << " and column " << t->getCol() << ". Expected ID | ( | ! | true | false" << endl;
    delete t;
    throw PARSE_ERROR;
    break;
  }

  return ret;
}
