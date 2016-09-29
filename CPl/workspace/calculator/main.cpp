#include "calculator.h"
#include "iostream"


int main() {
  while (std::cin) {
    std::cout << '=' << calc(std::cin) << '\n';
  }
}