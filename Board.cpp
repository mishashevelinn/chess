//
// Created by misha on 24/11/2020.
//




#include "Board.h"
#include "Entry.h"
#include <iostream>
using namespace std;


Board::Board() : moves(new Move[1024]), squares(new Entry[64]) {







}

void Board::init() {
    squares[E1] = Entry(Piece(WHITE, WK), E1);
    squares[D1] = Entry(Piece(WHITE, WQ), D1);
    squares[E8] = Entry(Piece(BLACK, BK), E8);
    squares[D8] = Entry(Piece(BLACK, BQ), D8);
    for (int i = A8; i <= H1; i++) {
        if (i >= A7 && i <= H7 ) //place White pawns
            squares[i] = Entry(Piece(BLACK, WP), i);
        if(i == A8 || i == H8)//place white rooks
            squares[i] = Entry(Piece(BLACK, WR), i);
        if(i == B8 || i == G8) //place white knights
            squares[i] = Entry(Piece(BLACK, WKN), i);
        if(i == C8 || i == F8 ) //place white bishops
            squares[i] = Entry(Piece(BLACK, WB) , i);
        if(i >= A2 && i <= H2) //place black pawns
            squares[i] = Entry(Piece(WHITE, BP), i);
        if(i == A1 || i == H1)  //place black rooks
            squares[i] = Entry(Piece(WHITE, BR), i);
        if(i == B1 || i == G1)//place black knights
            squares[i] = Entry(Piece(WHITE, BKN), i);
        if(i == C1 || i == F1)//place black bishops
            squares[i] = Entry(Piece(WHITE, BB), i);
        //else

    }

}

void Board::printBoard() {
    for (int i = A8; i <= H1; i++) {
        if(i == A1 || i == A2)
            cout << 9 - (i % 7 +7) << ' ';
        else if (i%8 == 1)
            cout << 9 - i % 7<< ' ';

        cout << ALPHAS[squares[i].getOwner().getName()] << " ";
        if (i !=0  && i % 8 == 0)
            cout <<  endl;
    }
    cout << "  ";
    cout << ALPHABETH << endl;
}





//enum // Squares
//{
//    A8 = 0, B8, C8, D8, E8, F8, G8, H8,
//    A7 = 8, B7, C7, D7, E7, F7, G7, H7,
//    A6 = 16, B6, C6, D6, E6, F6, G6, H6,
//    A5 = 24, B5, C5, D5, E5, F5, G5, H5,
//    A4 = 32, B4, C4, D4, E4, F4, G4, H4,
//    A3 = 40, B3, C3, D3, E3, F3, G3, H3,
//    A2 = 48, B2, C2, D2, E2, F2, G2, H2,
//    A1 = 56, B1, C1, D1, E1, F1, G1, H1,
//};

