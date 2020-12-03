//
// Created by misha on 24/11/2020.
//



#include <cstdio>
#include <cstdlib>
#include "Board.h"
#include <iostream>

using namespace std;

Piece empty = Piece(EM);


Board::Board() : board(new Square[120]), white_turn(true), lastMove(Move()) {

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

/*************************En*Passant******************************/
    if (m.en_passant) {
        if (white_turn) {
            Move template_move = Move(m.getDest() + 10, m.getDest() - 10);
            if (template_move != lastMove) return false;
            set_square(m.getDest() - 10, empty);
        } else {
            Move template_move = Move(m.getDest() - 10, m.getDest() + 10);
            if (template_move != lastMove) return false;
            set_square(m.getDest() + 10, empty);
        }
    }
/***********************Castling**********************************/
    if (m.isLeftCastlig() || m.isRightCastlig()) {
        if(!canCastle(m)) return false;
        do_castling(m);
    }


    //Pawn's promotion
    if (m.promoted) {
        if(m.getPromoted().getName() == EM){
            cout << "INVALID INPUT TO MAKE MOVE, PRMOTED PIECE IS MISSING" << endl;
            //TODO RETURN FALSE;
        }
        moved_piece.setName(m.getPromoted().getName());
    }
    moved_piece.move_counter_increase();
    set_square(m.getDest(), moved_piece);
    set_square(m.getSource(), empty);
    return true;
}


bool Board::make_move(Move &m) {
    Board backup = Board(*this);
    Piece moved_piece = board[m.getDest()].getOwner();

    if (!peek_move(m)) { return false; }

    find_legal_moves(m); //TODO do i need this?

    /*roll back move if it leads to current player's check*/
    if(white_turn && is_white_king_checked()) { *this = backup; return false;}
    if(!white_turn && is_black_king_checked()) {*this = backup; return false;}

    moved_piece.move_counter_increase();

    white_turn = !white_turn;
    mat_check();
    lastMove = m;

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

void Board::set_square(int position, const Piece &new_owner) {
    board[position].owner = new_owner;
    board[position].setID(position);
}

Square const &Board::get_square(int position) const {
    return board[position];
}

void Board::find_legal_moves(Move &m) {
    WhiteMoves.clear(); //clear all moves lists each time before starting counting
    BlackMoves.clear();


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
                                Move move(i, j, piece, true,WQ); //move object is aware of a piece which has done the move
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
                            Move move(i, j, piece);
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
                    if (i >= A5 && i <= H5)    //En Passant
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

                    if (i == E1 &&
                        get_square(i + 1).getOwner().getName() == EM && //right side
                        get_square(i + 2).getOwner().getName() == EM &&
                        get_square(H1).getOwner().getName() == WR) {
                        Move move(i, i + 2, piece, false, Piece());
                        WhiteMoves.add(move);
                    }
                    if (i == E1 &&
                    get_square(i - 1).getOwner().getName() == EM  //left side
                        && get_square(i - 2).getOwner().getName() == EM &&
                        get_square(A1).getOwner().getName() == WR) {
                        Move move(i, i - 2, piece, false, Piece());
                        WhiteMoves.add(move);
                    }
                }
                    break;

                default : // Invalid, wrong color, or empty
                    continue;
            }
        }
    }


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
                    /*Castling*/
                    if (i == E8 &&
                        get_square(i + 1).getOwner().getName() == EM && //right side
                        get_square(i + 2).getOwner().getName() == EM &&
                        get_square(H8).getOwner().getName() == BR) {
                        Move move(i, i + 2, piece);
                        BlackMoves.add(move);
                    }
                    if (i == E8 &&
                        get_square(i - 1).getOwner().getName() == EM  //left side
                        && get_square(i - 2).getOwner().getName() == EM &&
                        get_square(A8).getOwner().getName() == BR) {
                        Move move(i, i - 2, piece, false, Piece());
                        BlackMoves.add(move);
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

bool Board::is_checked(int k) const {
    if (get_square(k).getOwner().getName() < 0 && get_square(k).getOwner().getName() != IV) //black piece is inspected
    {
        for (int i = 0; i < WhiteMoves.size; i++) {
            if (get_square(k).getId() == WhiteMoves[i].getDest())
                return true;
        }
    }
    if (get_square(k).getOwner().getName() > 0 && get_square(k).getOwner().getName() != IV) //white piece is inspected
    {
        for (int i = 0; i < BlackMoves.size; i++) {
            if (get_square(k).getId() == BlackMoves[i].getDest())
                return true;
        }
    }
    return false; //Empty or invalid square

}

bool Board::is_white_king_checked() const {
    for (int i = A1; i <= H8; i++) {
        if (get_square(i).getOwner().getName() == WK && is_checked(i))
            return true;
    }
    return false;
}

bool Board::is_black_king_checked() const {
    for (int i = A1; i <= H8; i++) {
        if (get_square(i).getOwner().getName() == BK && is_checked(i))
            return true;
    }
    return false;
}

void Board::en_passant(Move &move) {
    if (white_turn) {
        set_square(move.getDest() - 10, empty);
    } else {
        set_square(move.getDest() + 10, empty);
    }
}

void Board::do_castling(Move &move) {
    switch (get_square(move.getSource()).getOwner().getName()) {

        case WK : {
            if (move.isRightCastlig()) {
                Piece r(WR);
                set_square(F1, r);
                set_square(H1, empty);
                Piece wk(WK);
                wk.set_counter(-1);
                set_square(move.getDest(), wk);
                set_square(move.getSource(), empty);

            }

            if (move.isLeftCastlig()) {
                Piece r(WR);
                set_square(D1, r);
                set_square(A1, empty);
                Piece wk(WK);
                wk.set_counter(-1);
                set_square(move.getDest(), wk);
                set_square(move.getSource(), empty);
            }
        }
            break;

        case BK:
            if (move.isRightCastlig()) {
                Piece R(BR);
                set_square(F8, R);
                set_square(H8, empty);
                Piece bk(BK);
                bk.set_counter(-1);
                set_square(move.getDest(), bk);
                set_square(move.getSource(), empty);
            }
            if (move.isLeftCastlig()) {
                Piece R(BR);
                set_square(D8, R);
                set_square(A8, empty);
                Piece bk(BK);
                bk.set_counter(-1);
                set_square(move.getDest(), bk);
                set_square(move.getSource(), empty);
            }
            break;
        default:
            cerr << "in function do_castling passed piece is not a king" << endl;
            return;
    }
}

bool Board::mat_check() {
    Move m(-1, -1);
    find_legal_moves(m);
    int w_counter = 0;
    int b_counter = 0;
    if (white_turn) {
        Move m(-1, -1);
        find_legal_moves(m);
        for (int i = 0; i < WhiteMoves.get_size(); i++) {
            Board b = Board(*this);

            if (!WhiteMoves[i].isRightCastlig() && !WhiteMoves[i].isLeftCastlig()) {
                if (b.peek_move(b.WhiteMoves[i])) {
                    b.find_legal_moves(m);
                    if (!b.is_white_king_checked()) {
                        w_counter+=1;
                                            }
                }
            }
        }
        if (w_counter == 0 && is_white_king_checked()) mate_to_white = true;
        if(w_counter == 0 &&  is_white_king_checked()) stalemate = true;

    } else {
        Move m(-1, -1);
        find_legal_moves(m);
        for (int i = 0; i < BlackMoves.get_size(); i++) {
            Board b = Board(*this);
            if (b.peek_move(BlackMoves[i])) {
                b.find_legal_moves(m);
                if(!b.is_black_king_checked())
                    b_counter++;
            }
        }
        if (b_counter == 0 && is_black_king_checked()) mate_to_black = true;
        if(b_counter == 0 && !is_black_king_checked()) stalemate = true;
    }
}

bool Board::canCastle(Move &m)
{
    int name = get_square(m.getSource()).getOwner().getName();
    if (get_square(m.getSource()).getOwner().get_counter() != 0) return false;
    if (white_turn) {
        if (name == WK) {
            if(get_square(E1).getOwner().get_counter() != 0) return false;

            if (m.isLeftCastlig()) //e1 d1 c1
            {
                if (get_square(A1).getOwner().get_counter() != 0) return false;
                for (int i = C1; i <= E1; i++) {
                    if (is_checked(get_square(i).getId()))
                        return false;
                }
                return true;

            }
            if (m.isRightCastlig()) { //e1 f1 g1
                if (get_square(H1).getOwner().get_counter() != 0) return false;
                for (int i = E1; i <= G1; i++) {
                    if (is_checked(get_square(i).getId()))
                        return false;
                }
                return true;

            }
        }

    }
    else {
        if (name == BK) {
            if(get_square(E8).getOwner().get_counter() != 0) return false;
            if (m.isLeftCastlig()) //e1 d1 c1
            {
                if (get_square(A8).getOwner().get_counter() != 0) return false;
                for (int i = C8; i <= E8; i++) {  //c8 d8 e8
                    if (is_checked(get_square(i).getId()))
                        return false;
                }
                return true;

            }
            if (m.isRightCastlig()) { //e1 f1 g1
                if (get_square(E1).getOwner().get_counter() != 0) return false;

                for (int i = E8; i <= G8; i++) {
                    if (is_checked(get_square(i).getId()))
                        return false;
                }
                return true;

            }
        }
    }
}