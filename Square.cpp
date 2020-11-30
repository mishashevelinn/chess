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
Square::Square() : owner(EM), id(-1) {

}

int const &Square::getId() const {
    return id;
}

Piece const &Square::getOwner() const {
    return owner;
}

void Square::setOwner(Piece &new_owner) {
    this->owner.setName(new_owner.getName());
    this->owner.set_counter(new_owner.get_counter());
}


/*For debugging*/
void Square::get_info() const {
    cout << "name: " << owner;
    cout << "position: " << *this << endl;

}

bool Square::isOccupied() const {
    if (owner.getName() == EM || owner.getName() == IV)
        return false;
    return true;
}

bool Square::operator==(const Square &rhs) const {
    return id == rhs.id;
}






