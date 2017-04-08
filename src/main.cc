#include <iostream>
#include "map.h"
#include "input.h"
#include "process.h"

int main()
{
  setlocale(LC_ALL, "rus");
  Map map1, map2;
  map1.create_ships();
  map1.arrange_ships();
  map1.draw();

  Input input;
  input.input_data();
  if (input.check_data()) {
    Process process(input.get_input());
    process.convert_input();
    process.make_shot();
  } else
    std::cout << "Fail!" << std::endl;


  return 0;
}
