#include <iostream>
#include <regex>
#include <algorithm>
#include "input.h"

Input::Input() {}

void Input::input_data() {
  std::cout << "Input fireshot: ";
  std::getline(std::cin, input_);
}

bool Input::check_data() {
  std::transform(input_.begin(), input_.end(), input_.begin(), ::tolower);
  std::regex regex("([a-j]([1-9]|10))|[qQ]");
  return (std::regex_match(input_, regex));
}

std::string Input::get_input() {
  return input_;
}