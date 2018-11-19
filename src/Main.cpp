#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <istream>

#include "Exceptions.h"
#include "Calculator.h"
#include "Parser.h"
#include "AST.h"
#include "Scanner.h"

using namespace std;

AST* eval(const string& line){
  Parser* parser = new Parser(new istringstream(line));
  AST* tree = parser->parse();
  delete parser;
  
  return tree;
}

void runInterpreter(){
  string line;
  cout << "> ";
  while(getline(cin, line)){
    AST* expr = NULL;

    try{
      line += '\n';
      expr = eval(line);
      expr->evaluate();
    }catch(Exception ex){
      cout << "*Exception caught." << endl;
    }
    
    delete expr;
    cout << "> ";
  }
}

void execute(ifstream& file){
  string line;
  
  try{
    while(getline(file, line)){
      line += '\n';
      AST* expr = eval(line);
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
      //      cout << "Executing " << argv[i] << "..." << endl;
      execute(file);
      file.close();
    }
  }
  
  return EXIT_SUCCESS;
}
