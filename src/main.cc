#include <iostream>
#include <thread>
#include <chrono>
#include "map.h"
#include "input.h"
#include "process.h"

int main()
{
  setlocale(LC_ALL, "rus");
  std::vector<Map*> maps;
  Map map1, map2, user_map;
  maps.push_back(&map1);
  maps.push_back(&map2);
  maps.push_back(&user_map);

  map1.create_ships();
  map1.arrange_ships();
  map2.ships_ = map1.ships_;
  //map1.draw("Computer's map with ships: ");

  Input input;
  for (;;) {
    system("cls");
    map2.draw("Computer's map: ");
    input.input_data("Input fireshot: ");
    if (input.check_data()) {
      Process process(input.get_input(), maps);
      if (!process.convert_input()) {
        std::cout << "Good bye!" << std::endl;
        return 1;
      }
      int result = process.make_fireshot();
      if (map2.get_destroyed_ships() == 10) {
        std::cout << "Game over! You won!" << std::endl;
        return 0;
      }
      if (result < 0) {
        std::cout << "Could not made fire shot!" << std::endl;
        return 2;
      }
      if (result == 1)
        continue;
      for (;;) {
        system("cls");
        user_map.draw("User's map: ");
        process.generate_fireshot();
        result = input.get_answer();
        process.mark_shot_point(result);
        if (result == 1) {
          break;
        }
        if (user_map.ships_.size() == 10) {
          std::cout << "Game over! Computer won!" << std::endl;
          return 0;
        }
      }
    } else {
      std::cout << "\nInput mask: first symbol - [a-jA-J]; second - [1-10] \nFor example, 'b5' \nOr input 'q' to exit.\n" << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(2));
    }
  }

  return 0;
}
