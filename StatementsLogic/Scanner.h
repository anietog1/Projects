#pragma once

#include <iostream>
#include <fstream>
#include "Token.h"

enum ScannerState {
  SEARCHING_ID, SEARCHING_OPERATOR, SEARCHING_GROUPING_SIGN, BLANK
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
