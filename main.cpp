#include "Tree.h"

#ifdef _WIN32
  #define CLEAR system("cls");
#else
  #define CLEAR system("clear");
#endif

int main() {
  Tree t1("Is it a mammal?", "Horse", "Fish");
  bool play = true;

  while(play) {
    CLEAR
    t1.game();

    if (!t1.getState())
      play = false;
  }

  return 0;
}
