#include "Scanner.h"
#include "Exceptions.h"
#include <iostream>
#include <string>
#include <cctype>
#include <cstdio>

using namespace std;

const int numberOfKeywords = 2;

const string keywords[numberOfKeywords] = {
  string("true"), string("false")
};

void unrecognizedTokenAt(int line, int column, const string &lex){
  cerr << "Unrecognized token: \"" << lex
       << "\" found at line " << line
       << " and column " << column << endl;
  
  throw UNRECOGNIZED_TOKEN;
}

TokenType getOperator(const string &lex){
  TokenType type;
  
  switch(lex){
  case "{":
    type = LKEY;
    break;
  case "}":
    type = RKEY;
    break;
  case "(":
    type = LPAREN;
    break;
  case ")":
    type = RPAREN;
    break;
  case ",":
    type = COMMA;
    break;
  case "=":
    type = ASSIGN;
    break;
  case "!":
    type = NEG;
    break;
  case "&":
    type = AND;
    break;
  case "|":
    type = OR;
    break;
  case "->":
    type = IMPL;
    break;
  case "<->":
    type = EQUIV;
    break;
  case "?":
    type = QUERY;
    break;
  default:
    type = UNRECOGNIZED;
    break;
  }

  return type;
}

Scanner::Scanner(ifstream* in):
  inStream(in),
  lineCount(1),
  colCount(-1),
  needToken(true),
  lastToken(NULL)
{}

Scanner::~Scanner() {
  try {
    delete inStream;
  } catch (...) {}
}

void Scanner::putBackToken() {
  needToken = false;
}

Token* Scanner::getToken() {
  if (!needToken) {
    needToken = true;
    return lastToken;
  }

  TokenType type;
  string lex;
  
  ScannerState state = BLANK;
  bool foundOne = false;

  int column, line,
    c = inStream -> get();

  while (!foundOne) {
    colCount += 1;

    switch (state) {
    case BLANK:
      lex = "";
      column = colCount;
      line = lineCount;
      
      if (isalpha(c))
	state = SEARCHING_ID;
      else if (ispunct(c))
	state = SEARCHING_OPERATOR;
      else if (c == '\n') {
	colCount = -1;
	lineCount += 1;
      }
      else if (isspace(c));//ignore
      else if (c == EOF || inStream -> eof()) {
	foundOne = true;
	type = END;
      }
      else {
	unrecognizedTokenAt(line, column, lex);//EXC
      }
      break;
    case SEARCHING_ID:
      if (isalpha(c));//state = SEARCHING_ID
      else {
	type = ID;
	foundOne = true;
      }
      break;
    case SEARCHING_OPERATOR:
      if (ispunct(c));
      else{
	type = OPERATOR;
	foundOne = true;
      }
      break;
    }
    
    if (!foundOne) {
      lex += static_cast<char>(c);
      c = inStream->get();
    }
  }

  inStream->putback(c);
  colCount -= 1;
  
  Token* t;
  if (type == ID) {
    for(int i=0; i < numberOfKeywords; ++i)
      if(lex == keywords[i]) {
	type = KEYWORD;
      }
    
    t = new LexicalToken(type, new string(lex), line, column);
  } else if (type == OPERATOR) {
    type = getTokenType(lex);

    if(type == UNRECOGNIZED)
      unrecognizedTokenAt(line, column, lex);
    
    t = new Token(type, line, column);
  }
  
  return (lastToken = t);
}
