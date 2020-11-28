//
// Created by misha on 24/11/2020.
//




#include "Board.h"
#include <iostream>

using namespace std;

Piece empty = Piece(2, EM);


Board::Board() : board(new Square[120]), turn(WHITE) {

}

std::ostream &operator<<(std::ostream &os, const Board &rhs) {
    static const char pieces[] = "kqrbnp.PNBRQK";

    for (int row = 8; row >= 1; --row) {
        os << row << " ";
        for (int col = 1; col <= 8; ++col) {
            int number = (row + 1) * 10 + col;
            int piece = rhs.get_square(number).getOwner().getName();
            if (piece != IV) {
                os << pieces[piece + 6] << " ";
            }
        }
        os << std::endl;
    }
    os << "  a b c d e f g h" << std::endl;


    if (rhs.white_king_checked) {
        os << "You are in check!" << std::endl;
    }
    //if black king checked
    return os;
}


/*Initialize a board to its beginning state*/
void Board::init() {
    int initial[120] = {
            IV, IV, IV, IV, IV, IV, IV, IV, IV, IV,
            IV, IV, IV, IV, IV, IV, IV, IV, IV, IV,
            IV, WR, WN, WB, WQ, WK, WB, WN, WR, IV,
            IV, WP, WP, WP, WP, WP, WP, WP, WP, IV,
            IV, EM, EM, EM, EM, EM, EM, EM, EM, IV,
            IV, EM, EM, EM, EM, EM, EM, EM, EM, IV,
            IV, EM, EM, EM, EM, EM, EM, EM, EM, IV,
            IV, EM, EM, EM, EM, EM, EM, EM, EM, IV,
            IV, BP, BP, BP, BP, BP, BP, BP, BP, IV,
            IV, BR, BN, BB, BQ, BK, BB, BN, BR, IV,
            IV, IV, IV, IV, IV, IV, IV, IV, IV, IV,
            IV, IV, IV, IV, IV, IV, IV, IV, IV, IV};

    Square board[120];
    for (int i = 21; i < 120; ++i) {
        if (initial[i] != IV) {
            Piece piece(BLACK, initial[i]);
            set_square(i, piece);
        }
    }
}


bool Board::make_move(Move const &m) {
    Piece moved_piece = board[m.getSource()].getOwner();
    if (!isValidMove(m)) {
        cerr << "passing invalid move to make_move(Move m)\n " << __FILE__ << " LINE: " << __LINE__ << endl;
        return false;
    }

    set_square(m.getDest(), moved_piece);
    set_square(m.getSource(), empty);


    cout << "move of " << ALPHAS[board[m.getDest()].getOwner().getName()] << " succeed" << endl;
    cout << "move info: " << key.substr(2 * m.getSource() - 1, 2) << ", " << key.substr(2 * m.getDest() - 1, 2) << endl;

    return true;


}

/*using array of counters to keep track of dead and alive pieces */


bool Board::isValidMove(const Move &m) const {
    if (this[0][m.getSource()].getOwner() == EM) return false; //piece == int overload


    return true;
}

void Board::set_square(int position, Piece &new_owner) const {
    board[position].setOwner(new_owner);
    new_owner.setPosition(position);
    board[position].setID(position);  //TODO adding set id to square
}

Square const &Board::get_square(int position) const {
    return board[position];
}

void Board::find_legal_moves() {
    for (int i = A8; i < H1; i++) {
        if (get_square(i).isOccupied()) {
            Piece piece = get_square(i).getOwner();
            int j;

            switch (piece.getName()) {
                case WP :  //white pawn
                    j = i - 8;   //one square forward
                    if (!get_square(i).isOccupied()) {
                        if (i < 17) //check for promotion
                        {
                            {
                                Move move(i, j, piece); //move object aware of a piece which has done the move
                                WhiteMoves.add(move);   //this can be used to indicate promotion input conditions
                            }
                            {

                            }
                        } else    //regular pawn move
                        {
                            Move move(i, j, piece);
                            WhiteMoves.add(move);
                        }

                        j = i - 16; //two board forward from second rank
                        if (!get_square(j).isOccupied() && i >= A2) {
                            Move move(i, j, piece);
                            WhiteMoves.add(move);
                        }
                    }
            }

        }


    }

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


