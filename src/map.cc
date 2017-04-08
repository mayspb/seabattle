#pragma once
#include <random>
#include <ctime>
#include <chrono>
#include <time.h>
#include "map.h"

Map::Map() : array_() {}

void Map::draw() {
  std::cout << "Map: " << std::endl;
  for (int i = 0; i < kSize_; i++) {
    for (int j = 0; j < kSize_; j++) {
      std::cout << array_[i][j];
    }
    std::cout << '\n';
  }
}

void Map::arrange_ships() {
  for (int i = 0; i < kSize_; i++) {
    generate_random_place();
  }

}

void Map::generate_random_place() {
  auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::mt19937 mt_rand(seed);
  int n_column, n_string;
  do {
    n_column = mt_rand() % kSize_;
    n_string = mt_rand() % kSize_;
  } while (check_location(n_column, n_string));
  array_[n_string][n_column] = 1;
  //std::cout << "n_column = " << n_column << "; n_string = " << n_string << std::endl;
}

bool Map::check_location(int n_column, int n_string) {
  bool busy = false;
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

  if (n_string != (kSize_ - 1))
    n_string_max = n_string + 1;
  else
    n_string_max = n_string;

  if (n_column != (kSize_ - 1))
    n_column_max = n_column + 1;
  else
    n_column_max = n_column;

  for (int i = n_string_min; i <= n_string_max; i++) {
    for (int j = n_column_min; j <= n_column_max; j++) {
      if (array_[i][j] != 0) {
        busy = true;
      }
    }
  }
  return busy;
}