#include <iostream>
#include <iostream>
using namespace std;
#include "Board.h"
#include "Entry.h"
#include "Piece.h"
int main() {
    Board* b = new Board;
    b->init();
    b->printBoard();
    return 0;
}
