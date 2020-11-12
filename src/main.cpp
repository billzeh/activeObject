#include <iostream>
#include "activeObject/ActiveObject.h"

int main() {
  std::cout << "1: Begin Main" << std::endl;

  std::atomic<int> count;
  count = 0;
  {
    ActiveObject ao;
    ao.async([]() {
      std::this_thread::sleep_for (std::chrono::seconds(1));
    });

    ao.async([&]() {
      ++count;
      std::cout << "3: Async first" << std::endl;
    });

    ao.async([&]() {
      ++count;
      std::cout << "4: Async second" << std::endl;
    });

    std::cout << "2: Pushed Async Work... " << count << std::endl;

    auto didBlock = ao.asyncAndBlock<bool>([]() { return true; });
    std::cout << "5: Async third and blocked? " << (didBlock ? "True" : "False")
              << std::endl;
  }
  std::cout << "6: End Main " << count << std::endl;
  return 0;
}
