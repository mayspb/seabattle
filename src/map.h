#pragma once
#include <iostream>
#include "ship.h"

class Map {
 public:
  Map();

 	static const int kSize_ = 10;
 	int array_[kSize_][kSize_];
  char well_ = '■';
  char damaged_ = '¤';
  char destroyed_ = 'X';

 	void draw();
 	void arrange_ships();

 private:
  void generate_random_place();
  bool check_location(int x, int y);
};