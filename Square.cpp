//
// Created by misha on 24/11/2020.
//

#include <iostream>
#include "Square.h"




Square::Square(const Piece &owner, int id) : owner(owner), id(id) {
}

/* default constructor provides an empty square, represented by
 * an empty piece - EMP and illegal color 2. "transparent piece"
*/
Square::Square() : owner(2, EM), id(-1) {

}

int const &Square::getId() const {
    return id;
}

Piece const &Square::getOwner() const {
    return owner;
}

void Square::setOwner(Piece &new_owner) {
    this->owner.setName(new_owner.getName());
    this->owner.setColor(new_owner.getColor());
}


/*For debugging*/
void Square::get_info() const {
    string key = ".A8B8C8D8E8F8G8H8A7B7C7D7E7F7G7H7A6B6C6D6E6F6G6H6A5B5C5D5E5F5G5H5A4B4C4D4E4F4G4H4A3B3C3D3E3F3G3H3A2B2C2D2E2F2G2H2A1B1C1D1E1F1G1H1";
    cout << "name: " << owner;
    cout << "position: " << *this << endl;

}

bool Square::isOccupied() const {
    if (owner.getName() == EM)
        return false;
    return true;
}

bool Square::operator==(const Square &rhs) const {
    return id == rhs.id;
}






