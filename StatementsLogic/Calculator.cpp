#include "Calculator.h"

using namespace std;

Calculator* Calculator::instance = NULL;

Calculator* Calculator::getInstance(){
  if(instance == NULL)
    instance = new Calculator();

  return instance;
}

bool Calculator::contains(const string& id){
  return idvalues.count(id);
}

bool Calculator::getValue(const string& id){
  return idvalues[id];
}

void Calculator::setValue(const string& id, bool value){
  idvalues[id] = value;
}
