//
// Created by misha on 24/11/2020.
//

#ifndef CHESS_SQUARE_H
#define CHESS_SQUARE_H

#include "Piece.h"
#include <string>

using namespace std;

enum {
    OCCUPIED = 1, FREE = 0
};

class Square {
public:
    Square();

    int row() const {return (id/10) - 1;} // returns 1 - 8
    int col() const {return (id%10);}

    friend std::ostream& operator <<(std::ostream &os, const Square &rhs)
    {


        char c = (rhs.id%10) + 'a' - 1;
        char r = (rhs.id/10) + '1' - 2;
        return os << c << r;
    }

    explicit operator int() const { return id; } //conversion to integer

    Square(int id): owner(IV), id(id)  {};

    Square(const Piece &owner, int id);

    Piece const &getOwner() const;

    void setOwner(Piece &owner);

    void get_info() const;

    int const &getId() const;

    bool isOccupied() const;

    void setID(int init_id){ id = init_id ;}


    Square(const Piece &owner, const bool Color, const int id);

    //check if the square is not empty for possible move

    /*a critical method - gets all legal moves from owner and intersects it with other's
     * sends info to global storage which contains data about all possible current moves
     */
    bool possible_move(const int &dest);

    //Entries current states to reveal whether the move is possible. parameter - destination
    //piece
    bool isChecked() const; //returns true if king is owner of square and checked, false otherwise
    bool Promotion() const; //first and last rows method, indicates the possibility from pawn's promotion
    bool
    capture(const Piece &new_owner); //in case of capture, gameplay mechanism calls this method to handle capture properly

    bool const &getColor() const;


    bool operator==(const Square &rhs) const;

    void operator=( Piece & p) { setOwner(p); }


private:
    Piece owner;
    int id;


    //


    void info();
};


#endif //CHESS_SQUARE_H
