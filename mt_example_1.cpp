#include <iostream>
#include <thread>

void threadFunction()
{
  std::this_thread::sleep_for(std::chrono::milliseconds(100)); // simulate work
  std::cout << "Finished work in thread\n";
}

void threadFunction02()
{
  std::this_thread::sleep_for(std::chrono::milliseconds(50)); // simulate work
  std::cout << "Finished work 1 in thread\n";

  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  std::cout << "Finished work 2 in thread\n";
}

void threadFunctionEven()
{
  std::this_thread::sleep_for(std::chrono::milliseconds(1)); // simulate work
  std::cout << "Even thread\n";
}

/* Student Task START */
void threadFunctionOdd() {
  std::this_thread::sleep_for(std::chrono::milliseconds(1)); // simulate work
  std::cout << "Odd thread\n";
}
/* Student Task END */

int main()
{
  // ex 1
  std::cout << "Hello concurrent world from main! Thread id = " << std::this_thread::get_id() << std::endl;

  // ex 2
  unsigned int nCores = std::thread::hardware_concurrency();
  std::cout << "This machine supports concurrency with " << nCores << " cores available" << std::endl;

  // ex 3
  // create thread
  std::thread t(threadFunction);

  // do something in main()
  std::this_thread::sleep_for(std::chrono::milliseconds(50)); // simulate work
  std::cout << "Finished work in main\n";

  // wait for thread to finish
  t.join();

  // ex 4
  // create thread
  std::thread t_02(threadFunction);

  // do something in main()
  std::this_thread::sleep_for(std::chrono::milliseconds(50)); // simulate work
  std::cout << "Finished work 1 in main\n";

  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  std::cout << "Finished work 2 in main\n";

  // wait for thread to finish
  t_02.join();

  //ex 6
  // create thread
  std::thread t_03(threadFunction);

  // detach thread and continue with main
  t_03.detach();

  // do something in main()
  std::this_thread::sleep_for(std::chrono::milliseconds(50)); // simulate work
  std::cout << "Finished work in main\n";

  // quiz 1
  /* Student Task START */
  for(size_t i = 0; i < 6; i ++) {
      std::thread t_quiz(i % 2 == 0 ? threadFunctionEven : threadFunctionOdd);
      t_quiz.detach();
  }
  /* Student Task END */

  // ensure that main does not return before the threads are finished
  //std::this_thread::sleep_for(std::chrono::milliseconds(1)); // simulate work

  std::cout << "End of main is reached" << std::endl;

  return 0;
}
