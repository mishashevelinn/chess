//
// Created by misha on 24/11/2020.
//

#include <iostream>
#include "Piece.h"
#include "Board.h"

/*position must be initalized by Square while setting the owner, if piece with position -10 is on board
 * indicates a mistake*/


Piece::~Piece() {


}


bool Piece::setPosition(const int &pos) {
//    if (pos % 10 == 0 || pos % 10 == 9 || pos < 21 || pos > 99 ) { //illegal spare columns and rows //TODO Do I need this check?
//        cerr << "setPosition failed, probably while assigning it to owner by a square ";
//        cerr << "class: " << __FILE__ << "line: " << __LINE__ << endl;
//        return false;
//    }
    position = pos;
    return true;
}

int Piece::getPosition() {
    return position;
}

void Piece::setName(int new_name) {
    this->name = new_name;
}


bool Piece::operator==(int i) const {
    return name == i;
}

bool Piece::operator==(const Piece &rhs) const {
    return name == rhs.name;


}

bool Piece::operator!=(const Piece &rhs) const {
    return !(rhs == *this);
}



void Piece::operator=(const Piece &rhs) {
    name = rhs.name;
    position = rhs.position;
    first_move = rhs.first_move;
    move_counter = rhs.move_counter;
}
