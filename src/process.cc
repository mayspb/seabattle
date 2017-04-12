#include <random>
#include <ctime>
#include <chrono>
#include <time.h>
#include <iostream>
#include <thread>
#include "process.h"

const char kSymbols[11] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', '\0' };
const char kFireshot = 183;
const char kDamaged = '?';
const char kDestroyed = 'X';

Process::Process() {}

Process::Process(std::string input, std::vector<Map*> maps)
    : input_(input),
      maps_(maps) {}

int Process::make_fireshot() {
  char *point0 = &maps_[0]->array_[shot_point_.second][shot_point_.first];
  char *point1 = &maps_[1]->array_[shot_point_.second][shot_point_.first];
  if (*point1 == 48) {
    if (*point0 == 48) {
      std::cout << "Missed!" << std::endl;
      *point1 = kFireshot;
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    } else {
      int ship_id = maps_[1]->find_ship(shot_point_.first, shot_point_.second);
      if (ship_id < 0)
        return -1;
      maps_[1]->ships_[ship_id].mark_damaged_part(shot_point_.first, shot_point_.second);
      int ship_status = maps_[1]->ships_[ship_id].check_status();
      if (ship_status == 0) {
        std::cout << "No damages." << std::endl;
        return -2;
      }
      if (ship_status == 1) {
        std::cout << "Ship damaged!" << std::endl;
        *point1 = kDamaged;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        return 1;
      }
      if (ship_status == 2) {
        std::cout << "Ship destroyed!" << std::endl;
        mark_destroyed_ship(*maps_[1], ship_id);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        return 1;
      }
    }
  } else if (*point1 == kFireshot) {
    std::cout << "Missed again at this point!" << std::endl;
  } else {
    std::cout << "At this point a shot was fired earlier." << std::endl;
  }
  return 2;
}

void Process::mark_destroyed_ship(Map &map, int ship_id) {
  for (int i = 0; i < map.ships_[ship_id].size_; i++) {
    if (map.ships_[ship_id].vertical_) {
      map.array_[map.ships_[ship_id].coordinates_.second + i][map.ships_[ship_id].coordinates_.first] = kDestroyed;
    } else {
      map.array_[map.ships_[ship_id].coordinates_.second][map.ships_[ship_id].coordinates_.first + i] = kDestroyed;
    }
  }
}

bool Process::convert_input() {
  if (input_.compare("q") == 0)
    return false;
  shot_point_.second = std::stoi(input_.substr(1, 2)) - 1;
  std::string first = input_.substr(0, 1);
  int i = 0;
  while (kSymbols) {
    if (first.compare(std::string(1, kSymbols[i])) == 0)
      break;
    i++;
  }
  shot_point_.first = i;
  return true;
}

void Process::generate_fireshot() {
  auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::mt19937 mt_rand(seed);
  int n_column, n_string, i_damaged, j_damaged;
  bool present_damage = false;
  for (int i = 0; i < maps_[2]->kMapSize; i++) {
    for (int j = 0; j < maps_[2]->kMapSize; j++) {
      if (maps_[2]->array_[i][j] == kDamaged) {
        i_damaged = i;
        j_damaged = j;
        present_damage = true;
        break;
      }
    }
  }
  do {
    if (present_damage) {
      int j_max = j_damaged;
      while (maps_[2]->array_[i_damaged][j_max] == kDamaged) {
        j_max++;
      }
      int i_max = i_damaged;
      while (maps_[2]->array_[i_max][j_damaged] == kDamaged) {
        i_max++;
      }
      if (i_max - i_damaged > 1) {
        n_string = rand() % 2 ? (i_damaged - 1) : i_max;
        n_column = j_damaged;
      }
      if (j_max - j_damaged > 1) {
        n_string = i_damaged;
        n_column = rand() % 2 ? (j_damaged - 1) : j_max;
      }
      if ((i_max - i_damaged) == (j_max - j_damaged)) {
        if (rand() % 2) {
          n_string = rand() % 2 ? (i_damaged - 1) : i_max;
          n_column = j_damaged;
        } else {
          n_string = i_damaged;
          n_column = rand() % 2 ? (j_damaged - 1) : j_max;
        }
      }
      if (n_string < 0)
        n_string = i_max;
      if (n_column < 0)
        n_column = j_max;
      if (n_string >= maps_[2]->kMapSize)
        n_string = i_damaged;
      if (n_column >= maps_[2]->kMapSize)
        n_column = j_damaged;
    } else {
      n_column = mt_rand() % maps_[2]->kMapSize;
      n_string = mt_rand() % maps_[2]->kMapSize;
    }
    std::cout << ".";
  } while (check_location(n_column, n_string));

  shot_point_ = {n_column, n_string};
  std::cout << "Fireshot on: " << convert_output(n_column, n_string) << std::endl;
  std::cout << "Please, choose one of answers:" << std::endl;
  std::cout << "1) Missed." << std::endl;
  std::cout << "2) Ship is damaged." << std::endl;
  std::cout << "3) Ship is destroyed." << std::endl;
}

bool Process::check_location(int n_column, int n_string) {
  char symbol = maps_[2]->array_[n_string][n_column];
  if (symbol == kFireshot || symbol == kDamaged || symbol == kDestroyed)
    return true;
  //// Here should be processing case, when ship is damaged
  //for (int i = 0; i < maps_[2]->kMapSize; i++) {
  //  for (int j = 0; j < maps_[2]->kMapSize; j++) {
  //    if (maps_[2]->array_[i][j] == kDamaged) {
  //      return true;
  //    }
  //  }
  //}
  return false;
}

std::string Process::convert_output(int n_column, int n_string) {
  std::string output = std::string(1, toupper(kSymbols[n_column]));
  return output.append(std::to_string(n_string + 1));
}

void Process::mark_shot_point(int result) {
  if (result == 1) {
    maps_[2]->array_[shot_point_.second][shot_point_.first] = kFireshot;
  }
  if (result == 2) {
    maps_[2]->array_[shot_point_.second][shot_point_.first] = kDamaged;
  }
  if (result == 3) {
    maps_[2]->array_[shot_point_.second][shot_point_.first] = kDamaged;
    maps_[2]->add_ship();
    int ship_id = maps_[2]->find_ship(shot_point_.first, shot_point_.second);
    mark_destroyed_ship(*maps_[2], ship_id);
  }
}