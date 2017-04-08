#pragma once
#include <vector>
#include <iostream>

class Ship {
 public:
   Ship();
   Ship(int size, bool vertical);

   int size_;
   bool vertical_;
   std::pair<int, int> coordinates_;
   std::vector<int> status_;
};