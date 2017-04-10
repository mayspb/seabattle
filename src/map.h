#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "ship.h"

class Map {
 public:
  Map();

  void draw(std::string text);
  void create_ships();
  void arrange_ships();
  int find_ship(int n_column, int n_string);
  void add_ship();
  int get_destroyed_ships();

  static const int kMapSize = 10;
  char array_[kMapSize][kMapSize];
  std::vector<Ship> ships_;

 private:
  void generate_random_place(Ship &ship);
  bool check_location(int x, int y, Ship &ship);
  void place_ship(Ship &ship);
};