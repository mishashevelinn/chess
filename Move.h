//
// Created by misha on 26/11/2020.
//


#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H


#include <ostream>
#include "Square.h"

class Move {
public:
    Move();
    Move(int i, int j, const Piece &p=Piece(),bool promoted=false, const Piece & promoted_piece=Piece(), bool en_passant=false);


    int getSource() const { return source; }
    int getDest() const { return dest; }
    const Piece & getPromoted() const { return promoted_piece; }
    void setPromoted(int name) { promoted_piece.setName(name);}


    void setSource(int i) {source = i;}
    void setDest(int j) {dest = j;}


    friend std::ostream &operator<<(std::ostream &os, Move const &m) {
        Square square_from(m.getSource());
        Square square_to(m.getDest());
        return os << m.piece << ": " << square_from
                  << " --> " << square_to;
    }

    bool operator==(const Move &rhs) const;

    bool operator!=(const Move &rhs) const;;

    void operator=(const Move & rhs){
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
