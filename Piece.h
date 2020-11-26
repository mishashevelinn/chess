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
 *      Contains enums and definitions related to a piece
 */

enum   {WK = 0, WQ = 1, WB = 2, WKN = 3, WR = 4, WP = 5,
        BK = 6, BQ = 7, BB = 8, BKN = 9, BR = 10, BP = 11, EMP = 12};
#define ALPHAS "KQbnrpkqBNRP."



#define BLACK 0
#define WHITE 1


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

    bool first_move; //used to handle king's pawns and rook's stuff

};


#endif //CHESS_PIECE_H
