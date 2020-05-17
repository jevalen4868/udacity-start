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

  MyMovableClass(MyMovableClass &&source) // 4. move constructor
  {
    std::cout << "MOVING (c'tor) instance " << &source << " to instance " << this << std::endl;
    _data = source._data;
    _size = source._size;
    source._data = nullptr;
    source._size = 0;
  }

  MyMovableClass &operator=(MyMovableClass &&source) // 5. move assignment operator.
  {
    std::cout << "MOVING (assign) instance " << &source << " to instance " << this << std::endl;
    if(this == &source) { return *this; }

    delete[] _data;

    _data = source._data;
    _size = source._size;

    source._data = nullptr;
    source._size = 0;

    return *this;
  }

};

MyMovableClass createObject(size_t size) {
  MyMovableClass obj{size};
  return obj;
}

void useObject(MyMovableClass obj) {
  std::cout << "using object " << &obj << std::endl;
}

int main() {
  std::cout << "1." << std::endl;
  MyMovableClass class1 {400};
  std::cout << "2." << std::endl;
  MyMovableClass class2 {class1};
  std::cout << "3." << std::endl;
  MyMovableClass class3 = class2;
  class3 = class1;

  std::cout << "4." << std::endl;
  MyMovableClass class4 {createObject(1000)};
  std::cout << "4.1:" << &class4 << std::endl;
  class4 = createObject(2000);

  std::cout << "5:" << std::endl;
  MyMovableClass class5{1000}; // constructor
  class5 = MyMovableClass(2000); // move assignment
  MyMovableClass class6 = MyMovableClass{3000}; // move constructor

  std::cout << "6:" << std::endl;
  useObject(class6);

  std::cout << "7:" << std::endl;
  useObject(MyMovableClass{1234});

  std::cout << "8:" << std::endl;
  MyMovableClass waste_me{5343};
  useObject(std::move(waste_me));

  std::cout << "9:" << std::endl;
  useObject(std::move(MyMovableClass{2345}));

  return 0;
}