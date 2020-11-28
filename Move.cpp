//
// Created by misha on 26/11/2020.
//

#include "Move.h"


Move::Move(int i, int j, const Piece &p) : source(i), dest(j), piece(p) {
}


Move::Move() : source(-1), dest(-1), piece(2, EM) {

}
