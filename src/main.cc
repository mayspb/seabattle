#include <iostream>
#include "map.h"
#include "input.h"
#include "process.h"

int main()
{
  setlocale(LC_ALL, "rus");
  std::vector<Map*> maps;
  Map map1, map2;
  maps.push_back(&map1);
  maps.push_back(&map2);
  map1.create_ships();
  map1.arrange_ships();
  map2.ships_ = map1.ships_;
  map1.draw();

  Input input;
  for (;;) {
    input.input_data();
    if (input.check_data()) {
      Process process(input.get_input());
      if (!process.convert_input()) {
        std::cout << "Good bye!" << std::endl;
        return 1;
      }
      if (!process.make_fireshot(maps)) {
        std::cout << "Could not made fire shot!" << std::endl;
        return 2;
      }
      map2.draw();
    } else
      std::cout << "\nInput mask: first symbol - [a-jA-J]; second - [1-10] \nFor example, 'b5' \nOr input 'q' to exit.\n" << std::endl;
  }

  return 0;
}
