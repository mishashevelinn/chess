//
// Created by misha on 24/11/2020.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "MoveList.h"


enum // Squares
{
    A8 = 91, B8, C8, D8, E8, F8, G8, H8,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
}squares;


enum // Directions
{
    N = 10, S = -10, E = -1, W = 1,
    NW = 11, SW = -9, NE = 9, SE = -11,
    NNW = 21, NNE = 19, NWW = 12, NEE = 8,
    SSW = -19, SSE = -21, SWW = -8, SEE = -12
};

class Board {
public:
    Board();

    Board(const Board & b):WhiteMoves(b.WhiteMoves), BlackMoves(b.BlackMoves), mate_to_white(b.mate_to_white),
    mate_to_black(b.mate_to_black), stalemate(b.stalemate), ins_material(b.ins_material), white_turn(b.white_turn),
    promotion(b.promotion), white_king_checked(b.white_king_checked) {
        board = new Square[120];
        for (int i = 0; i < 120; i++) {
            board[i] = b.board[i];
        }

    }


    void init();

    Square *board;
    MoveList WhiteMoves;
    MoveList BlackMoves;

    bool make_move(Move &m);

    Square const &get_square(int position) const;

    const Square &operator[](int position) const { return board[position]; }

    void find_legal_moves(Move &m);

    void test();

    friend std::ostream& operator <<(std::ostream &os, const Board &rhs);

    void set_square(int position, const Piece & new_owner) ;

    bool mate_to_white;
    bool mate_to_black;
    bool stalemate;
    bool ins_material;
    bool white_turn;
    bool promotion;             //Flag to handle pawn's promotion

    bool is_checked(int i) const;

    bool mat_check() ;

private:


    bool white_king_checked;

    bool isValidMove(Move &m) const;

    void init_players();


    bool peek_move(Move &m);

    bool is_white_king_checked() const ;

    bool is_black_king_checked() const ;

    void en_passant(Move &move);

    void do_castling(Move &move) ;

    void mat();



    void roll_back();

    void roll_back(const Move &m);

    void pat_check();

    bool canCastle( Move &m);

    Move lastMove;
};


#endif //CHESS_BOARD_H
