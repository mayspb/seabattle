#pragma once
#include <string>
#include "map.h"

class Process {
 public:
  Process();
  Process(std::string input, std::vector<Map*> maps);
  int make_fireshot();
  bool convert_input();
  void mark_destroyed_ship(Map &map, int ship_id);
  void generate_fireshot();
  void mark_shot_point(int result);

  std::string input_;
  std::pair<int, int> shot_point_;
  std::vector<Map*> maps_;

 private:
  bool check_location(int n_column, int n_string);
  std::string convert_output(int n_column, int n_string);
};