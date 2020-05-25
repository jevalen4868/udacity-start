#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
#include <algorithm>

class Vehicle
{
public:
  Vehicle(int id) : _id(id) {}
  int getID() { return _id; }

private:
  int _id;
};

class WaitingVehicles
{
public:
  WaitingVehicles() {}

  bool dataIsAvailable()
  {
    std::lock_guard<std::mutex> myLock(_mutex);
    return !_vehicles.empty();
  }

  int dataCount() {
    std::lock_guard<std::mutex> lock(_mutex);
    return _vehicles.size();
  }

  Vehicle popBack()
  {
    // perform vector modification under the lock
    std::lock_guard<std::mutex> uLock(_mutex);

    // remove last vector element from queue
    Vehicle v = std::move(_vehicles.back());
    _vehicles.pop_back();

    return v; // will not be copied due to return value optimization (RVO) in C++
  }

  void pushBack(Vehicle &&v)
  {
    // simulate some work
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // perform vector modification under the lock
    std::lock_guard<std::mutex> uLock(_mutex);

    // add vector to queue
    std::cout << "   Vehicle #" << v.getID() << " will be added to the queue" << std::endl;
    _vehicles.emplace_back(std::move(v));
  }

private:
  std::vector<Vehicle> _vehicles; // list of all vehicles waiting to enter this intersection
  std::mutex _mutex;
};

int main()
{
  // create monitor object as a shared pointer to enable access by multiple threads
  std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);

  std::cout << "Spawning threads..." << std::endl;
  std::vector<std::future<void>> futures;
  for (int i = 0; i < 100000; ++i)
  {
    // create a new Vehicle instance and move it into the queue
    Vehicle v(i);
    futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v)));
  }

  // make sure there's data.
  while(queue->dataCount() <= 0) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }

  std::cout << "Collecting results..." << std::endl;
  while (true)
  {
    if (queue->dataIsAvailable())
    {
      Vehicle v = queue->popBack();
      std::cout << "   Vehicle #" << v.getID() << " has been removed from the queue" << std::endl;
      if(queue->dataCount() <= 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        break;
      }
    }
  }

  std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr) {
    ftr.wait();
  });

  std::cout << "Finished processing queue size=" << queue->dataCount() << std::endl;

  return 0;
}