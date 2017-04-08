#include <iostream>
#include <regex>
#include <algorithm>
#include "input.h"

Input::Input() {}

void Input::input_data() {
  std::cout << "Input shot coordinates (for example: b5): ";
  std::getline(std::cin, input_);
}

bool Input::check_data() {
  std::transform(input_.begin(), input_.end(), input_.begin(), ::tolower);
  std::regex regex("[a-j]([1-9]|10)");
  return (std::regex_match(input_, regex));
}

std::string Input::get_input() {
  return input_;
}