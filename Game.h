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
    Game(Board board) : board(board) {};

    void game_loop(); //invokes other methods and controls the game flow

    void display_board() const { cout << board; }

    string get_input();

    bool isValidInput(string) const;




private:
    Game(const Game &) {} //Only one game played at a time
    Board board;
    string curr_move;
    unsigned int counter; //counting moves for display 1) , 2) ...


};


#endif //CHESS_GAME_H
