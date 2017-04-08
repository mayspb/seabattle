#pragma once
#include <random>
#include <ctime>
#include <chrono>
#include <time.h>
#include "map.h"

Map::Map() : array_() {}

void Map::draw() {
  char well = 43;
  char damaged = 15;
  char destroyed = 'X';
  std::cout << "Map: " << std::endl;
  for (int i = 0; i < kMapSize; i++) {
    for (int j = 0; j < kMapSize; j++) {
      //if(array_[i][j] == 0)
        std::cout << array_[i][j];
      //else
      //  std::cout << well;
    }
    std::cout << '\n';
  }
}

void Map::create_ships() {
  auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::mt19937 mt_rand(seed);
  int divider = 2;
  int ship1 = 4;
  int ship2 = 3;
  int ship3 = 2;
  int ship4 = 1;
  for (int i = 0; i < 10; i++) {
    if (ship4 != 0) {
      Ship ship(4, mt_rand() % divider);
      ships_.push_back(ship);
      ship4--;
      continue;
    }
    if (ship3 != 0) {
      Ship ship(3, mt_rand() % divider);
      ships_.push_back(ship);
      ship3--;
      continue;
    }
    if (ship2 != 0) {
      Ship ship(2, mt_rand() % divider);
      ships_.push_back(ship);
      ship2--;
      continue;
    }
    if (ship1 != 0) {
      Ship ship(1, mt_rand() % divider);
      ships_.push_back(ship);
      ship1--;
    }
  }
}

void Map::arrange_ships() {
  for (int i = 0; i < ships_.size(); i++) {
    generate_random_place(ships_[i]);
    place_ship(ships_[i]);
  }
}

void Map::place_ship(Ship &ship) {
  if (ship.vertical_) {
    for (int i = ship.coordinates_.second; i < ship.coordinates_.second + ship.size_; i++) {
      array_[i][ship.coordinates_.first] = ship.size_;
    }
  } else {
    for (int i = ship.coordinates_.first; i < ship.coordinates_.first + ship.size_; i++) {
      array_[ship.coordinates_.second][i] = ship.size_;
    }
  }
}

void Map::generate_random_place(Ship &ship) {
  auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::mt19937 mt_rand(seed);
  int n_column, n_string;
  do {
    n_column = mt_rand() % kMapSize;
    n_string = mt_rand() % kMapSize;
  } while (check_location(n_column, n_string, ship));
  ship.coordinates_.first = n_column;
  ship.coordinates_.second = n_string;
  array_[n_string][n_column] = ship.size_;
}

bool Map::check_location(int n_column, int n_string, Ship &ship) {
  int n_string_max, n_column_max;
  int n_string_min, n_column_min;

  if (n_string != 0)
    n_string_min = n_string - 1;
  else
    n_string_min = n_string;

  if (n_column != 0)
    n_column_min = n_column - 1;
  else
    n_column_min = n_column;

  if (n_string != (kMapSize - 1))
    n_string_max = n_string + 1;
  else 
    n_string_max = n_string;

  if (n_column != (kMapSize - 1))
    n_column_max = n_column + 1;
  else
    n_column_max = n_column;

  if (ship.vertical_)
    n_string_max += ship.size_ - 1;
  else
    n_column_max += ship.size_ - 1;

  if (n_string_max > kMapSize || n_column_max > kMapSize)
    return true;

  if (ship.vertical_ && (n_string + ship.size_) > kMapSize)
    return true;

  if (!ship.vertical_ && (n_column + ship.size_) > kMapSize)
    return true;

  for (int i = n_string_min; i <= n_string_max; i++) {
    for (int j = n_column_min; j <= n_column_max; j++) {
      if (array_[i][j] != 0) {
        return true;
      }
    }
  }
  return false;
}