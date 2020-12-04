//
// Created by misha on 27/11/2020.
//

#include <iostream>
#include "MoveList.h"

using namespace std;

MoveList::MoveList() : moves(new Move[128]), size(0) {}

bool MoveList::add(const Move &move) {
    if (size > 128) {
        cerr << __FILE__ << " moves[] Segmentation Fault in line: __LINE__" << endl; //self security measure
        return false;
    }
    moves[size] = move;
    size++;
    return true;
}

bool MoveList::clear() {
    for (int i = 0; i < size; i++)
    {
        moves[i] = Move();//this is for inner order, avoiding storing garbage and easier debugging
    }
    size = 0;   //limiting traversal ability;
return true;
}

bool MoveList::in(Move &move) const {
    for (int i = 0; i < size; i++)
    {
        if (move == moves[i]) {
            move = moves[i];
            return true;
        }
    }

    return false;

}
