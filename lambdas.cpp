#include <iostream>

int main()
{
  // create lambdas
  int id = 0; // Define an integer variable

  //auto f0 = []() { std::cout << "ID = " << id << std::endl; }; // Error: 'id' cannot be accessed

  id++;
  auto f1 = [id]() { std::cout << "1 ID = " << id << std::endl; }; // OK, 'id' is captured by value
  auto f1a = [id](int actual_id) {
    std::cout << "1a ID = " << id << std::endl;
    std::cout << "actual_id = " << actual_id << std::endl;
  }; // OK, 'id' is captured by value

  id++;
  auto f2 = [&id]() { std::cout << "2 ID = " << id << std::endl; }; // OK, 'id' is captured by reference

  //auto f3 = [id]() { std::cout << "ID = " << ++id << std::endl; }; // Error, 'id' may not be modified

  auto f4 = [id](int multi) mutable { std::cout << "4 ID = " << ++id * multi << std::endl; }; // OK, 'id' may be modified

  auto f5 = [&id](int actual_id) {
    std::cout << "5 ID = " << id << std::endl;
    std::cout << "actual_id = " << actual_id << std::endl;
  }; // OK, 'id' is captured by value

  id++;

  auto f6 = [&id](int actual_id) {
    std::cout << "6 ID = " << id << std::endl;
    std::cout << "actual_id = " << actual_id << std::endl;
  }; // OK, 'id' is captured by value

  // execute lambdas
  f1();
  f2();
  f4(1231231);
  f1();
  f5(id);
  f6(id);
  f1();
  f1a(id);
  f2();

  // create lambda
  auto f7 = [](const int id) { std::cout << "7 ID = " << id << std::endl; }; // ID is passed as a parameter

  // execute function object and pass the parameter
  f7(id);
  f1();

  return 0;
}