#pragma once
#include <vector>
#include <iostream>

class Ship {
 public:
   Ship();
   Ship(int size, bool vertical);
   int check_status();
   void hit(int x, int y);

   int size_;
   bool vertical_;
   std::pair<int, int> coordinates_;
   std::vector<bool> status_;
};