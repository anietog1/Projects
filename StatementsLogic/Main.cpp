#include <cstdlib>

using namespace std;

Calculator* calc = Calculator::getInstance();

void runInterpreter(){
  string line;
  while(getline(cin, line)){
      
  }
}

void execute(ifstream* file){
  
}

int main(int argc, char** argv){  
  if(argc == 1){
    runInterpreter();
  } else {
    for(int i=1; i < argc; ++i){
      ifstream file(argv[i]);
      execute(&file);
      file.close();
    }
  }


  return EXIT_SUCCESS;
}
