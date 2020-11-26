#include <iostream>
#include <iostream>
using namespace std;
#include "Board.h"
#include "Square.h"
#include "Piece.h"
int main() {
    Board* b = new Board;
    b->init();
    b->printBoard();

    b->make_move(Move(A2, A4));
    //b->squares[A4].get_info();
    b->printBoard();

    return 0;
}
