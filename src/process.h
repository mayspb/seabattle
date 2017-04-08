#pragma once
#include <string>

class Process {
 public:
  Process();
  Process(std::string input);
  void make_shot();
  void convert_input();

  std::string input_;
  std::pair<int, int> shot_point_;
};