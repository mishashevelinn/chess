#include "Piece.h"


Piece::~Piece() {


}

void Piece::setName(int new_name) {
    this->name = new_name;
}

bool Piece::operator==(int i) const {
    return name == i;
}
bool Piece::operator>(int i) const {return  name > i;}
bool Piece::operator<(int i) const { return name < i;}
bool Piece::operator==(const Piece &rhs) const {
    return name == rhs.name;
}

bool Piece::operator!=(const Piece &rhs) const {
    return !(rhs == *this);
}



Piece & Piece::operator=(const Piece &rhs) {
    name = rhs.name;
    position = rhs.position;
    first_move = rhs.first_move;
    move_counter = rhs.move_counter;
    return *this;
}
