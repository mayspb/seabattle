#pragma once
#include <string>

class Input {
 public:
  Input();

  void input_data();
  bool check_data();
  std::string get_input();

  std::string input_;
};