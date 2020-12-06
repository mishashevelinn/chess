
#ifndef CHESS_SQUARE_H
#define CHESS_SQUARE_H
#include <ostream>
#include "Piece.h"
#include <string>

using namespace std;


class Square {
public:
    Square();


    friend std::ostream& operator <<(std::ostream &os, const Square &rhs) {

        char c = (rhs.id % 10) + 'a' - 1; //used for debugging
        char r = (rhs.id / 10) + '1' - 2;
        return os << c << r;
    }

//    explicit operator int() const { return id; } //conversion to integer

    Square(int id): owner(IV), id(id)  {};


    Piece const & getOwner() const;

    void setOwner(Piece &owner);


    int const & getId() const;

    bool isOccupied() const;

    void setID(int init_id){ id = init_id ;}

    bool operator==(const Square &rhs) const;

    /*Overloading operators for easier coding, basically surrounding piece setter as member of Square   */

    Square & operator=( Piece & p) { setOwner(p); return *this;}
    Piece owner;


private:

    int id;

};


#endif //CHESS_SQUARE_H
