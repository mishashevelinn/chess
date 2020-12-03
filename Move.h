//
// Created by misha on 26/11/2020.
//


#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H


#include <ostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include "Square.h"

class Move {
public:
    Move();
    Move(int i, int j, const Piece &p=Piece(),bool promoted=false, const Piece & promoted_piece=Piece(), bool en_passant=false);
    Move( const Move& m):source(m.source), dest(m.dest), piece(m.piece), promoted_piece(m.promoted_piece) {}


    int getSource() const { return source; }
    int getDest() const { return dest; }
    const Piece & getPromoted() const { return promoted_piece; }
    void setPromoted(const Piece & piece) { promoted_piece.setName(piece.getName());}


    void setSource(int i) {source = i;}
    void setDest(int j) {dest = j;}


    friend std::ostream &operator<<(std::ostream &os, Move const &m) {
        Square square_from(m.getSource());
        Square square_to(m.getDest());
        return os << m.piece << ": " << square_from
                  << " --> " << square_to;
    }

    bool isRightCastlig() const {return ((dest - source) == 2) && (piece.getName() == BK || piece.getName() == WK);}
    bool isLeftCastlig() const {return ((dest - source) == -2) && (piece.getName() == BK || piece.getName() == WK);}

    bool operator==(const Move &rhs) const;

    bool operator!=(const Move &rhs) const;;

    Move & operator=(const Move & rhs){
        source = rhs.source;
        dest = rhs.dest;
        piece = rhs.piece;
        promoted_piece = rhs.promoted_piece;
        en_passant = rhs.en_passant;
    }

    bool promoted;


    bool en_passant;
private:
    int source;
    int dest;
    Piece piece;
    Piece promoted_piece;


};


#endif //CHESS_MOVE_H
