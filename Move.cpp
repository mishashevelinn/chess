//
// Created by misha on 26/11/2020.
//

#include "Move.h"


Move::Move(int i, int j, const Piece &p, bool is_promoted, const Piece & promoted, bool en_passant)
        : source(i), dest(j), piece(p), promoted(is_promoted), promoted_piece(promoted), en_passant(en_passant) {
}


Move::Move() : source(-1), dest(-1), piece(EM), promoted(false) {

}

bool Move::operator==(const Move &rhs) const {
    return source == rhs.source &&
           dest == rhs.dest;
           //piece == rhs.piece;
}

bool Move::operator!=(const Move &rhs) const {
    return !(rhs == *this);
}
