#include <vector>
#include <iostream>

class Ship {
 public:
   int size_;
   bool vertical_;
   std::pair<int, int> coordinates;
   std::vector<bool> status_;

   void draw();
};