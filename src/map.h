#pragma once
#include <iostream>
#include <vector>
#include "ship.h"

class Map {
 public:
  Map();

  void draw();
  void create_ships();
  void arrange_ships();

  static const int kMapSize = 10;
  int array_[kMapSize][kMapSize];
  std::vector<Ship> ships_;

 private:
  void generate_random_place(Ship &ship);
  bool check_location(int x, int y, Ship &ship);
  void place_ship(Ship &ship);
};