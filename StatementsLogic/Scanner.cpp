#include "Scanner.h"
#include "Exceptions.h"
#include <cctype>
#include <cstdio>

using namespace std;
//#define debug

const int numberOfKeywords = 2;

const string keywords[numberOfKeywords] = {
  string("true"), string("false")
};

Scanner::Scanner(istream* in):
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
  string* lex;

  ScannerState state = BLANK;
  bool foundOne = false;

  int column, line,
    c = inStream->get();

  while (!foundOne) {
    colCount += 1;

    switch (state) {
    case BLANK:
      lex = new string();
      column = colCount;
      line = lineCount;

      if (isalpha(c))
	state = S_ID;
      else if(isblank(c));//ignore
      else if(c == EOF || inStream->eof()) {
	foundOne = true;
	type = _EOF;
      }else {
	switch(c){
	case '=':
	  state = S_ASSIGN;
	  break;
	case '(':
	  state = S_LPAREN;
	  break;
	case ')':
	  state = S_RPAREN;
	  break;
	case '!':
	  state = S_NEG;
	  break;
	case '&':
	  state = S_AND;
	  break;
	case '|':
	  state = S_OR;
	  break;
	case '-':
	  state = S_IMPL;
	  break;
	case '<':
	  state = S_EQUIV;
	  break;
	case '?':
	  state = S_QUERY;
	  break;
	case '\n':
	  colCount = -1;
	  lineCount += 1;
	  state = S_EOL;
	  break;
	default:
	  //something wrong
	  foundOne = true;
	  type = UNRECOGNIZED;
	  break;
	}
      }
      break;
    case S_ID:
      if(!isalpha(c)){
	foundOne = true;
	type = ID;

	for(int i=0; i<numberOfKeywords; ++i)
	  if(*lex == keywords[i])
	    type = KEYWORD;
      }
      break;
    case S_ASSIGN:
      foundOne = true;
      type = ASSIGN;
      break;
    case S_LPAREN:
      foundOne = true;
      type = LPAREN;
      break;
    case S_RPAREN:
      foundOne = true;
      type = RPAREN;
      break;
    case S_NEG:
      foundOne = true;
      type = NEG;
      break;
    case S_AND:
      foundOne = true;
      type = AND;
      break;
    case S_OR:
      foundOne = true;
      type = OR;
      break;
    case S_IMPL:
      if(lex->length() >= 2){
	foundOne = true;

	if((*lex) == "->")
	  type = IMPL;
	else
	  type = UNRECOGNIZED;
      }
      break;
    case S_EQUIV:
      if(lex->length() >= 3){
	foundOne = true;

	if((*lex) == "<->")
	  type = EQUIV;
	else
	  type = UNRECOGNIZED;
      }
      break;
    case S_QUERY:
      foundOne = true;
      type = QUERY;
      break;
    case S_EOL:
      foundOne = true;
      type = _EOL;
      break;
    }

    if(!foundOne){
      *lex += static_cast<char>(c);
      c = inStream->get();
    }
  }

  inStream->putback(c);
  colCount -= 1;

  if(type == UNRECOGNIZED) {
    cerr << "Unrecognized token: \"" << *lex << "\" found at line " << line
	 << " and column " << column << "." << endl;

    throw UNRECOGNIZED_TOKEN;
  }

  Token* t;
  if (type == ID || type == KEYWORD) {
    t = new LexicalToken(type, lex, line, column);
  } else {
    t = new Token(type, line, column);
  }

#ifdef debug
  cout << "Found \"" << *lex << "\", with type " << t->getType() << endl;
#endif

  return (lastToken = t);
}
