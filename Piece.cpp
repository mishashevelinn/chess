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

Piece::Piece() : color(2), name(EMP), first_move(false) {

}

bool Piece::setPosition(const int &pos) {
    if (pos <= A8 || pos >= H1) {
        cerr << "Attempt to set illegal position for owner while setting owner of Square\n";
        return false;
    }
    position = pos;
    return true;
}

