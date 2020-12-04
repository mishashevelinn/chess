//
// Created by misha on 24/11/2020.
//
#include <ostream>
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
    WK = 6, WQ = 5, WR = 4, WB = 3, WN = 2, WP = 1,
    BK = -6, BQ = -5, BR = -4, BB = -3, BN = -2,  BP = -1, EM = 0, IV = 7
};


using namespace std;


class Piece {
public:
    Piece(): name(EM), move_counter(0) {};

    Piece(int name) : name(name), move_counter(0){}


    int getName() const { return name; }

    bool setPosition(const int &pos);

    int getPosition();

    void setName(int new_name);

    bool operator==(int) const;

    void set_first_move() { first_move = true; }

    bool get_first_move() const { return first_move; }

    void move_counter_increase() { move_counter++;}
    int get_counter() const  { return  move_counter; }
    void set_counter(int i) { move_counter = i;}



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

    void operator=(const Piece & rhs){
        name = rhs.name;
        position = rhs.position;
        first_move = rhs.first_move;
        move_counter = rhs.move_counter;
    }


};


#endif //CHESS_PIECE_H
