#include <map>
#include <string>

class Calculator {
 public:
  ~Calculator();
  static Calculator* getInstance();
  bool& operator[](const std::string& idname);
 private:
  std::map<std::string, bool> idvalues;
  //Singleton
  static Calculator* instance;//Onliest instance
  Calculator();//Not allowing to instantiate
  Calculator(const Calculator& other);//Not allowing to copy
  Calculator& operator=(const Calculator& other);//Not allowing to assign
};
