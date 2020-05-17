#include <assert.h>
#include <string>
#include <sstream>
#include <filesystem>
#include <iostream>

class MyInt
{
  int *_p; // pointer to heap data
public:
  MyInt(int *p = NULL) { _p = p; }
  ~MyInt()
  {
    std::cout << "resource " << *_p << " deallocated" << std::endl;
    delete _p;
  }
  int &operator*() { return *_p; } // // overload dereferencing operator
};

MyInt *getMyIntPtr() {
  MyInt *myint = new MyInt(new int(5004564));
  return myint;
}

MyInt getMyInt() {
  MyInt myint{new int(5004564)};
  return myint;
}

// Test
int main() {
  double den[] = {1.0, 2.0, 3.0, 4.0, 5.0};
  for (size_t i = 0; i< 5; ++i)
  {
    // allocate the resource on the stack
    MyInt en(new int(i));

    // use the resource
    std::cout << *en << "/" << den[i] << " = " << *en / den[i] << std::endl;
  }

  MyInt *int_i = getMyIntPtr();
  std::cout << "AFTER INT I CREATION." << std::endl;
  for (size_t i = 0; i< 10; ++i)
  {
    std::cout << **int_i << std::endl;
  }

  MyInt int_j = getMyInt();
  std::cout << "AFTER INT J CREATION." << std::endl;
  for (size_t i = 0; i< 10; ++i)
  {
    std::cout << *int_j << std::endl;
  }
  return 0;
}