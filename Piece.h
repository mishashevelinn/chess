//
// Created by misha on 24/11/2020.
//
#include <ostream>
#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

/* Functionality:
 *      Holding and providing name, color, and number of move since game start, made by specific piece
 * Explanation:
 *      Name is an integer. If a name less then zero - a piece is black. equals zero if it represents
 *      an empty piece and black otherwise. names are coded by following enumeration for easier code writing.
 *      IV for invalid piece, placed at spare squares, surrounding the Board.
 *
 *      Move counter updates elsewhere if a piece has moved. It is used to analyze special cases like Castling
 */

enum {
    WK = 6, WQ = 5, WR = 4, WB = 3, WN = 2, WP = 1,
    BK = -6, BQ = -5, BR = -4, BB = -3, BN = -2,  BP = -1, EM = 0, IV = 7
};


using namespace std;


class Piece {
public:
    Piece(): name(EM), position(-1), first_move(true), move_counter(0) {};

    Piece(int name) : name(name), position(-1), first_move(true), move_counter(0) {}


    int getName() const { return name; }


    void setName(int new_name);

    bool operator==(int) const;

    void move_counter_increase() { move_counter++;}

    int get_counter() const  { return  move_counter; }

    void set_counter(int i) { move_counter = i;}


/*Operator is not necessary for the assignment and was written for
 * practicing operator overloading and widely used in debugging.
 **/
    friend std::ostream &operator<<(std::ostream &os, Piece const &p) {
        switch (p.getName()) {
            case WP:
                os << "WP";
                break;
            case WN:
                os << "WN";
                break;
            case WB:
                os << "WB";
                break;
            case WR:
                os << "WR";
                break;
            case WQ:
                os << "WQ";
                break;
            case WK:
                os << "WK";
                break;
            case BK:
                os << "BK";
                break;
            case BQ:
                os << "BQ";
                break;
            case BR:
                os << "BR";
                break;
            case BB:
                os << "BB";
                break;
            case BN:
                os << "BN";
                break;
            case BP:
                os << "BP";
                break;
            case EM:
                os << "EM";
                break;
            case IV:
                os << "IV";
                break;
        }
        return os;
    }

    virtual ~Piece();

private:
    int name;
    int position;
    bool first_move; //used to handle king's pawns and rook's stuff
    int move_counter;
public:
    bool operator==(const Piece &rhs) const;
    bool operator!=(const Piece &rhs) const;
    Piece & operator=(const Piece & rhs);
    bool operator<(int) const;
    bool operator>(int) const;
};


#endif //CHESS_PIECE_H
