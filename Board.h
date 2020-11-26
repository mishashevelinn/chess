//
// Created by misha on 24/11/2020.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "Move.h"
#include "Entry.h"
#include "Piece.h"
class Board{
public:
    Entry* squares;
    Board();
    Move* moves;
    void init();
private:


    void find_legal_moves(int (&moves)[1024]);
    bool isValidMove(int source, int dest) const;











};


#endif //CHESS_BOARD_H
