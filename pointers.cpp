#include <stdlib.h>
#include <iostream>
#include <memory>

void RawPointer()
{
  int *raw = new int; // create a raw pointer on the heap
  *raw = 1; // assign a value
  delete raw; // delete the resource again
}

void UniquePointer()
{
  std::unique_ptr<int> unique(new int); // create a unique pointer on the stack
  *unique = 2; // assign a value
  // delete is not necessary
}

class MyClass
{
private:
  std::string _text;

public:
  MyClass() {}
  MyClass(std::string text) { _text = text; }
  ~MyClass() { std::cout << _text << " destroyed" << std::endl; }
  void setText(std::string text) { _text = text; }
};

int main() {
  RawPointer();
  UniquePointer();

  // create unique pointer to proprietary class
  std::unique_ptr<MyClass> myClass1 = std::unique_ptr<MyClass>(new MyClass());
  std::unique_ptr<MyClass> myClass2(new MyClass("String 2"));

  // call member function using ->
  myClass1->setText("String 1");

  // use the dereference operator *
  *myClass1 = *myClass2;

  // use the .get() function to retrieve a raw pointer to the object
  std::cout << "Objects have stack addresses " << myClass1.get() << " and " << myClass2.get() << std::endl;

  // shared pointers
  std::shared_ptr<int> shared1(new int);
  std::cout << "shared pointer count = " << shared1.use_count() << std::endl;

  {
    std::shared_ptr<int> shared2 = shared1;
    std::cout << "shared pointer count = " << shared1.use_count() << std::endl;
  }

  std::cout << "shared pointer count = " << shared1.use_count() << std::endl;

  std::shared_ptr<int> shared3(new int);
  *shared3 = *shared1;
  std::cout << "shared pointer count = " << shared1.use_count() << std::endl;
  shared3.reset();

  // weak pointers
  std::cout << "weak pointers" << std::endl;
  std::shared_ptr<int> mySharedPtr(new int);
  std::cout << "shared pointer count = " << mySharedPtr.use_count() << std::endl;

  std::weak_ptr<int> myWeakPtr1(mySharedPtr);
  std::weak_ptr<int> myWeakPtr2(myWeakPtr1);
  std::cout << "shared pointer count = " << mySharedPtr.use_count() << std::endl;

  if (myWeakPtr1.expired()) {
    std::cout << "Weak pointer expired!" << std::endl;
  } else {
    std::cout << "Weak pointer NOT expired!" << std::endl;
  }
  //std::weak_ptr<int> myWeakPtr3(new int); // COMPILE ERROR

  // construct a unique pointer
  std::unique_ptr<int> uniquePtr(new int);

  // (1) shared pointer from unique pointer
  std::shared_ptr<int> sharedPtr1 = std::move(uniquePtr);

  // (2) sWhared pointer from weak pointer
  std::weak_ptr<int> weakPtr(sharedPtr1);
  std::shared_ptr<int> sharedPtr2 = weakPtr.lock();

  // (3) raw pointer from shared (or unique) pointer
  int *rawPtr = sharedPtr2.get();
  //sharedPtr2.reset(); seems to not be problematic.
  // this throws an exception on linux, not sure why not here or wsl.
  delete rawPtr;

  std::cout << "Reached the end." << std::endl;

  return 0;
}