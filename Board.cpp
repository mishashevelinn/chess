//
// Created by misha on 24/11/2020.
//




#include "Board.h"
#include "Square.h"
#include <iostream>
using namespace std;


Board::Board() : moves(new Move[1024]), squares(new Square[64]) {

}
/*Initialize a board to its beginning state*/
void Board::init() {
    init_players();
    squares[E1] = Square(Piece(WHITE, WK), E1); //place kings and queens
    squares[D1] = Square(Piece(WHITE, WQ), D1);
    squares[E8] = Square(Piece(BLACK, BK), E8);
    squares[D8] = Square(Piece(BLACK, BQ), D8);
    for (int i = A8; i <= H1; i++) {
        if (i >= A7 && i <= H7 ) //place White pawns
            squares[i] = Square(Piece(BLACK, WP), i);
        else if(i == A8 || i == H8)//place white rooks
            squares[i] = Square(Piece(BLACK, WR), i);
        else if(i == B8 || i == G8) //place white knights
            squares[i] = Square(Piece(BLACK, WKN), i);
        else if(i == C8 || i == F8 ) //place white bishops
            squares[i] = Square(Piece(BLACK, WB) , i);
        else if(i >= A2 && i <= H2) //place black pawns
            squares[i] = Square(Piece(WHITE, BP), i);
        else if(i == A1 || i == H1)  //place black rooks
            squares[i] = Square(Piece(WHITE, BR), i);
        else if(i == B1 || i == G1)//place black knights
            squares[i] = Square(Piece(WHITE, BKN), i);
        else if(i == C1 || i == F1)//place black bishops
            squares[i] = Square(Piece(WHITE, BB), i);
        else if(i != E1 && i != D1 && i != D8 && i != E8)
            squares[i] = Square(Piece(-1, EMP), i );
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

bool Board::make_move(Move m) {
    Piece p1 = squares[m.getSource()].getOwner();
    if(!isValidMove(m)) {
        cout << "make_move got invalid move and returned false";
        return false;
    }
    squares[m.getDest()].setOwner(Piece(p1.getColor(), p1.getName()));
    squares[m.getSource()].setOwner( Piece()); //make source square empty


    cout << "move of " << ALPHAS[squares[m.getDest()].getOwner().getName()] << " succeed" <<endl;
    cout << "move info: " << key.substr(2*m.getSource() - 1, 2) << ", " << key.substr(2*m.getDest() - 1,2 ) << endl;

    return true;


}
/*using array of counters to keep track of dead and alive pieces */
void Board::init_players() {
    whites[WK] = 1;
    whites[WQ] = 1;
    whites[WB] = 2;
    whites[WKN] = 2;
    whites[WR] = 2;
    whites[WP] = 8;

    blacks[BK - 6] = 1;
    whites[BQ - 6] = 1;
    whites[BB - 6] = 2;
    whites[BKN - 6] = 2;
    whites[BR - 6] = 2;
    whites[BP - 6] = 8;
    }

bool Board::isValidMove(const Move &m) const {
    return true;
}


//enum   {WK = 0, WQ = 1, WB = 2, WKN = 3, WR = 4, WP = 5,
//    BK = 6, BQ = 7, BB = 8, BKN = 9, BR = 10, BP = 11, EMP = 12};
//
//


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


