#include "ship.h"

Ship::Ship() {}

Ship::Ship(int size, bool vertical)
  : size_(size),
    vertical_(vertical),
    coordinates_(),
    status_(size) {}
