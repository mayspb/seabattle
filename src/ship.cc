#include "ship.h"

Ship::Ship() {}

Ship::Ship(int size, bool vertical)
  : size_(size),
    vertical_(vertical),
    coordinates_(),
    status_(size) {}

int Ship::check_status() {
  int damages = 0;
  for (int i = 0; i < size_; i++) {
    if (status_[i])
      damages++;
  }
  if (damages == 0)
    return 0;
  if (damages > 0 && damages < size_)
    return 1;
  return 2;
}