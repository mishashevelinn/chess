//
// Created by misha on 24/11/2020.
//

#include <iostream>
#include "Square.h"


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



Square::Square(const Piece &owner, int id): owner(owner), id(id) {


}

/* default constructor provides an empty square, represented by
 * an empty piece - EMP and illegal color 2. "transparent piece"
*/
Square::Square(): owner(2, EMP), id(63) {

}

int const &Square::getId() const {
    return id;
}

Piece const &Square::getOwner() const {
    return owner;
}

void Square::setOwner(Piece new_owner) {
    this->owner = new_owner;
    new_owner.setPosition(id);
}


/*For debugging*/
void Square::get_info() {
    string key = ".A8B8C8D8E8F8G8H8A7B7C7D7E7F7G7H7A6B6C6D6E6F6G6H6A5B5C5D5E5F5G5H5A4B4C4D4E4F4G4H4A3B3C3D3E3F3G3H3A2B2C2D2E2F2G2H2A1B1C1D1E1F1G1H1";
    cout <<"name: "  <<ALPHAS[owner.getName()] << endl;
    cout <<"position: " << key.substr(2*id - 1, 2) << endl;

}




