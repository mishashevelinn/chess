#include <iostream>
#include "Board.h"
#include "Game.h"


int main() {
//      Board* b = new Board;
//      b->init();
//      //cout << *b;
//      Piece piece(WHITE, WP);
//      Move move(C2, C3);
//      cout << b->get_square(D2).getOwner();
//      b->make_move(move);
//      cout << *b;
//        cout << (((int)'1' - 28) % 10 + 1)* 10 << endl;
//        cout << ( ( ( (int)'H') - 56 ) % 9 ) + 1 ;


    Game * game = new Game();
    game->game_loop();


    return 0;
}
