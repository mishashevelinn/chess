//
// Created by misha on 24/11/2020.
//


#define BLACK 0
#define WHITE 1

#include "Board.h"
#include "Entry.h"
enum // Squares
{
    A8 = 56, B8, C8, D8, E8, F8, G8, H8,
    A7 = 48, B7, C7, D7, E7, F7, G7, H7,
    A6 = 40, B6, C6, D6, E6, F6, G6, H6,
    A5 = 32, B5, C5, D5, E5, F5, G5, H5,
    A4 = 24, B4, C4, D4, E4, F4, G4, H4,
    A3 = 16, B3, C3, D3, E3, F3, G3, H3,
    A2 = 8, B2, C2, D2, E2, F2, G2, H2,
    A1 = 0, B1, C1, D1, E1, F1, G1, H1,
};


Board::Board() : moves(new Move[1024]), squares(new Entry[64]) {







}

void Board::init() {
    squares[D1] = Entry(Piece(WHITE, WK), D1);
    squares[E1] = Entry(Piece(WHITE, WQ), E1);
    squares[D8] = Entry(Piece(BLACK, BK), D8);
    squares[E8] = Entry(Piece(BLACK, BQ), E8);
    for (int i = A1; i <= H8; i++) {
        if (i >= A2 && i <= H2 )
            squares[i] = Entry(Piece(WHITE, WP), i); //place White pawns
        if(i == A1 || i == H1)
            squares[i] = Entry(Piece(WHITE, WR), i);    //place white rooks
        if(i == B1 || i == G1)
            squares[i] = Entry(Piece(WHITE, WKN), i);   //place white knights
        if(i == C1 || i == F1 )
            squares[i] = Entry(Piece(WHITE, WB) , i);   //place white bishops
        if(i >= A7 && i <= H7)
            squares[i] = Entry(Piece(BLACK, BP), i);    //place black pawns
        if(i == A8 || i == H8)
            squares[i] = Entry(Piece(BLACK, BR), i);    //place black rooks
        if(i == B8 || i == G8)
            squares[i] = Entry(Piece(BLACK, BK), i);    //place black knights
        if(i == C8 || i == F8)
            squares[i] = Entry(Piece(BLACK, BB), i);    //place black bishops

    }

}


//enum // Squares
//{
//    A8 = 56, B8, C8, D8, E8, F8, G8, H8,
//    A7 = 48, B7, C7, D7, E7, F7, G7, H7,
//    A6 = 40, B6, C6, D6, E6, F6, G6, H6,
//    A5 = 32, B5, C5, D5, E5, F5, G5, H5,
//    A4 = 24, B4, C4, D4, E4, F4, G4, H4,
//    A3 = 16, B3, C3, D3, E3, F3, G3, H3,
//    A2 = 8, B2, C2, D2, E2, F2, G2, H2,
//    A1 = 0, B1, C1, D1, E1, F1, G1, H1,
//};

