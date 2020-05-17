#include <iostream>
#include <thread>

using std::thread;

class Vehicle
{
public:
  void operator()()
  {
    std::cout << "Vehicle object has been created " << std::this_thread::get_id() << std::endl;
  }
};


int main()
{
  // create thread
  std::cout << "main thread" << std::this_thread::get_id() << std::endl;

  // broke here, fixed below
  //std::thread t(Vehicle()); // C++'s most vexing parse

  // do something in main()
  //std::cout << "Finished work in main \n";

  // wait for thread to finish
  //t.join();

  // create thread
  //std::thread t0(Vehicle()); // C++'s most vexing parse

  thread t1( (Vehicle()) ); // Add an extra pair of parantheses

  thread t2 = thread( Vehicle() ); // Use copy initialization

  thread t3{ Vehicle() };// Use uniform initialization with braces

  // do something in main()
  std::cout << "Finished work in main \n";

  // wait for thread to finish
  t1.join();
  t2.join();
  t3.join();

  return 0;
}