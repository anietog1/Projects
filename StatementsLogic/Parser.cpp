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
