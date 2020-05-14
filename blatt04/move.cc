#include <iostream>

class A{
public:
  A (){ std::cout << "default ctor" << std::endl;}
  A (const A&) { std::cout << "copy ctor" << std::endl;}
  ~A(){};

  A& operator=(const A&){ std::cout << "copy assignment" << std::endl;
    return *this;
  }
};

A operator+(const A&, const A&){
  A tmp;
  return tmp;
}

int main(){
  A x;
  A y;
  A z;

  std::cout << std::endl << "======================================" << std::endl << std::endl;

  // Modifizieren Sie die Klasse A, so dass bei der Auswerung
  // folgender Anweisung nur einmal der default ctor und keinmal der
  // copy ctor aufgerufen wird:
  A v = z + x + y;

  std::cout << std::endl << "======================================" << std::endl << std::endl;

  // Benutzen Sie std::move um folgenden Ausdruck zu modifizieren,
  // sodass der keinmal der default ctor aufgerufen wird:
  v = std::move(v) + y + z;
  return 0;
}
