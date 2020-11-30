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

    bool add(const Move &move);

    bool clear();

    int get_size() const { return size; }

    bool in(Move & move) const;

    const Move &operator[](unsigned int index) const
    {
        if(index > size + 1)
        {
            cout << "RANGE ERROR";
            throw exception();
        }

        return moves[index];
    }

    Move *moves;
    int size;






private:

};

#endif //CHESS_MOVELIST_H
