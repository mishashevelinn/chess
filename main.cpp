#include <iostream>
#include "Board.h"


int main() {
    Board *b = new Board;
    b->init();
    cout << *b;
    b->find_legal_moves();
    Move move(81, 61, BP);
    b->make_move(move);
   cout << *b;

        return 0;
    }
