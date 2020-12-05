//
// Created by misha on 24/11/2020.
//



#include "Board.h"
#include <iostream>

using namespace std;
Piece empty = Piece(EM); //an "empty" Piece. Set as owner of square to make square empty.

static int WhitePiecesInit[7] = {0};    //used to initalize primitive arrays of counters.
static int BlackPiecesInit[7] = {0};    //those arrays used to keep track of number of dead and alive pieces


/*Providing default constructor
 *Initializes boolean flags
 * Dynamically allocates array of squares
 * Sets last move with Move default constructor, since when board created, there is no last move
 * Sets pieces-tracking arrays to be arrays of zeroes*/
Board::Board() : board(new Square[120]), mate_to_white(false), mate_to_black(false),
                 stalemate(false), ins_material(false), white_turn(true), promotion(false),
                 white_king_checked(false), lastMove(Move())
                 {

    WhitePieces = WhitePiecesInit;
    BlackPieces = BlackPiecesInit;
}

/*Copy constructor
 *Primitive data members being initialized in constructor initializer
 * Dynamically allocated array is deeply copied*/
Board::Board(const Board & b):WhiteMoves(b.WhiteMoves), BlackMoves(b.BlackMoves), mate_to_white(b.mate_to_white),
                       mate_to_black(b.mate_to_black), stalemate(b.stalemate), ins_material(b.ins_material), white_turn(b.white_turn),
                       promotion(b.promotion), white_king_checked(b.white_king_checked), WhitePieces(b.WhitePieces), BlackPieces(b.BlackPieces) {

    board = new Square[120];
    for (int i = 0; i < 120; i++) {
        board[i] = b.board[i];
    }
}

/*A print function as operator << */
std::ostream &operator<<(std::ostream &os, const Board &rhs) {
    static const char pieces[] = "KQRBNP.pnbrqk";

    for (int row = 8; row >= 1; --row) {
        os << row << " ";
        for (int col = 1; col <= 8; ++col) {
            int number = (row + 1) * 10 + col;
            int piece_name = rhs.get_square(number).getOwner().getName();   //*using advantage of enumeration
            if (piece_name != IV) {                                         //of pieces names
                if (col != 8) os << pieces[piece_name + 6] << " ";
                else os << pieces[piece_name + 6];
            }
        }
        os << std::endl;
    }
    os << "  A B C D E F G H" << std::endl;

    return os;
}


/*Initialize a board to its beginning state.
 * Board is 1D array of integers, surrounded by invalid values (represents an invalid square)
 * It makes a range check easier while finding possible moves.
 * Additional rows of invalid squares at top and bottom
 * leads to friendly enumeration: neighbour rows numbers are differ by 10:


                           BLACK
      110     111 112 113 114 115 116 117 118     119
      100     101 102 103 104 105 106 107 108     109

              A   B   C   D   E   F   G   H
 8    90      A8  92  93  Q    K  96  97  H8      99
 7    80      81  82  83  84  85  86  87  88      89
 6    70      71  72  73  74  75  76  77  78      79
 5    60      61  62  63  64  EM  66  67  68      69
 4    50      51  52  53  54  55  56  57  58      59
 3    40      41  42  EM  44  45  46  47  48      49
 2    30      31  32  33  34  35  36  37  H2      39
 1    20      21  22  23  q    k  26  27  H1      29
              A   B   C   D   E   F   G   H
      10      IV  IV  13  14  15  16  17  18      19
      0       1   2   3   4   IV   6   7   8       9
                           WHITE
      */


/*This method sets a board to its initial state
 * It passes to Piece construcor an integer, repesenteting
 * piece's name and color and call set_square method
 * to populate an array of empty squares*/
void Board::init() {
    int initial[120] = {
            IV, IV, IV, IV, IV, IV, IV, IV, IV, IV,
            IV, IV, IV, IV, IV, IV, IV, IV, IV, IV,
            IV, WR, WN, WB, WQ, WK, WB, WN, WR, IV,
            IV, WP, WP, WP, WP, WP, WP, WP, WP, IV,
            IV, EM, EM, EM, EM, EM, EM, EM, EM, IV,
            IV, EM, EM, EM, EM, EM, EM, EM, EM, IV,
            IV, EM, EM, EM, EM, EM, EM, EM, EM, IV,
            IV, EM, EM, EM, EM, EM, EM, EM, EM, IV,
            IV, BP, BP, BP, BP, BP, BP, BP, BP, IV,
            IV, BR, BN, BB, BQ, BK, BB, BN, BR, IV,
            IV, IV, IV, IV, IV, IV, IV, IV, IV, IV,
            IV, IV, IV, IV, IV, IV, IV, IV, IV, IV};

/*An array of squares initialized according to default constructor of Square,
 * Which provides an empty piece as owner of square.
 * */
    for (int i = 0; i < 120; ++i) {
        Piece piece(initial[i]); //calling a constructor of piece, which gets int (name) as parameter
        set_square(i, piece); //setting it to be owner of corresponding square by calling set_square
    }
}

/*Method which makes a pseudo-legal move.
 * Pseudo Legal Move we call a move, which is possible if check to current player is ignored.
 * Finds all pseudo-legal moves by calling find_legal_moves
 * Checks if an argument Move &m is valid - right color, non-empty origin square and
 * whether a move exists in a list of possible moves - WhiteMoves/BlackMoves.
 * Handles special moves: en passant, castling and promotion*/
bool Board::peek_move(Move &m) {
    find_legal_moves();
    if (!isValidMove(m)) return false;

    Piece moved_piece = board[m.getSource()].getOwner(); //getting a current moved piece in a variable

/************************ *En Passant* *****************************/
    if (m.en_passant) {
        if (white_turn) {
            Move template_move = Move(m.getDest() + 10, m.getDest() - 10);  //expected last move of opponent
            if (template_move != lastMove) return false;
            set_square(m.getDest() - 10, empty);                //making en passant
        } else {
            Move template_move = Move(m.getDest() - 10, m.getDest() + 10); //the calculations are symmetric
            if (template_move != lastMove) return false;
            set_square(m.getDest() + 10, empty);
        }
    }
/********************** *Castling* *********************************/
    if (m.isLeftCastlig() || m.isRightCastlig()) { //a move stores an information whether it is castling or not:
        if (!canCastle(m)) return false;        //if it is, check whether calsting conditions hold.
        do_castling(m);                         //also folding a complex castling exchange into separate funciton
    }


/********************** *Promotion* *********************************/
    if (m.promoted && m.getPromoted().getName() != EM) { //using a move info to determine whether a move is promotion
        moved_piece.setName(m.getPromoted().getName()); //just setting a moved piece's name to be a promoted piece's name
    }                                                   //according to input


/********************** *Do Pseudo-Legal Move **********************************/
                                                        //Finally:
    moved_piece.move_counter_increase();                //if a move is regular or promoted, setting a destanation
    set_square(m.getDest(), moved_piece);            //square's owner to moved piece and origin square - empty.
    set_square(m.getSource(), empty);
    return true;
}

/*This method creates a copy of board in current state and checks wheter
 * a pseudo-legal move that done in peek_move method, sets current player's King to check.
 * If it is, a move can't be done and a function returns false to a Game class caller.
 * In this case, a roll back performed by assigning current object to be a previously made copy.
 * Otherwise, move is approved, a turn passes to other player and checks of Mat and Draw are
 * performed and updates a last_move data member to be a current move.*/
bool Board::make_move(Move &m) {
    Board backup = Board(*this);
    Piece moved_piece = board[m.getDest()].getOwner();

    if (!peek_move(m)) { return false; }

    find_legal_moves(); //Since peek_move has changed a state of board, looking for legal moves secondly.

    /*Roll back move if it leads to current player's check.*/
    if (white_turn && is_white_king_checked()) {
        *this = backup;
        return false;
    }
    if (!white_turn && is_black_king_checked()) {
        *this = backup;
        return false;
    }


    white_turn = !white_turn;
    mat_check();
    ins_material_check();
    lastMove = m;

    return true;


}


/*Checks if player chose an empty square to move it,
 *Player tries to move opponent's piece
 *if a move is in list of possible moves of current player
 * Admit that in() method changes a move.
 * if it's en passant or castling or promotion, adds a certain flags*/
bool Board::isValidMove(Move &m) const {
    if (get_square(m.getSource()) == EM) return false;
    if (get_square(m.getSource()).getOwner() < 0 && white_turn) return false;
    if (get_square(m.getSource()).getOwner() > 0 && !white_turn) return false;
    if (white_turn && WhiteMoves.in(m)) return true; //changes a move
    if (!white_turn && BlackMoves.in(m)) return true;

    return false; //indication of program fail
}

/*A setter, gets index sets new owner. Set owner called by operator=.
 */
void Board::set_square(int position, Piece &new_owner) const {
    board[position].owner = new_owner;
    board[position].setID(position);
}
//A getter
Square const &Board::get_square(int position) const {
    return board[position];
}


/*Iteration all over the board's pieces and squares.
 * For each piece, caclulating a possible moves,
 * Creating a move and storing it in MovesList - a class, containing array of Moves
 * If a move is special move(en passant, castling, promotion) sets a flag, to inform
 * a caller - peek_move()
 * */
void Board::find_legal_moves() {
    WhiteMoves.clear(); //clear all moves lists each time before starting counting
    BlackMoves.clear();


    for (int i = A1; i <= H8; i++) {
        if (get_square(i).isOccupied() && get_square(i).getOwner().getName() != IV) {
            Piece piece = get_square(i).getOwner();
            int j;

            switch (piece.getName()) {
                case WP : //white pawn
                    j = i + 10;
                    if (!get_square(j).isOccupied()) { //one square forward
                        if (i > 80) //check for promotion
                        {
                            {
                                Move move(i, j, piece, true,
                                          WQ); //move object is aware of a piece which has done the move
                                WhiteMoves.add(move);

                                Move move2(i, j, piece, true, WN);
                                WhiteMoves.add((move2));

                                Move move3(i, j, piece, true, WB);
                                WhiteMoves.add(move3);

                                Move move5(i, j, piece, true, WR);
                                WhiteMoves.add(move3);

                            }


                        } else    //regular pawn move
                        {
                            Move move(i, j, piece);
                            WhiteMoves.add(move);
                        }

                        j = i + 20; //two squares forward from second rank
                        if (!get_square(j).isOccupied() && i <= H2) {
                            Move move(i, j, piece, false, Piece());
                            WhiteMoves.add(move);
                        }

                    } //done with one square forward options


                    j = i + 9; //Diagonal capture
                    if (get_square(j).isOccupied() &&
                        get_square(j).getOwner().getName() < 0) {
                        if (i > 80) { //check for promotion
                            Move move(i, j, piece, true, WQ);
                            WhiteMoves.add(move);

                            Move move2(i, j, piece, true, WN);
                            WhiteMoves.add((move2));

                            Move move3(i, j, piece, true, WB);
                            WhiteMoves.add(move3);

                            Move move4(i, j, piece, true, WR);
                            WhiteMoves.add(move4);
                        } else {
                            Move move(i, j, piece, false);
                            WhiteMoves.add(move);
                        }
                    }
                    if (i >= A5 && i <= H5)    //En Passant
                    {
                        if (get_square(i - 1).isOccupied() &&
                            get_square(i - 1).getOwner().getName() == BP &&
                            get_square(i - 1).getOwner().get_counter() == 1) {
                            Move move(i, j, piece, false, Piece(), true); //setting En Passant flag - true
                            WhiteMoves.add(move);
                        }
                    }
                    j = i + 11; //other side diagonal capture
                    if (get_square(j).isOccupied() && get_square(j).getOwner().getName() < 0) {
                        if (i > 80) //Check for promotion
                        {
                            Move move(i, j, piece, true, WQ); //setting a promoted piece
                            WhiteMoves.add(move);             //else it is Empty piece since
                                                                //default constructor is envoked
                            Move move2(i, j, piece, true, WN);
                            WhiteMoves.add((move2));

                            Move move3(i, j, piece, true, WB);
                            WhiteMoves.add(move3);

                            Move move4(i, j, piece, true, WR);
                            WhiteMoves.add(move4);
                        } else {
                            Move move(i, j, piece, false);
                            WhiteMoves.add(move);
                        }
                    }
                    if (A5 <= i && i <= H5)    //En Passant
                    {
                        if (get_square(i + 1).isOccupied() &&
                            get_square(i + 1).getOwner().getName() == BP &&
                            get_square(i + 1).getOwner().get_counter() == 1) {
                            Move move(i, j, piece, false, Piece(), true);
                            WhiteMoves.add(move);
                        }
                    }

                    break; //done with white pawn

                case WN : //white Knight
                {
                    int dirs[8] = {NNW, NNE, NWW, NEE, SSW, SSE, SWW, SEE};
                    for (int k = 0; k < 8; ++k) {
                        int dir = dirs[k];

                        j = i + dir;
                        if (get_square(j).getOwner().getName() != IV)
                            if (get_square(j).getOwner().getName() <= 0) {
                                Move move(i, j, piece, false, Piece());
                                WhiteMoves.add(move);
                            }
                    }
                }
                    break;
                case WB: //White bishop
                {
                    int dirs[4] = {NE, NW, SE, SW};

                    for (int k = 0; k < 4; ++k) {
                        int dir = dirs[k];
                        j = i;
                        while (true) {
                            j += dir;
                            if (get_square(j) == IV) break;
                            if (get_square(j).getOwner().getName() <= 0) {
                                Move move(i, j, piece, false, Piece());
                                WhiteMoves.add(move);
                                if (get_square(j).getOwner().getName() < 0)
                                    break;
                            } else
                                break;
                        }
                    }
                }
                    break;
                case WR :   // White rook
                {
                    int dirs[4] = {N, E, S, W};

                    for (int k = 0; k < 4; ++k) {
                        int dir = dirs[k];
                        j = i;
                        while (true) {
                            j += dir;
                            if (get_square(i) == IV)
                                break;             //edge of the board reached = > all moves in current direction are checked
                            if (get_square(j).getOwner().getName() <= 0)
                                //move counts if next square in current direction is empty or occupied by a black piece
                            {
                                Move move(i, j, piece, false, Piece());
                                WhiteMoves.add(move);
                                if (get_square(j).getOwner().getName() < 0) //disability to jump over black pieces
                                    break;
                            } else        //white piece is on next square in current direction
                                break;
                        }
                    }
                }
                    break; //white rook done
                case WQ : //White queen
                {
                    int dirs[8] = {NE, NW, SE, SW, N, E, S, W};

                    for (int k = 0; k < 8; k++) {
                        int dir = dirs[k];
                        j = i;
                        while (true) {
                            j += dir;
                            if (get_square(j).getOwner().getName() == IV)
                                break;  //stop condition - edge of the board is reached
                            if (get_square(j).getOwner().getName() <=
                                0) //next square in current direction is occupied by black piece or empty
                            {
                                Move move(i, j, piece, false, Piece());
                                WhiteMoves.add(move);
                                if (get_square(j).getOwner().getName() < 0)
                                    break; //next square in current direction is occupied by black piece, can't jump over, done with current direction
                            } else
                                break; //next square in current direction is occupied by white piece, done with current direction
                        }
                    }
                }
                    break;

                case WK : // White king
                {
                    int dirs[8] = {NE, NW, SE, SW, N, E, S, W};

                    for (int k = 0; k < 8; ++k) {
                        int dir = dirs[k];

                        j = i + dir;
                        if (get_square(j).getOwner().getName() != IV)
                            if (get_square(j).getOwner().getName() <= 0) {
                                Move move(i, j, piece, false, Piece());
                                WhiteMoves.add(move);
                            }
                    }
                    /*Castling*/

                    if (i == E1 &&
                        get_square(i + 1).getOwner().getName() == EM && //right side
                        get_square(i + 2).getOwner().getName() == EM &&
                        get_square(H1).getOwner().getName() == WR) {
                        Move move(i, i + 2, piece, false, Piece());
                        WhiteMoves.add(move);
                    }
                    if (i == E1 &&
                        get_square(i - 1).getOwner().getName() == EM  //left side
                        && get_square(i - 2).getOwner().getName() == EM &&
                        get_square(A1).getOwner().getName() == WR) {
                        Move move(i, i - 2, piece, false, Piece());
                        WhiteMoves.add(move);
                    }
                }
                    break;

                default : // Invalid, wrong color, or empty
                    continue;
            }
        }
    }

/****************************  Black's moves ***************************************/
    for (int i = A1; i <= H8; ++i) {
        if (get_square(i).isOccupied() && get_square(i).getOwner().getName() != IV) {
            Piece piece = get_square(i).getOwner();
            int j;

            switch (piece.getName()) {
                case BP : // Black pawn
                    j = i - 10; // One square forward
                    if (!get_square(j).isOccupied()) {
                        if (i < 40) // Check for promotion
                        {
                            {
                                Move move(i, j, piece, true, BQ);
                                BlackMoves.add(move);

                                Move move1(i, j, piece, true, BB);
                                BlackMoves.add(move);

                                Move move2(i, j, piece, true, BN);
                                BlackMoves.add(move2);

                                Move move3(i, j, piece, true, BR);
                                BlackMoves.add(move3);
                            }

                        } else // Regular pawn move
                        {
                            Move move(i, j, piece, false, Piece());
                            BlackMoves.add(move);
                        }

                        j = i - 20; // Two squares forward
                        if (!get_square(j).isOccupied()) {
                            if (i > 80) // Only from seventh rank
                            {
                                Move move(i, j, piece, false, Piece());
                                BlackMoves.add(move);
                            }
                        }
                    }


                    j = i - 9; // Diagonal capture
                    if ((get_square(j).isOccupied() && get_square(j).getOwner().getName() > 0)) {
                        if (i < 40) // Check for promotion
                        {
                            {
                                Move move(i, j, piece, true, BQ);
                                BlackMoves.add(move);

                                Move move1(i, j, piece, true, BB);
                                BlackMoves.add(move);

                                Move move2(i, j, piece, true, BN);
                                BlackMoves.add(move2);

                                Move move3(i, j, piece, true, BR);
                                BlackMoves.add(move3);

                            }


                        } else {
                            Move move(i, j, piece, false);
                            BlackMoves.add(move);
                        }
                    }
                    if (i >= A4 && i <= H4)    //En Passant
                    {
                        if (get_square(i + 1).isOccupied() &&
                            get_square(i + 1).getOwner().getName() == WP &&
                            get_square(i + 1).getOwner().get_counter() == 1) {
                            Move move(i, j, piece, false, Piece(), true);
                            //  cout << move << endl;
                            BlackMoves.add(move);
                        }
                    }

                    j = i - 11; //other side diagonal capture
                    if ((get_square(j).isOccupied() && get_square(j).getOwner().getName() > 0)) {
                        if (i < 40) // Check for promotion
                        {
                            {
                                Move move(i, j, piece, true, BQ);
                                BlackMoves.add(move);

                                Move move2(i, j, piece, true, BN);
                                BlackMoves.add((move2));

                                Move move3(i, j, piece, true, BB);
                                BlackMoves.add(move3);

                                Move move4(i, j, piece, true, BR);
                                BlackMoves.add(move4);
                            }

                        } else {
                            Move move(i, j, piece, false);
                            BlackMoves.add(move);
                        }
                    }//En Passant
                    if (A4 <= i && i <= H4)    //En Passant
                    {
                        if (get_square(i - 1).isOccupied() &&
                            get_square(i - 1).getOwner().getName() == WP &&
                            get_square(i - 1).getOwner().get_counter() == 1) {
                            Move move(i, j, piece, false, Piece(), true);
                            BlackMoves.add(move);
                            //  cout << move << endl;
                        }
                    }
                    break;

                case BN : // Black knight
                {
                    int dirs[8] = {NNW, NNE, NWW, NEE, SSW, SSE, SWW, SEE};

                    for (int k = 0; k < 8; ++k) {
                        int dir = dirs[k];

                        j = i + dir;
                        if (get_square(j).getOwner().getName() != IV)
                            if (get_square(j).getOwner().getName() >= 0) {
                                Move move(i, j, piece, false, Piece());
                                BlackMoves.add(move);
                            }
                    }
                }
                    break;

                case BB : // Black bishop
                {
                    int dirs[4] = {NE, NW, SE, SW};

                    for (int k = 0; k < 4; ++k) {
                        int dir = dirs[k];
                        j = i;
                        while (true) {
                            j += dir;
                            if (get_square(j).getOwner().getName() == IV) break;
                            if (get_square(j).getOwner().getName() >= 0) {
                                Move move(i, j, piece, false, Piece());
                                BlackMoves.add(move);
                                if (get_square(j).getOwner().getName() > 0)
                                    break;
                            } else
                                break;
                        }
                    }
                }

                    break;

                case BR : // Black rook
                {
                    int dirs[4] = {N, E, S, W};

                    for (int k = 0; k < 4; ++k) {
                        int dir = dirs[k];
                        j = i;
                        while (true) {
                            j += dir;
                            if (get_square(j).getOwner().getName() == IV) break;
                            if (get_square(j).getOwner().getName() >= 0) {
                                Move move(i, j, piece, false, Piece());
                                BlackMoves.add(move);
                                if (get_square(j).getOwner().getName() > 0)
                                    break;
                            } else
                                break;
                        }
                    }
                }

                    break;

                case BQ : // Black queen
                {
                    int dirs[8] = {NE, NW, SE, SW, N, E, S, W};

                    for (int k = 0; k < 8; ++k) {
                        int dir = dirs[k];
                        j = i;
                        while (true) {
                            j += dir;
                            if (get_square(j).getOwner().getName() == IV) break;
                            if (get_square(j).getOwner().getName() >= 0) {
                                Move move(i, j, piece, false, Piece());
                                BlackMoves.add(move);
                                if (get_square(j).getOwner().getName() > 0)
                                    break;
                            } else
                                break;
                        }
                    }
                }

                    break;

                case BK : // Black king
                {
                    int dirs[8] = {NE, NW, SE, SW, N, E, S, W};

                    for (int k = 0; k < 8; ++k) {
                        int dir = dirs[k];

                        j = i + dir;
                        if (get_square(j).getOwner().getName() != IV)
                            if (get_square(j).getOwner().getName() >= 0) {
                                Move move(i, j, piece, false, Piece());
                                BlackMoves.add(move);
                            }
                    }
                    /*Castling*/
                    if (i == E8 &&
                        get_square(i + 1).getOwner().getName() == EM && //right side
                        get_square(i + 2).getOwner().getName() == EM &&
                        get_square(H8).getOwner().getName() == BR) {
                        Move move(i, i + 2, piece);
                        BlackMoves.add(move);
                    }
                    if (i == E8 &&
                        get_square(i - 1).getOwner().getName() == EM  //left side
                        && get_square(i - 2).getOwner().getName() == EM &&
                        get_square(A8).getOwner().getName() == BR) {
                        Move move(i, i - 2, piece, false, Piece());
                        BlackMoves.add(move);
                    }
                }

                    break;

                default : // Invalid, wrong color, or empty
                    continue;
            }
        }
    } // done with black pieces



}


/*Finds king, checks if its square is reachable by opponent's piece*/
bool Board::is_checked(int k) const {
    if (get_square(k).getOwner().getName() < 0 && get_square(k).getOwner().getName() != IV) //black piece is inspected
    {
        for (int i = 0; i < WhiteMoves.size; i++) {
            if (get_square(k).getId() == WhiteMoves[i].getDest()) //can white move get to black king?
                return true;                                        // [ ] operator is overloaded
        }
    }
    if (get_square(k).getOwner().getName() > 0 && get_square(k).getOwner().getName() != IV) //white piece is inspected
    {
        for (int i = 0; i < BlackMoves.size; i++) {
            if (get_square(k).getId() == BlackMoves[i].getDest())
                return true;
        }
    }
    return false; //Empty or invalid square

}

bool Board::is_white_king_checked() const { //Finds a king and checks whether its square is checked.
    for (int i = A1; i <= H8; i++) {
        if (get_square(i).getOwner().getName() == WK && is_checked(i))
            return true;
    }
    return false;
}

bool Board::is_black_king_checked() const { //Same as white king.
    for (int i = A1; i <= H8; i++) {
        if (get_square(i).getOwner().getName() == BK && is_checked(i))
            return true;
    }
    return false;
}

/*Since only king moved ny a played explicitly and Rook's reaction has to be programmed,
 * Doing it in separate method*/
void Board::do_castling(Move &move) {
    switch (get_square(move.getSource()).getOwner().getName()) {

        case WK : {
            if (move.isRightCastlig()) {        //Depends on directions of castling, setting a squares to hold
                Piece r(WR);                    //desiered pieces
                set_square(F1, r);
                set_square(H1, empty);
                Piece wk(WK);
                wk.set_counter(-1);
                set_square(move.getDest(), wk);
                set_square(move.getSource(), empty);

            }

            if (move.isLeftCastlig()) {
                Piece r(WR);
                set_square(D1, r);
                set_square(A1, empty);
                Piece wk(WK);
                wk.set_counter(-1);
                set_square(move.getDest(), wk);
                set_square(move.getSource(), empty);
            }
        }
            break;

        case BK:
            if (move.isRightCastlig()) {
                Piece R(BR);
                set_square(F8, R);
                set_square(H8, empty);
                Piece bk(BK);
                bk.set_counter(-1);
                set_square(move.getDest(), bk);
                set_square(move.getSource(), empty);
            }
            if (move.isLeftCastlig()) {
                Piece R(BR);
                set_square(D8, R);
                set_square(A8, empty);
                Piece bk(BK);
                bk.set_counter(-1);
                set_square(move.getDest(), bk);
                set_square(move.getSource(), empty);
            }
            break;
        default:
            cerr << "in function do_castling passed piece is not a king" << __FILE__<< endl; //for debugging
            return;
    }
}


/*Detects a mate situation.
 * For loop:
 *  Each iteration, a copy of current board is created.
 *  A copied board invokes peek_move() for each pseudo-legal move is <Color>Moves list.
 *  After peek_move(), update a moves list according to a new state of game.
 *  If king is in not in check we count peek'd move, because it gets a player's king
 *  out of check situation.
 * If the number of counted moves is 0, king is no where to go from check.
 * If this situation happens when king is currently checked - it's mate.
 * If king's not checked - draw is detected.*/
bool Board::mat_check() {

    //Methodicly implementing mentioned algo. for both colors, depending on turn.
    int w_counter = 0;
    int b_counter = 0;
    if (white_turn) {
        for (int i = 0; i < WhiteMoves.get_size(); i++)
        {
            Board b = Board(*this);
            if (!WhiteMoves[i].isRightCastlig() && !WhiteMoves[i].isLeftCastlig())
            {
                if (b.peek_move(b.WhiteMoves[i]))
                {
                    b.find_legal_moves();
                    if (!b.is_white_king_checked())
                    {
                        w_counter += 1;
                    }
                }
            }
        }
        /*Indication of game-over situation is through global flags to a caller --
         * a function of Game class
         */
        if (w_counter == 0 && is_white_king_checked()) mate_to_white = true;
        if (w_counter == 0 && !is_white_king_checked()) stalemate = true;
    } else {
        for (int i = 0; i < BlackMoves.get_size(); i++) {
            Board b = Board(*this);
            if (b.peek_move(BlackMoves[i])) {
                b.find_legal_moves();
                if (!b.is_black_king_checked())
                    b_counter++;
            }
        }
        if (b_counter == 0 && is_black_king_checked()) mate_to_black = true;
        if (b_counter == 0 && !is_black_king_checked()) stalemate = true;
    }
    return false;
}


/*A sequence of checks to find whether castling is legal:
    *King's currently is not in check
    * Non of squares passed by king towards castling destination isn't checked
    * Castling is first move of both King and Rook
* Left and right sided castlings checked separately for each color*/

bool Board::canCastle(Move &m) {
    int name = get_square(m.getSource()).getOwner().getName();
    if (get_square(m.getSource()).getOwner().get_counter() != 0) return false;  //King's first move
    if (white_turn) {
        if (name == WK) {
            if (get_square(E1).getOwner().get_counter() != 0) return false;     //Rook's first move

            if (m.isLeftCastlig()) //e1 d1 c1
            {
                if (get_square(A1).getOwner().get_counter() != 0) return false; //Squares are free and not checked
                for (int i = C1; i <= E1; i++) {
                    if (is_checked(get_square(i).getId()))
                        return false;
                }
                return true;

            }
            if (m.isRightCastlig()) { //e1 f1 g1
                if (get_square(H1).getOwner().get_counter() != 0) return false;
                for (int i = E1; i <= G1; i++) {
                    if (is_checked(get_square(i).getId()))
                        return false;
                }
                return true;

            }
        }

    } else {
        if (name == BK) {
            if (get_square(E8).getOwner().get_counter() != 0) return false;
            if (m.isLeftCastlig()) //e1 d1 c1
            {
                if (get_square(A8).getOwner().get_counter() != 0) return false;
                for (int i = C8; i <= E8; i++) {  //c8 d8 e8
                    if (is_checked(get_square(i).getId()))
                        return false;
                }
                return true;

            }
            if (m.isRightCastlig()) { //e1 f1 g1
                if (get_square(E1).getOwner().get_counter() != 0) return false;

                for (int i = E8; i <= G8; i++) {
                    if (is_checked(get_square(i).getId()))
                        return false;
                }
                return true;

            }
        }
    }
    return false;
}


/**Each turn, counting how many pieces there are of each color.
 * Using enum of pieces names, to treat them as indexes in array
 * of counters: int WhitePieces[7], BlackPieces[7]
 * Reminder of enum from Piece.h:
          enum {
                  WK = 6, WQ = 5, WR = 4, WB = 3, WN = 2, WP = 1,
                  BK = -6, BQ = -5, BR = -4, BB = -3, BN = -2,  BP = -1, EM = 0, IV = 7
                }
 * if one of counters is 0, there are no pieces of corresponding
 * index left.
 * Interaction with caller via flag data member
 * */

void Board::ins_material_check() {
    for (int i = 0; i < 7; i++) {
        WhitePieces[i] = 0;
        BlackPieces[i] = 0;
    }
    int whitePiecesDead = 0;
    int blackPiecesDead = 0;
    for (int i = 1; i <= 7; i++) {  //counting how many pieces left on board
        for (int j = A1; j <= H8; j++) {
            int name = get_square(j).getOwner().getName();
            if (name > 0 && name != IV) {
                if (name == i)
                    WhitePieces[name]++; //
            }
            if (name < 0) //IV > 0
            {
                if (name * (-1) == i)
                    BlackPieces[name * (-1)]++;

            }
        }
    }

    for (int i = 1; i <= 5; i++) {
        if (WhitePieces[i] == 0) {
            whitePiecesDead++;
        }
        if (BlackPieces[i] == 0) {
            blackPiecesDead++;
        }
    }
    if (whitePiecesDead == 5 && blackPiecesDead == 5) { //required combinations of pieces of both players
        ins_material = true;
    }
    if (whitePiecesDead == 4 && blackPiecesDead == 4 && WhitePieces[WB] == 1 && BlackPieces[WB] == 1) {
        ins_material = true;
    }
    if (whitePiecesDead == 4 && blackPiecesDead == 4 && WhitePieces[WN] == 1 && BlackPieces[WN] == 1) {
        ins_material = true;
    }

}