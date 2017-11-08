#include "Scanner.h"
#include "Exceptions.h"
#include <string>
#include <cctype>
#include <cstdio>

using namespace std;
#define debug

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
  if(lex == "{")
    type = LKEY;
  else if(lex == "}")
    type = RKEY;
  else if(lex == "(")
    type = LPAREN;
  else if(lex == ")")
    type = RPAREN;
  else if( lex ==  ",")
    type = COMMA;
  else if( lex ==  "=")
    type = ASSIGN;
  else if( lex ==  "!")
    type = NEG;
  else if( lex ==  "&")
    type = AND;
  else if( lex ==  "|")
    type = OR;
  else if( lex ==  "->")
    type = IMPL;
  else if( lex ==  "<->")
    type = EQUIV;
  else if( lex ==  "?")
    type = QUERY;
  else
    type = UNRECOGNIZED;

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
    c = inStream->get();

  while (!foundOne) {
    colCount += 1;

    switch (state) {
    case BLANK:
      lex = "";
      column = colCount;
      line = lineCount;
      
      if (isalpha(c))
	state = SEARCHING_ID;
      else if (c == '(' || c == ')' || c == '{' || c == '}')
	state = SEARCHING_GROUPING_SIGN;
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
    case SEARCHING_GROUPING_SIGN:
      type = OPERATOR;
      foundOne = true;
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
    type = getOperator(lex);

    if(type == UNRECOGNIZED)
      unrecognizedTokenAt(line, column, lex);
    
    t = new Token(type, line, column);
  } else {
    t = new Token(type, line, column);
  }

#ifdef debug
  cout << "Found \"" << lex << "\", with type " << t->getType() << endl;
#endif
  
  return (lastToken = t);
}
