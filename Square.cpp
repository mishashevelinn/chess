#include "Square.h"




/* default constructor provides an empty square, represented by
 * an empty piece - EMP and illegal color 2. "transparent piece"/
 * Default c'tor is needed, because Board class has an array of squares, initialized by default constructor.
 * No need for copy constructor or destructor, because data members are primitive values.
*/
Square::Square() : owner(EM), id(-1) {

}
// Index of square
int const &Square::getId() const {
    return id;
}

//Piece, placed on square
Piece const &Square::getOwner() const {
    return owner;
}


void Square::setOwner(Piece &new_owner) {
    this->owner.setName(new_owner.getName());
    this->owner.set_counter(new_owner.get_counter());
}

bool Square::isOccupied() const {
    if (owner.getName() == EM || owner.getName() == IV)
        return false;
    return true;
}

bool Square::operator==(const Square &rhs) const {
    return getOwner() == rhs.getOwner();
}






