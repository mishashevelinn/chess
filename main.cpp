#include <iostream>
#include <cstdio>

#include "Board.h"


int main() {
      Board* b = new Board;
      b->init();
      cout << *b;
      b->find_legal_moves();
    for (int i = 0; i < b->WhiteMoves.get_size(); i++) {
        cout << b->WhiteMoves[i] << endl;

    }


        cout << b->get_square(24).getOwner().getName();
    return 0;
}
