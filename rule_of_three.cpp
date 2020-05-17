#include <stdlib.h>
#include <iostream>

class MyMovableClass
{
private:
  int _size;
  int *_data;

public:
  MyMovableClass(size_t size) // constructor
  {
    _size = size;
    _data = new int[_size];
    std::cout << "CREATING instance of MyMovableClass at " << this << " allocated with size = " << _size*sizeof(int)  << " bytes" << std::endl;
  }

  ~MyMovableClass() // 1 : destructor
  {
    std::cout << "DELETING instance of MyMovableClass at " << this << std::endl;
    delete[] _data;
  }

  MyMovableClass(const MyMovableClass &source) // 2. copy constructor
  {
    _size = source._size;
    _data = new int[_size];
    *_data = *source._data;
    std::cout << "COPYING content of instance " << &source << " to instance " << this << std::endl;
  }

  MyMovableClass &operator=(const MyMovableClass &source) // 3. copy assignment operator
  {
    std::cout << "ASSIGNING content of instance " << &source << " to instance " << this << std::endl;
    if( this == &source) { return *this; }
    delete [] this->_data;
    this->_data = new int[source._size];
    *_data = *source._data;
    _size = source._size;
    return *this;
  }
};

MyMovableClass createObject(size_t size) {
  MyMovableClass obj{size};
  return obj;
}

int main() {
  std::cout << "1." << std::endl;
  MyMovableClass class1 {10};
  std::cout << "2." << std::endl;
  MyMovableClass class2 {class1};
  std::cout << "3." << std::endl;
  MyMovableClass class3 = class2;
  class3 = class1;

  std::cout << "4." << std::endl;
  MyMovableClass class4 {createObject(10)};
  std::cout << "4.1" << std::endl;
  class4 = createObject(20);

  return 0;
}