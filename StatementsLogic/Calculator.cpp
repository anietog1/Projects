#include "Calculator.h"

using namespace std;

Calculator* Calculator::instance = NULL;

Calculator::~Calculator(){}

Calculator* Calculator::getInstance(){
  if(instance == NULL)
    instance = new Calculator();

  return instance;
}

bool& operator[](const string& idname){
  return idvalues[idname];
}
