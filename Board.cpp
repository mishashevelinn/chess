//
// Created by misha on 24/11/2020.
//




#include "Board.h"
#include <iostream>

using namespace std;

Piece empty = Piece(2, EM);


Board::Board() : board(new Square[120]), white_turn(true) {

}

std::ostream &operator<<(std::ostream &os, const Board &rhs) {
    static const char pieces[] = "KQRBNP.pnbrqk";

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
    os << "  A B C D E F G H" << std::endl;


    if (rhs.white_king_checked && rhs.white_turn) {
        os << "White king checked" << std::endl;
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
    for (int i = 0; i < 120; ++i) {
        if (initial[i] != IV) {
            Piece piece(BLACK, initial[i]);
            set_square(i, piece);
        } else {
            Piece inv_piece(2, IV);
            set_square(i, inv_piece);
        }
    }
}


bool Board::make_move(Move const &m)  {
    Piece moved_piece = board[m.getSource()].getOwner();
    if (!isValidMove(m)) {
        cerr << "ERROR: INVALID MOVE\n " << __FILE__ << " LINE: " << __LINE__ << endl;
        return false;
    }

    set_square(m.getDest(), moved_piece);
    set_square(m.getSource(), empty);


    cout << "move of " << ALPHAS[board[m.getDest()].getOwner().getName()] << " succeed" << endl;

    white_turn  = !white_turn;
    return true;


}

/*using array of counters to keep track of dead and alive pieces */


bool Board::isValidMove(const Move &m) const {
    if (get_square(m.getSource()) == EM) return false;
    if (get_square(m.getSource()).getOwner().getName() < 0 && white_turn) return false;
    if (get_square(m.getSource()).getOwner().getName() > 0 && !white_turn) return false;
    if(white_turn && WhiteMoves.in(m)) return true;
    if(!white_turn && BlackMoves.in(m)) return true;
    return false;
}

void Board::set_square(int position, Piece &new_owner) const {
    board[position] = new_owner;
    new_owner.setPosition(position);
    board[position].setID(position);
}

Square const &Board::get_square(int position) const {
    return board[position];
}

void Board::find_legal_moves() {
    WhiteMoves.clear(); //clear all moves lists each time before starting counting
    BlackMoves.clear();

    if (white_turn) {
        for (int i = A1; i <= H8; i++) {
            if (get_square(i).isOccupied() && get_square(i).getOwner().getName() != IV) {
                Piece piece = get_square(i).getOwner();
                int j;

                switch (piece.getName()) {
                    case WP : //white pawn
                        j = i + 10;
                        if (!get_square(j).isOccupied()) { //one square forward
                            if (i > 80) //check for promotion
                            {
                                {
                                    Move move(i, j, piece); //move object aware of a piece which has done the move
                                    WhiteMoves.add(
                                            move);   //TODO this can be used to indicate promotion input conditions
                                }

                            } else    //regular pawn move
                            {
                                Move move(i, j, piece);
                                WhiteMoves.add(move);
                            }

                            j = i + 20; //two squares forward from second rank
                            if (!get_square(j).isOccupied() && i <= H2) {
                                Move move(i, j, piece);
                                WhiteMoves.add(move);
                            }

                        }//done with one square forward options
                        j = i + 9; //Diagonal capture
                        if (!get_square(j).isOccupied() &&
                            get_square(j).getOwner().getName() < 0) //TODO overload < for pieces
                        {
                            if (i > 80) { //check for promotion
                                Move move(i, j, piece);
                                WhiteMoves.add(move);               //TODO put a flag 'if promoted'
                            } else {
                                Move move(i, j, piece);
                                WhiteMoves.add(move);
                            }
                        }
                        j = i + 11; //other side diagonal captue
                        if (!get_square(j).isOccupied() && get_square(j).getOwner().getName() < 0) {
                            if (i > 80) //Check for promotion
                            {
                                Move move(i, j, piece);
                                WhiteMoves.add(move); //TODO inform about promotion
                            } else {
                                Move move(i, j, piece);
                                WhiteMoves.add(move);
                            }
                        }

                        break; //done with white pawn

                    case WN : //white knight
                    {
                        int dirs[8] = {NNW, NNE, NWW, NEE, SSW, SSE, SWW, SEE};
                        for (int k = 0; k < 8; ++k) {
                            int dir = dirs[k];

                            j = i + dir;
                            if (get_square(j).getOwner().getName() != IV)
                                if (get_square(j).getOwner().getName() <= 0) {
                                    Move move(i, j, piece);
                                    WhiteMoves.add(move);
                                }
                        }
                    }
                        break;
                    case WB: //White bishop
                    {
                        int dirs[4] = {NE, NW, SE, SW};

                        for (int k = 0; k < 4; ++k) {
                            int dir = dirs[k];
                            j = i;
                            while (true) {
                                j += dir;
                                if (get_square(j) == IV) break;
                                if (get_square(j).getOwner().getName() <= 0) {
                                    Move move(i, j, piece);
                                    WhiteMoves.add(move);
                                    if (get_square(j).getOwner().getName() < 0)
                                        break;
                                } else
                                    break;
                            }
                        }
                    }
                        break;
                    case WR :   // White rook
                    {
                        int dirs[4] = {N, E, S, W};

                        for (int k = 0; k < 4; ++k) {
                            int dir = dirs[k];
                            j = i;
                            while (true) {
                                j += dir;
                                if (get_square(i) == IV)
                                    break;             //edge of the board reached = > all moves in current direction are checked
                                if (get_square(j).getOwner().getName() <= 0)
                                    //move counts if next square in current direction is empty or occupied by a black piece
                                {
                                    Move move(i, j, piece);
                                    WhiteMoves.add(move);
                                    if (get_square(j).getOwner().getName() < 0) //disability to jump over black pieces
                                        break;
                                } else        //white piece is on next square in current direction
                                    break;
                            }
                        }
                    }
                        break; //white rook done
                    case WQ : //White queen
                    {
                        int dirs[8] = {NE, NW, SE, SW, N, E, S, W};

                        for (int k = 0; k < 8; k++) {
                            int dir = dirs[k];
                            j = i;
                            while (true) {
                                j += dir;
                                if (get_square(j).getOwner().getName() == IV)
                                    break;  //stop condition - edge of the board is reached
                                if (get_square(j).getOwner().getName() <=0) //next square in current direction is occupied by black piece or empty
                                {
                                    Move move(i, j, piece);
                                    WhiteMoves.add(move);
                                    if (get_square(j).getOwner().getName() < 0)
                                        break; //next square in current direction is occupied by black piece, can't jump over, done with current direction
                                } else
                                    break; //next square in current direction is occupied by white piece, done with current direction
                            }
                        }
                    }
                        break;

                    case WK : // White king
                    {
                        int dirs[8] = {NE, NW, SE, SW, N, E, S, W};

                        for (int k = 0; k < 8; ++k) {
                            int dir = dirs[k];

                            j = i + dir;
                            if (get_square(j).getOwner().getName() != IV)
                                if (get_square(j).getOwner().getName() <= 0) {
                                    Move move(i, j, piece);
                                    WhiteMoves.add(move);
                                }
                        }
                    }
                        break;

                    default : // Invalid, wrong color, or empty
                        continue;
                }
            }
        }

    } else
        for (int i = A1; i <= H8; ++i) {
            if (get_square(i).isOccupied() && get_square(i).getOwner().getName() != IV) {
                Piece piece = get_square(i).getOwner();
                int j;

                switch (piece.getName()) {
                    case BP : // Black pawn
                        j = i - 10; // One square forward
                        if (!get_square(j).isOccupied()) {
                            if (i < 40) // Check for promotion
                            {
                                {
                                    Move move(i, j, piece);
                                    BlackMoves.add(move);
                                }

                            } else // Regular pawn move
                            {
                                Move move(i, j, piece);
                                BlackMoves.add(move);
                            }

                            j = i - 20; // Two squares forward
                            if (!get_square(j).isOccupied()) {
                                if (i > 80) // Only from seventh rank
                                {
                                    Move move(i, j, piece);
                                    BlackMoves.add(move);
                                }
                            }
                        }

                        j = i - 9; // Diagonal capture
                        if ((get_square(j).getOwner().getName() != IV && get_square(j).getOwner().getName() > 0)) {
                            if (i < 40) // Check for promotion
                            {
                                {
                                    Move move(i, j, piece); //TODO inform about promo
                                    BlackMoves.add(move);
                                }


                            } else {
                                Move move(i, j, piece);
                                BlackMoves.add(move);
                            }
                        }

                        j = i - 11; // Diagonal capture
                        if ((get_square(j).getOwner().getName() != IV && get_square(j).getOwner().getName() > 0)) {
                            if (i < 40) // Check for promotion
                            {
                                {
                                    Move move(i, j, piece);
                                    BlackMoves.add(move);
                                }

                            } else {
                                Move move(i, j, piece);
                                BlackMoves.add(move);
                            }
                        }
                        break;

                    case BN : // Black knight
                    {
                        int dirs[8] = {NNW, NNE, NWW, NEE, SSW, SSE, SWW, SEE};

                        for (int k = 0; k < 8; ++k) {
                            int dir = dirs[k];

                            j = i + dir;
                            if (get_square(j).getOwner().getName() != IV)
                                if (get_square(j).getOwner().getName() >= 0) {
                                    Move move(i, j, piece);
                                    BlackMoves.add(move);
                                }
                        }
                    }
                        break;

                    case BB : // Black bishop
                    {
                        int dirs[4] = {NE, NW, SE, SW};

                        for (int k = 0; k < 4; ++k) {
                            int dir = dirs[k];
                            j = i;
                            while (true) {
                                j += dir;
                                if (get_square(j).getOwner().getName() == IV) break;
                                if (get_square(j).getOwner().getName() >= 0) {
                                    Move move(i, j, piece);
                                    BlackMoves.add(move);
                                    if (get_square(j).getOwner().getName() > 0)
                                        break;
                                } else
                                    break;
                            }
                        }
                    }

                        break;

                    case BR : // Black rook
                    {
                        int dirs[4] = {N, E, S, W};

                        for (int k = 0; k < 4; ++k) {
                            int dir = dirs[k];
                            j = i;
                            while (true) {
                                j += dir;
                                if (get_square(j).getOwner().getName() == IV) break;
                                if (get_square(j).getOwner().getName() >= 0) {
                                    Move move(i, j, piece);
                                    BlackMoves.add(move);
                                    if (get_square(j).getOwner().getName() > 0)
                                        break;
                                } else
                                    break;
                            }
                        }
                    }

                        break;

                    case BQ : // Black queen
                    {
                        int dirs[8] = {NE, NW, SE, SW, N, E, S, W};

                        for (int k = 0; k < 8; ++k) {
                            int dir = dirs[k];
                            j = i;
                            while (true) {
                                j += dir;
                                if (get_square(j).getOwner().getName() == IV) break;
                                if (get_square(j).getOwner().getName() >= 0) {
                                    Move move(i, j, piece);
                                    BlackMoves.add(move);
                                    if (get_square(j).getOwner().getName() > 0)
                                        break;
                                } else
                                    break;
                            }
                        }
                    }

                        break;

                    case BK : // Black king
                    {
                        int dirs[8] = {NE, NW, SE, SW, N, E, S, W};

                        for (int k = 0; k < 8; ++k) {
                            int dir = dirs[k];

                            j = i + dir;
                            if (get_square(j).getOwner().getName() != IV)
                                if (get_square(j).getOwner().getName() >= 0) {
                                    Move move(i, j, piece);
                                    BlackMoves.add(move);
                                }
                        }

                    }

                        break;

                    default : // Invalid, wrong color, or empty
                        continue;
                }
            }
        } // done with black pieces







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


}