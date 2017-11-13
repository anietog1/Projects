#pragma once

#include <iostream>
#include "Token.h"

enum ScannerState {//SEARCHING_ changed for S_
  S_ID, S_ASSIGN, S_LPAREN, S_RPAREN, S_NEG,
  S_AND, S_OR, S_IMPL, S_EQUIV, S_QUERY
};

class Scanner {
 public:
  Scanner(std::istream* in);
  ~Scanner();
  Token* getToken();
  void putBackToken();
 private:
  Scanner();
  std::istream* inStream;
  int lineCount;
  int colCount;
  bool needToken;
  Token* lastToken;
};
