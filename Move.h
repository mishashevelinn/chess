//
// Created by misha on 26/11/2020.
//

#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H


class Move {
public:
    Move();
    Move(int i, int j);
    int getSource() const{return source;}
    int getDest() const{return dest;}

private:
    int source;
    int dest;
};


#endif //CHESS_MOVE_H
