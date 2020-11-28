//
// Created by misha on 24/11/2020.
//

#include <iostream>
#include "Piece.h"
#include "Board.h"

/*position must be initalized by Square while setting the owner, if piece with position -10 is on board
 * indicates a mistake*/
Piece::Piece(int color_init, int name_init) :
        color(color_init), name(name_init), first_move(true), position(-10) {}


Piece::~Piece() {


}

Piece::Piece() : color(2), name(EM), first_move(false) {

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

void Piece::setColor(int new_Color) {
    this->color = new_Color;
}

bool Piece::operator==(int i) const {
    return name == i;
}

