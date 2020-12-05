#ifndef CHESS_GAME_H
#define CHESS_GAME_H
#include "Board.h"


class Game {
public:
    void game_loop(); //invokes other methods and controls the game flow

    Game() : board(new Board()) { num_turn = 1; }

private:
    Board *board;
    int num_turn; //counting moves for display 1) , 2) ...

    void display_board() const { cout << board; }

    bool valid_option(string str);

    int str_to_move(const string &str, Move &move) const;

    bool str_square_check(const string &str_square) const;

    int str_to_name(const char &str_name) const;


    Game(const Game &) {} //Only one game played at a time




};


#endif //CHESS_GAME_H
