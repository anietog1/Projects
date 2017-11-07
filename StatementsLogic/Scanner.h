#pragma once

#include <iostream>
#include "Token.h"

enum ScannerState {
  SEARCHING_ID, SEARCHING_OPERATOR, BLANK
};

class Scanner {
 public:
  Scanner(std::ifstream* in);
  ~Scanner();
  Token* getToken();
  void putBackToken();
 private:
  Scanner();
  std::ifstream* inStream;
  int lineCount;
  int colCount;
  bool needToken;
  Token* lastToken;
};
