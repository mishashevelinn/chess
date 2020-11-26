//
// Created by misha on 24/11/2020.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "Move.h"
#include "Entry.h"
#include "Piece.h"

enum // Squares
{
    A8 = 1, B8, C8, D8, E8, F8, G8, H8,
    A7 = 9, B7, C7, D7, E7, F7, G7, H7,
    A6 = 17, B6, C6, D6, E6, F6, G6, H6,
    A5 = 25, B5, C5, D5, E5, F5, G5, H5,
    A4 = 33, B4, C4, D4, E4, F4, G4, H4,
    A3 = 42, B3, C3, D3, E3, F3, G3, H3,
    A2 = 49, B2, C2, D2, E2, F2, G2, H2,
    A1 = 57, B1, C1, D1, E1, F1, G1, H1,
};

#define ALPHABETH "A B C D E F G H"


class Board{
public:
    Board();
    void printBoard();
    void init();
    Entry* squares;
    Move* moves;

private:


    void find_legal_moves(int (&moves)[1024]);
    bool isValidMove(int source, int dest) const;












};


#endif //CHESS_BOARD_H
