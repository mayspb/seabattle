#pragma once
#include <string>

class Input {
 public:
  Input();

  void input_data(std::string text);
  bool check_data();
  std::string get_input();
  int get_answer();
  bool check_answer();

 private:
  std::string input_;
};