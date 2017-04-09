#pragma once
#include <string>
#include "map.h"

class Process {
 public:
  Process();
  Process(std::string input);
  bool make_fireshot(std::vector<Map*> maps);
  bool convert_input();
  void mark_destroyed_ship(Map &map, int ship_id);

  std::string input_;
  std::pair<int, int> shot_point_;
};