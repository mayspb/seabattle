#include <iostream>
#include "map.h"


int main()
{
  setlocale(LC_ALL, "rus");
  Map map1, map2;
  map1.arrange_ships();
  map1.draw();
  return 0;
}
