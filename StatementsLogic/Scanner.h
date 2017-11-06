#pragma once

#include <iostream>
#include "Token.h"

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
