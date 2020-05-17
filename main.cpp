#include <assert.h>
#include <string>
#include <sstream>
#include <filesystem>
#include <iostream>

// TODO: Add the correct template specification
template <typename T, typename R>
class Mapping {
public:
  Mapping(T key, R value) : key(key), value(value) {}
  std::string Print() const {
    std::ostringstream stream;
    stream << key << ": " << value;
    return stream.str();
  }
  T key;
  R value;
};

// Test
int main() {

  char str1[] = "UDACITY";
  printf("%s", str1);

  Mapping<std::string, int> mapping("age", 20);
  assert(mapping.Print() == "age: 20");

  // create array
  const int size = 4000;
  static int x[size][size];

  auto t1 = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      x[j][i] = i + j;
      //std::cout << &x[j][i] << ": i=" << i << ", j=" << j << std::endl;
    }
  }

  // print execution time to console
  auto t2 = std::chrono::high_resolution_clock::now(); // stop time measurement
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
  std::cout << "Execution time: " << duration << " microseconds" << std::endl;
}