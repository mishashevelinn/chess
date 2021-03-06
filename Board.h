// Created by misha on 24/11/2020.




#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "MoveList.h"

/*Enum provides convenient way for indexing squares
  And makes loops and range definitions clearer
 */
enum // Squares
{
    A8 = 91, B8, C8, D8, E8, F8, G8, H8,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A1 = 21, B1, C1, D1, E1, F1, G1, H1
};


enum // Directions. used for easier calculations. adding each of directions to current direction
{    //gives a destination coordinate.
    N = 10, S = -10, E = -1, W = 1,
    NW = 11, SW = -9, NE = 9, SE = -11,
    NNW = 21, NNE = 19, NWW = 12, NEE = 8,
    SSW = -19, SSE = -21, SWW = -8, SEE = -12
};


class Board {
public:
    Board();
    Board(const Board & b);

    void init() const;


    bool mate_to_white;
    bool mate_to_black;
    bool stalemate;
    bool ins_material;
    bool white_turn;
    bool promotion;
    bool white_king_checked;


    bool make_move(Move &m);

    Square const &get_square(int position) const;

    const Square &operator[](int position) const { return board[position]; }

    void find_legal_moves();


    friend std::ostream &operator<<(std::ostream &os, const Board &rhs);

    void set_square(int position, Piece &new_owner) const;

    //Flag to handle pawn's promotion

    bool is_checked(int i) const;

    bool mat_check();

    Board &operator=(const Board &rhs) {
        if (this == &rhs)
            return *this;

        this->board = new Square[128];
        for (int i = 0; i < 128; i++) {
            this->board[i] = rhs.board[i];
        }
        return *this;
    }

    virtual ~Board();


private:
    Square *board;
    MoveList WhiteMoves;
    MoveList BlackMoves;
    Move lastMove;
    int *WhitePieces;
    int *BlackPieces;


    bool isValidMove(Move &m) const;


    bool peek_move(Move &m);

    bool is_white_king_checked() const;

    bool is_black_king_checked() const;


    void do_castling(Move &move) const;


    bool canCastle(Move &m) const;


    void ins_material_check();

};


#endif //CHESS_BOARD_H
