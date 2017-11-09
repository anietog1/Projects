#include <map>
#include <string>

class Calculator {
 public:
  Calculator();
  bool getBoolValue(std::string id);
  void setValue(std::string id, bool value);
 private:
  std::map<std::string, bool> idvalues;
};
