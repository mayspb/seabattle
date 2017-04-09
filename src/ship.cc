#include "ship.h"

Ship::Ship() {}

Ship::Ship(int size, bool vertical)
  : size_(size),
    vertical_(vertical),
    coordinates_(),
    damages_(size) {}

int Ship::check_status() {
  int damages = 0;
  for (int i = 0; i < size_; i++) {
    if (damages_[i])
      damages++;
  }
  if (damages == 0)
    return 0;
  if (damages > 0 && damages < size_)
    return 1;
  return 2;
}

void Ship::hit(int n_column, int n_string) {
  for (int i = 0; i < size_; i++) {
    if (vertical_) {
      if (coordinates_.second + i == n_string)
        damages_[i] = true;
    } else {
      if (coordinates_.first + i == n_column)
        damages_[i] = true;
    }
  }
}