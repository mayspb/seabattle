#include "process.h"
#include <iostream>

Process::Process() {}

Process::Process(std::string input) : input_(input) {}

bool Process::make_fireshot(std::vector<Map*> maps) {
  char fireshot = 183;
  char damaged = '?';
  char destroyed = 'X';
  char *point0 = &maps[0]->array_[shot_point_.second][shot_point_.first];
  char *point1 = &maps[1]->array_[shot_point_.second][shot_point_.first];
  if (*point1 == 48) {
    if (*point0 == 48) {
      std::cout << "Missed!" << std::endl;
      *point1 = fireshot;
    } else {
      int ship_id = maps[0]->find_ship(shot_point_.first, shot_point_.second);
      if (ship_id < 0)
        return false;
      maps[0]->ships_[ship_id].hit(shot_point_.first, shot_point_.second);
      int ship_status = maps[0]->ships_[ship_id].check_status();
      if (ship_status == 0) {
        std::cout << "No damages" << std::endl;
      }
      if (ship_status == 1) {
        std::cout << "Ship damaged!" << std::endl;
        *point1 = damaged;
      }
      if (ship_status == 2) {
        std::cout << "Ship destroyed!" << std::endl;
        mark_destroyed_ship(*maps[1], ship_id);
      }
    }
  } else if (*point1 == fireshot) {
    std::cout << "Missed again at this point!" << std::endl;
  } else {
    std::cout << "At this point a shot was fired earlier." << std::endl;
  }
  return true;
}

void Process::mark_destroyed_ship(Map &map, int ship_id) {
  for (int i = 0; i < map.ships_[ship_id].size_; i++) {
    if (map.ships_[ship_id].vertical_) {
      map.array_[map.ships_[ship_id].coordinates_.second + i][map.ships_[ship_id].coordinates_.first] = 'X';
    } else {
      map.array_[map.ships_[ship_id].coordinates_.second][map.ships_[ship_id].coordinates_.first + i] = 'X';
    }
  }
}

bool Process::convert_input() {
  if (input_.compare("q") == 0)
    return false;
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
  return true;
}