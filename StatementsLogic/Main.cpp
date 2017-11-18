#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include "Exceptions.h"
#include "Calculator.h"
#include "Parser.h"
#include "AST.h"
#include "Scanner.h"

using namespace std;

Calculator* calc = Calculator::getInstance();

AST* eval(const string& line){
  Parser* parser = new Parser(new istringstream(line));
  AST* tree = parser->parse();
  delete parser;
  return tree;
}

void runInterpreter(){
  string line;
  while(getline(cin, line)){
    AST* expr;

    try{
      line += '\n';
      expr = eval(line);
      expr->evaluate();
    }catch(Exception ex){
      cout << "*Exception caught." << endl;
    }
    
    delete expr;
  }

}

void execute(const ifstream& file){
  cout << "Executing..." << endl;
  char line[100] = {};

  try{
    while(file.getline(line, 100)){
      string sline = string(line);
      sline += '\n';
      AST* expr = eval(sline);
      expr->evaluate();
    
      delete expr;
    }
  }catch(Exception ex){
    cout << "*Exception caught. Can't continue running." << endl;
  }
}

int main(int argc, char** argv){  
  if(argc == 1){
    runInterpreter();
  } else {
    for(int i=1; i < argc; ++i){
      ifstream file(argv[i]);
      execute(file);
      file.close();
    }
  }
  
  return EXIT_SUCCESS;
}
