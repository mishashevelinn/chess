//
// Created by misha on 24/11/2020.
//

#ifndef CHESS_ENTRY_H
#define CHESS_ENTRY_H
#include "Piece.h"

class Entry {
public:
    Entry();
    Entry(const Piece& owner, int id);
    Piece const & getOwner() const;
    bool setOwner(const Piece &owner);

    Entry(const Piece &owner, const bool Color, const int id);

    bool isOccupied() const; //check if the square is not empty for possible move

    /*a critical method - gets all legal moves from owner and intersects it with other's
     * sends info to global storage which contains data about all possible current moves
     */
    bool possible_move(const int& dest);

                                //Entries current states to reveal whether the move is possible. parameter - destination
                                //piece
    bool isChecked() const; //returns true if king is owner of square and checked, false otherwise
    bool Promotion() const; //first and last rows method, indicates the possibility from pawn's promotion
    bool capture(const Piece& new_owner); //in case of capture, gameplay mechanism calls this method to handle capture properly

    bool const & getColor() const;
    int const & getId() const;

private:
    Piece owner;
    int id;

                                    //


    void info();
};


#endif //CHESS_ENTRY_H
