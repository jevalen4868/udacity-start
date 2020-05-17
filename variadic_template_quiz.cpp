#include <iostream>
#include <thread>

using std::string;

class Vehicle
{
public:
  Vehicle() : _id(0) {}
  void setName(string name) { this->_name = name; }
  void addID(int id) { _id = id; }
  void printName() { std::cout << "Vehicle Name=" << this->_name << std::endl; }
  void printID()
  {
    std::cout << "Vehicle ID=" << _id << std::endl;
  }
  // TODO: Modify the Vehicle class as indicated in the instructions on the left.
private:
  int _id;
  string _name;
};

int main()
{
  // create thread
  std::shared_ptr<Vehicle> v(new Vehicle);
  std::thread t = std::thread(&Vehicle::addID, v, 1); // call member function on object v
  std::thread t2 = std::thread(&Vehicle::setName, v, "Fjord"); // call member function on object v

  // TODO: Modify the main to start setName as a thread.
  // Also, add code to main to print the name of the vehicle.

  // wait for thread to finish
  t.join();
  t2.join();

  // print Vehicle id
  v->printID();
  v->printName();

  return 0;
}