//
// Created by misha on 24/11/2020.
//



#include <cstdio>
#include <cstdlib>
#include "Board.h"
#include <iostream>

using namespace std;

Piece empty = Piece(EM);


Board::Board() : board(new Square[120]), white_turn(true) {

}

std::ostream &operator<<(std::ostream &os, const Board &rhs) {
    static const char pieces[] = "KQRBNP.pnbrqk";

    for (int row = 8; row >= 1; --row) {
        os << row << " ";
        for (int col = 1; col <= 8; ++col) {
            int number = (row + 1) * 10 + col;
            int piece_name = rhs.get_square(number).getOwner().getName();   //*using advantage of enumeration
            if (piece_name != IV) {                                         //of pieces names
                os << pieces[piece_name + 6] << " ";
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


    for (int i = 0; i < 120; ++i) {
        if (initial[i] != IV) {
            Piece piece(initial[i]);
            set_square(i, piece);
        } else {
            Piece inv_piece(IV);
            set_square(i, inv_piece);
        }
    }
}

bool Board::peek_move(Move &m) {

    find_legal_moves(m);

    if (!isValidMove(m)) {
        cerr << "ERROR: INVALID MOVE\n " << __FILE__ << " LINE: " << __LINE__ << endl;
        return false;
    }

    Piece moved_piece = board[m.getSource()].getOwner();

    if (m.en_passant) {
        switch (white_turn) {
            case true:
                set_square(m.getDest() - 10, empty);
                cout<< "EMPASANT" << endl;
                //TODO decrement black pawns counter
            case false:
                set_square(m.getDest() + 10, empty);
                //TODO decrement white pawns counter
        }
    }

    //White king's castling

    if (get_square(m.getSource()).getOwner() == WK) {
        if (m.getDest() - m.getSource() == 2) {
            Piece r(WR);
            set_square(F1, r);
            set_square(H1, empty);
        }
        if (m.getDest() - m.getSource() == -2) {
            Piece r(WR);
            set_square(D1, r);
            set_square(A1, empty);
        }
    }
    //Black king's castling
    if (get_square(m.getSource()).getOwner() == BK) {
        if (m.getDest() - m.getSource() == 2) {
            Piece R(BR);
            set_square(F8, R);
            set_square(H8, empty);
        }
        if (m.getDest() - m.getSource() == -2) {
            Piece r(WR);
            set_square(D8, r);
            set_square(A8, empty);
        }
    }
    //Pawn's promotion
    if (m.promoted) {
        moved_piece.setName(m.getPromoted().getName());
    }
    moved_piece.move_counter_increase();
    set_square(m.getDest(), moved_piece);
    set_square(m.getSource(), empty);
    return true;


}


bool Board::make_move(Move &m) {
    if (!peek_move(m)) { return false; }
    find_legal_moves(m);


    Piece moved_piece = board[m.getSource()].getOwner();
    moved_piece.move_counter_increase();

    switch (white_turn) {
        case true:
            for (int i = A1; i <= H8; i++) {
                if (get_square(i).getOwner() == WK && is_ckecked(get_square(i))) {
                    set_square(m.getSource(), moved_piece);
                    set_square(m.getDest(), empty);
                    return false;
                }

            }
        case false:
            for (int i = A1; i <= H8; i++) {
                if (get_square(i).getOwner() == BK && is_ckecked(get_square(i))) {
                    set_square(m.getSource(), moved_piece);
                    set_square(m.getDest(), empty);
                    return false;
                }

            }
    }


    cout << moved_piece.get_counter() << " move of " << moved_piece << " succeed" << endl;
    white_turn = !white_turn;
    return true;


}

/*using array of counters to keep track of dead and alive pieces */


bool Board::isValidMove(Move &m) const {
    if (get_square(m.getSource()) == EM) return false;
    if (get_square(m.getSource()).getOwner().getName() < 0 && white_turn) return false;
    if (get_square(m.getSource()).getOwner().getName() > 0 && !white_turn) return false;
    if (white_turn && WhiteMoves.in(m)) return true;
    if (!white_turn && BlackMoves.in(m)) return true;
    return false;
}

void Board::set_square(int position, Piece &new_owner) const {
    board[position].owner = new_owner;
    new_owner.setPosition(position);
    board[position].setID(position);
}

Square const &Board::get_square(int position) const {
    return board[position];
}

void Board::find_legal_moves(Move & m) {
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
                                    Move move(i, j, piece, true,
                                              WQ); //move object is aware of a piece which has done the move
                                    WhiteMoves.add(move);

                                    Move move2(i, j, piece, true, WN);
                                    WhiteMoves.add((move2));

                                    Move move3(i, j, piece, true, WB);
                                    WhiteMoves.add(move3);

                                    Move move5(i, j, piece, true, WR);
                                    WhiteMoves.add(move3);

                                }


                            } else    //regular pawn move
                            {
                                Move move(i, j, piece, false, Piece());
                                WhiteMoves.add(move);
                            }

                            j = i + 20; //two squares forward from second rank
                            if (!get_square(j).isOccupied() && i <= H2) {
                                Move move(i, j, piece, false, Piece());
                                WhiteMoves.add(move);
                            }

                        }//done with one square forward options
                        j = i + 9; //Diagonal capture
                        if (get_square(j).isOccupied() &&
                            get_square(j).getOwner().getName() < 0) {
                            if (i > 80) { //check for promotion
                                Move move(i, j, piece, true, WQ);
                                WhiteMoves.add(move);

                                Move move2(i, j, piece, true, WN);
                                WhiteMoves.add((move2));

                                Move move3(i, j, piece, true, WB);
                                WhiteMoves.add(move3);

                                Move move4(i, j, piece, true, WR);
                                WhiteMoves.add(move4);
                            } else {
                                Move move(i, j, piece, false);
                                WhiteMoves.add(move);
                            }
                        }
                        if (A5 <= i && i <= H5)    //En Passant
                        {
                            if (get_square(i - 1).isOccupied() &&
                                get_square(i - 1).getOwner().getName() == BP &&
                                get_square(i - 1).getOwner().get_counter() == 1) {
                                Move move(i, j, piece, false, Piece(), true);
                                WhiteMoves.add(move);
                            }
                        }
                        j = i + 11; //other side diagonal captue
                        if (get_square(j).isOccupied() && get_square(j).getOwner().getName() < 0) {
                            if (i > 80) //Check for promotion
                            {
                                Move move(i, j, piece, true, WQ);
                                WhiteMoves.add(move);

                                Move move2(i, j, piece, true, WN);
                                WhiteMoves.add((move2));

                                Move move3(i, j, piece, true, WB);
                                WhiteMoves.add(move3);

                                Move move4(i, j, piece, true, WR);
                                WhiteMoves.add(move4);
                            } else {
                                Move move(i, j, piece, false);
                                WhiteMoves.add(move);
                            }
                        }
                        if (A5 <= i && i <= H5)    //En Passant
                        {
                            if (get_square(i + 1).isOccupied() &&
                                get_square(i + 1).getOwner().getName() == BP &&
                                get_square(i + 1).getOwner().get_counter() == 1) {
                                Move move(i, j, piece, false, Piece(), true);
                                WhiteMoves.add(move);
                            }
                        }

                        break; //done with white pawn

                    case WN : //white Knight
                    {
                        int dirs[8] = {NNW, NNE, NWW, NEE, SSW, SSE, SWW, SEE};
                        for (int k = 0; k < 8; ++k) {
                            int dir = dirs[k];

                            j = i + dir;
                            if (get_square(j).getOwner().getName() != IV)
                                if (get_square(j).getOwner().getName() <= 0) {
                                    Move move(i, j, piece, false, Piece());
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
                                    Move move(i, j, piece, false, Piece());
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
                                    Move move(i, j, piece, false, Piece());
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
                                if (get_square(j).getOwner().getName() <=
                                    0) //next square in current direction is occupied by black piece or empty
                                {
                                    Move move(i, j, piece, false, Piece());
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
                                    Move move(i, j, piece, false, Piece());
                                    WhiteMoves.add(move);
                                }
                        }
                        /*Castling*/
                        if (get_square(i).getOwner().get_counter() == 0 && //king's first move
                            get_square(A1).getOwner().getName() == WR &&    //Left Rook's first move
                            get_square(A1).getOwner().get_counter() == 0) {
                            int empty_squares = 0;
                            for (int k = B1; k <= D1; k++) {
                                if (!get_square(k).isOccupied())
                                    empty_squares++;
                            }
                            if (empty_squares == 3) //squares are free
                            {
                                if (!is_ckecked(get_square(D1)) &&
                                    !is_ckecked(get_square(C1))) {   //free squares are not checked
                                    Move move(i, i - 2);
                                    WhiteMoves.add(move);
                                }
                            }


                        }
                        if (get_square(i).getOwner().get_counter() == 0 && //king's first move
                            get_square(H1).getOwner().getName() == WR &&    //Right Rook's first move
                            get_square(H1).getOwner().get_counter() == 0) {
                            int empty_squares = 0;
                            for (int k = E1; k <= G1; k++) {
                                if (!get_square(k).isOccupied())
                                    empty_squares++;
                            }
                            if (empty_squares == 2) {
                                if (!is_ckecked(get_square(F1)) &&
                                    !is_ckecked(get_square(G1))) {   //free squares are not in check
                                    Move move(i, i + 2);
                                    WhiteMoves.add(move);
                                }
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
                                    Move move(i, j, piece, true, Piece());
                                    BlackMoves.add(move);
                                }

                            } else // Regular pawn move
                            {
                                Move move(i, j, piece, false, Piece());
                                BlackMoves.add(move);
                            }

                            j = i - 20; // Two squares forward
                            if (!get_square(j).isOccupied()) {
                                if (i > 80) // Only from seventh rank
                                {
                                    Move move(i, j, piece, false, Piece());
                                    BlackMoves.add(move);
                                }
                            }
                        }

                        j = i - 9; // Diagonal capture
                        if ((get_square(j).getOwner().getName() != IV && get_square(j).getOwner().getName() > 0)) {
                            if (i < 40) // Check for promotion
                            {
                                {
                                    Move move(i, j, piece, true, BQ);
                                    BlackMoves.add(move);

                                    Move move1(i, j, piece, true, BB);
                                    BlackMoves.add(move);

                                    Move move2(i, j, true, BN);
                                    BlackMoves.add(move2);

                                    Move move3(i, j, true, BR);
                                    BlackMoves.add(move3);

                                }


                            } else {
                                Move move(i, j, piece, false, Piece());
                                BlackMoves.add(move);
                            }
                        }
                        if (A4 <= i && i <= H4)    //En Passant
                        {
                            if (get_square(i - 1).isOccupied() &&
                                get_square(i - 1).getOwner().getName() == WP &&
                                get_square(i - 1).getOwner().get_counter() == 1) {
                                Move move(i, j, piece, false, Piece(), true);
                                WhiteMoves.add(move);
                            }
                        }

                        j = i - 11; // Diagonal capture
                        if ((get_square(j).getOwner().getName() != IV && get_square(j).getOwner().getName() > 0)) {
                            if (i < 40) // Check for promotion
                            {
                                {
                                    Move move(i, j, piece, true, Piece());
                                    BlackMoves.add(move);
                                }

                            } else {
                                Move move(i, j, piece, false, Piece());
                                BlackMoves.add(move);
                            }
                        }//En Passant
                        if (A4 <= i && i <= H4)    //En Passant
                        {
                            if (get_square(i + 1).isOccupied() &&
                                get_square(i + 1).getOwner().getName() == WP &&
                                get_square(i + 1).getOwner().get_counter() == 1) {
                                Move move(i, j, piece, false, Piece(), true);
                                WhiteMoves.add(move);
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
                                    Move move(i, j, piece, false, Piece());
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
                                    Move move(i, j, piece, false, Piece());
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
                                    Move move(i, j, piece, false, Piece());
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
                                    Move move(i, j, piece, false, Piece());
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
                                    Move move(i, j, piece, false, Piece());
                                    BlackMoves.add(move);
                                }
                        }
                        if (get_square(i).getOwner().get_counter() == 0 && //king's first move
                            get_square(A8).getOwner().getName() == BR &&    //Left Rook's first move
                            get_square(A8).getOwner().get_counter() == 0) {
                            int empty_squares = 0;
                            for (int k = C8; k <= D8; k++) {
                                if (!get_square(k).isOccupied() && !is_ckecked(get_square(k)))
                                    empty_squares++;
                            }
                            if (empty_squares == 2) {
                                Move move(i, i - 2);
                                WhiteMoves.add(move);
                            }


                        }
                        if (get_square(i).getOwner().get_counter() == 0 && //king's first move
                            get_square(H8).getOwner().getName() == BR &&    //Right Rook's first move
                            get_square(H8).getOwner().get_counter() == 0) {
                            int empty_squares = 0;
                            for (int k = F1; k <= G1; k++) {
                                if (!get_square(k).isOccupied() && !is_ckecked(get_square(k)))
                                    empty_squares++;
                            }
                            if (empty_squares == 2) {
                                Move move(i, i + 2);
                                WhiteMoves.add(move);
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

bool Board::is_ckecked(const Square &s) const {
    if (s.getOwner().getName() < 0 && s.getOwner().getName() != IV) //black piece is inspected
    {
        for (int i = 0; i < WhiteMoves.size; i++) {
            if (s.getId() == WhiteMoves[i].getDest())
                return true;
        }
    }
    if (s.getOwner().getName() > 0 && s.getOwner().getName() != IV) //white piece is inspected
    {
        for (int i = 0; i < BlackMoves.size; i++) {
            if (s.getId() == BlackMoves[i].getDest())
                return true;
        }
    }
    return false; //Empty or invalid square

}
