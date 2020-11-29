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


    void init();

    Square *board;
    MoveList WhiteMoves;
    MoveList BlackMoves;

    bool make_move(const Move &m);

    Square const &get_square(int position) const;

    const Square &operator[](int position) const { return board[position]; }

    void find_legal_moves();

    void test();

    friend std::ostream& operator <<(std::ostream &os, const Board &rhs);

    void set_square(int position, Piece &new_owner) const;



private:
    string key = ".A8B8C8D8E8F8G8H8A7B7C7D7E7F7G7H7A6B6C6D6E6F6G6H6A5B5C5D5E5F5G5H5A4B4C4D4E4F4G4H4A3B3C3D3E3F3G3H3A2B2C2D2E2F2G2H2A1B1C1D1E1F1G1H1";


    bool white_king_checked;
    bool white_turn;


    bool isValidMove(const Move &m) const;

    void init_players();



};


#endif //CHESS_BOARD_H
