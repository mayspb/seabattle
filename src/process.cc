#include "process.h"
#include <iostream>

Process::Process() {}

Process::Process(std::string input) : input_(input) {}

void Process::make_shot() {
  std::cout << "We will shot on " << shot_point_.first << ", " << shot_point_.second << std::endl;
}

void Process::convert_input() {
  shot_point_.second = std::stoi(input_.substr(1, 2)) - 1;
  std::string first = input_.substr(0, 1);
  char str[11] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', '\0' };
  int i = 0;
  while (str) {
    if (first.compare(std::string(1, str[i])) == 0)
      break;
    i++;
  }
  shot_point_.first = i;
}