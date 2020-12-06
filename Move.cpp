#include "Move.h"

/*No heap allocations, each time there is a need to copy a move, it is copied within
 * dinamicly allocated array - MoveList class. so its copied properly*/
Move::Move(int i, int j, const Piece &p, bool is_promoted, const Piece &promoted, bool en_passant)
        : source(i), dest(j), promoted_piece(promoted), piece(p), promoted(is_promoted), en_passant(en_passant) {
}


Move::Move() : source(-1), dest(-1), piece(EM), promoted(false) {

}

bool Move::operator==(const Move &rhs) const {
    return source == rhs.source &&
           dest == rhs.dest &&
           promoted_piece == rhs.promoted_piece; //promoted piece is being compared, since
    //it's passed from user and possible moves,
    //allows promotion also contains certain
    //promoted piece.

}

bool Move::operator!=(const Move &rhs) const {
    return !(rhs == *this);
}
