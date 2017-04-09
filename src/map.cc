#pragma once
#include <random>
#include <ctime>
#include <chrono>
#include <time.h>
#include "map.h"

Map::Map() {
  for (int i = 0; i < kMapSize; i++) {
    for (int j = 0; j < kMapSize; j++) {
      array_[i][j] = '0';
    }
  }
}

void Map::draw() {
  std::cout << "Map: " << std::endl;
  char str[14] = { ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', '\0' };
  int n_string_max = kMapSize + 2;
  int n_column_max = kMapSize + 3;
  for (int i = 0; i < n_string_max; i++) {
    for (int j = 0; j < n_column_max; j++) {
      if (i == 0)
        std::cout << str[j];
      if (i == 1 && j < 3)
        std::cout << " ";
      if (i == 1 && j > 2)
        std::cout << char(173);
      if (j == 0 && i < n_string_max-1 && i > 1)
        std::cout << " ";
      if (j == 1 && i > 1)
        std::cout << i-1;
      if (j == 2 && i > 1)
        std::cout << char(166);
      if (i > 1 && j > 2)
        std::cout << array_[i-2][j-3];
    }
    std::cout << '\n';
  }
}

int Map::find_ship(int n_column, int n_string) {
  for (int ship_id = 0; ship_id < ships_.size(); ship_id++) {
    int ship_col = ships_[ship_id].coordinates_.first;
    int ship_str = ships_[ship_id].coordinates_.second;
    if (ships_[ship_id].vertical_) {
      if (ship_col == n_column) {
        for (int i = ship_str; i < ship_str + ships_[ship_id].size_; i++) {
          if (i == n_string)
            return ship_id;
        }
      }
    } else {
      if (ship_str == n_string) {
        for (int i = ship_col; i < ship_col + ships_[ship_id].size_; i++) {
          if (i == n_column)
            return ship_id;
        }
      }
    }
  }
  std::cout << "Ship was not found!" << std::endl;
  return -1;
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
  char symbol;
  switch (ship.size_) {
  case 1:
    symbol = 49;
    break;
  case 2:
    symbol = 50;
    break;
  case 3:
    symbol = 51;
    break;
  case 4:
    symbol = 52;
    break;
  default:
    symbol = '?';
    break;
  }

  if (ship.vertical_) {
    for (int i = ship.coordinates_.second; i < ship.coordinates_.second + ship.size_; i++) {
      array_[i][ship.coordinates_.first] = symbol;
    }
  } else {
    for (int i = ship.coordinates_.first; i < ship.coordinates_.first + ship.size_; i++) {
      array_[ship.coordinates_.second][i] = symbol;
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
      if (array_[i][j] != 48) {
        return true;
      }
    }
  }
  return false;
}