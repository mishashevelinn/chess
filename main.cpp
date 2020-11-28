#include <iostream>

#include "Board.h"


int main() {
      Board* b = new Board;
      b->init();
      Piece piece(BLACK, BK);
      Square square(A1);
      cout << square;

    return 0;
}
