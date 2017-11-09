#include "Parser.h"
#include "Exceptions.h"

#include <string>
#include <sstream>

Parser::Parser(ifstream* in) {
   scan = new Scanner(in);
}

Parser::~Parser() {
   try {
      delete scan;
   } catch (...) {}
}

AST* Parser::func(){
  Token* t = scan->getToken();

  if(t->getType == NEG){
    return new NegNode(statement());
  }

  scan->putBackToken();
  AST* left = statement();
  
  t = scan->getToken();
}

AST* Parser::statement(){
  Token* t = scan->getToken();

  if(t->getType() == KEYWORD){
    if(t->getLex() == "true"){
      return new StatementNode(true);
    }else if(t->getLex() == "false"){
      return new StatementNode(false);
    }else {
      throw "anything";//asdf
    }
  }else if(t->getType == ID){
    return new StatementNode(idvalues(t->getLex()));
  }else if(t->getType == LPAREN){
    AST* sub = function();
    t = scan->getToken();
    
    if(t->getType() != RPAREN)
      throw "anything";//asdf
    else
      return sub;
  }else {
    throw "anything";//asdf
  }
}

AST* Parser::operate(){

}
