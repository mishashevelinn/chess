//
// Created by misha on 27/11/2020.
//

#include "Move.h"
#include <iostream>
#ifndef CHESS_MOVELIST_H
#define CHESS_MOVELIST_H


class MoveList {
public:
    MoveList();

    MoveList(const MoveList & ml) :size(ml.size) {
        moves = new Move[128];
        for (int i = 0; i < 128; i++) {
            moves[i] = ml.moves[i];
        }
    }

    bool add(const Move &move);

    bool clear();

    int get_size() const { return size; }

    bool in(Move & move) const;

     Move &operator[]( int index) const
    {
        if(index > size + 1)
        {
            cerr << "RANGE ERROR";
            throw exception();
        }

        return moves[index];
    }

    Move *moves;
    int size;






private:

};

#endif //CHESS_MOVELIST_H
