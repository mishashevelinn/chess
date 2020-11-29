//
// Created by misha on 26/11/2020.
//

#include "Move.h"


Move::Move(int i, int j, const Piece &p, bool promoted) : source(i), dest(j), piece(p) {
}
Move::Move(int i, int j) : source(i), dest(j)
{
    piece = Piece();
}

Move::Move() : source(-1), dest(-1), piece(2, EM) {

}

bool Move::operator==(const Move &rhs) const {
    return source == rhs.source &&
           dest == rhs.dest;
           //piece == rhs.piece;
}

bool Move::operator!=(const Move &rhs) const {
    return !(rhs == *this);
}
