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

enum {
    WK = 6, WQ = 5, WB = 3, WN = 2, WR = 4, WP = 1,
    BK = -6, BQ = -5, BB = -3, BN = -2, BR = -4, BP = -1, EM = 0, IV = 99
}pieces;

static std::string names = "BKBQBRBBBNBPEMWPWRWNWBWQWK";

using namespace std;
#define ALPHAS "KQbnrpkqBNRP."


#define BLACK 0
#define WHITE 1


class Piece {
public:
    Piece();

    Piece(int color, int name);
    Piece(int color) : name(10){};

    int getColor() const { return color; }

    int getName() const { return name; }

    bool setPosition(const int &pos);

    int getPosition();

    void setName(int new_name);

    void setColor(int new_Color);

    bool operator==(int) const;

    friend std::ostream &operator<<(std::ostream &os, Piece const &p) {
        return os << names.substr(p.getName()+6, 2) << endl;
    };

    virtual ~Piece();

private:
    int color;
    int name;
    int position;

    bool first_move; //used to handle king's pawns and rook's stuff

};


#endif //CHESS_PIECE_H
