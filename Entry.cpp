//
// Created by misha on 24/11/2020.
//

#include "Entry.h"

enum // Squares
{
    A8 = 0, B8, C8, D8, E8, F8, G8, H8,
    A7 = 8, B7, C7, D7, E7, F7, G7, H7,
    A6 = 16, B6, C6, D6, E6, F6, G6, H6,
    A5 = 24, B5, C5, D5, E5, F5, G5, H5,
    A4 = 32, B4, C4, D4, E4, F4, G4, H4,
    A3 = 40, B3, C3, D3, E3, F3, G3, H3,
    A2 = 48, B2, C2, D2, E2, F2, G2, H2,
    A1 = 56, B1, C1, D1, E1, F1, G1, H1,
};



Entry::Entry(const Piece &owner, int id): owner(owner), id(id) {


}

/* default constructor provides an empty square, represented by
 * an empty piece - EMP and illegal color 2. "transparent piece"
*/
Entry::Entry(): owner(2, EMP), id(63) {

}

int const &Entry::getId() const {
    return id;
}

Piece const &Entry::getOwner() const {
    return owner;
}

bool Entry::setOwner(const Piece &owner) {
    this->owner = owner;
}

