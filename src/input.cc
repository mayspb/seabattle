#include <iostream>
#include <regex>
#include <algorithm>

#ifdef _WIN32
#include <conio.h>
#endif

#include "input.h"

Input::Input() {}

void Input::input_data(std::string text) {
  std::cout << text;
  std::getline(std::cin, input_);
}

bool Input::check_data() {
  std::transform(input_.begin(), input_.end(), input_.begin(), ::tolower);
  std::regex regex("([a-j]([1-9]|10))|q");
  return (std::regex_match(input_, regex));
}

std::string Input::get_input() {
  return input_;
}

int Input::get_answer() {
  do {
    #ifdef _WIN32
    char answer = _getch();
    input_ = answer;
    #else
    std::getline(std::cin, input_);
    #endif
  } while (!check_answer());
  return std::stoi(input_);
}

bool Input::check_answer() {
  std::regex regex("[1-3]");
  return (std::regex_match(input_, regex));
}