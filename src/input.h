#pragma once
#include <string>

class Input {
 public:
  Input();

  void input_data();
  bool check_data();
  std::string get_input();

 private:
  std::string input_;
};