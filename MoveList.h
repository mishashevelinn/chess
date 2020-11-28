//
// Created by misha on 27/11/2020.
//

#include "Move.h"

#ifndef CHESS_MOVELIST_H
#define CHESS_MOVELIST_H


class MoveList {
public:
    MoveList();

    bool add(const Move &move);

    bool clear();

    int get_size() const { return size; }

    const Move &operator[](unsigned int index) const { return moves[index]; }

    Move *moves;
    int size;

private:

};

#endif //CHESS_MOVELIST_H
