//
// Created by misha on 27/11/2020.
//

#include <iostream>
#include "MoveList.h"

using namespace std;

MoveList::MoveList() : size(0), moves(new Move[64]) {};

bool MoveList::add(const Move &move) {
    if (size > 64) {
        cerr << __FILE__ << " moves[] Segmentation Fault in line: __LINE__" << endl;
        return false;
    }
    moves[size] = move;
    size++;
    return true;
}

bool MoveList::clear() {
    for (int i = 0; i < size; i++) {    //this is for inner order.
        moves[i] = Move();
    }
    size = 0;   //limiting traversal ability;
}