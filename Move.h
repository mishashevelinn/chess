//
// Created by misha on 26/11/2020.
//


#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H


#include <ostream>
#include "Square.h"


const static string dic = ".A8B8C8D8E8F8G8H8A7B7C7D7E7F7G7H7A6B6C6D6E6F6G6H6A5B5C5D5E5F5G5H5A4B4C4D4E4F4G4H4A3B3C3D3E3F3G3H3A2B2C2D2E2F2G2H2A1B1C1D1E1F1G1H1";


class Move {
public:
    Move();

    Move(int i, int j, const Piece &p);

    int getSource() const { return source; }

    int getDest() const { return dest; }

    friend std::ostream &operator<<(std::ostream &os, Move const &m) {
        return os << m.piece << ": " << m.getSource()
                  << " --> " << m.getDest();
    }

    bool operator==(const Move &rhs) const;

    bool operator!=(const Move &rhs) const;;



private:
    int source;
    int dest;
    Piece piece;

};


#endif //CHESS_MOVE_H
