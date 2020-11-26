//
// Created by misha on 24/11/2020.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

/* Functionality:
 *      Legal moves calculation and keeping it in a class member
 *      Color of piece
 *      Name of piece
 *      Special class member to handle some special pieces properties
 *                  .       .       .
 */

enum   {WK = 1, WQ = 2, WB = 3, WKN = 4, WR = 5, WP = 6,
        BK = -1, BQ = -2, BB = -3, BKN = -4, BR = -5, BP = -6, EMP = 0};

class Piece {
public:
    Piece();
    Piece(int color, int name);
    int getColor() const { return color;}
    int getName() const { return name;}



    virtual ~Piece();

private:
    int color;
    int name;
    int position;

    bool first_move; //used to handle king's

};


#endif //CHESS_PIECE_H
