//
// Created by misha on 29/11/2020.
//

#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include "Board.h"
/*This class is responsible for gameplay loop and console interaction.
 * Invokes corresponding methods of Board and uses its own methods*/

class Game {
public:
    Game() : board(new Board()) {num_turn = 1;}

    void game_loop(); //invokes other methods and controls the game flow

    void display_board() const { cout << board; }

    bool valid_option(string str);

    int str_to_move(const string & str, Move & move) const ;

    bool str_square_check(const string & str_square) const;




private:
    Game(const Game &) {} //Only one game played at a time
    Board* board;
    string curr_move;
    int num_turn; //counting moves for display 1) , 2) ...


};


#endif //CHESS_GAME_H
