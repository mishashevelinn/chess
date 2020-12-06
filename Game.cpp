#include <sstream>
#include "Game.h"

/*This class is responsible for gameplay loop and console interaction.
 * Invokes corresponding methods of Board and uses its own methods
 * checks input
 * parsing of string to move, if legal
 * No copy c'tor or operator= because only one played at a time.
 * Destructor to delete a dynamically allocated pointer board.
 * */
using namespace std;

void Game::game_loop() {

    board->init();  //initializing a board
    cout << *board;
    //If one of following situations occurs, the program ends.
    string str_move;
    while (true) {
        if (board->ins_material || board->mate_to_black || board->mate_to_white || board->stalemate) {
            if (board->mate_to_black) cout << "White wins with checkmate!" << endl;
            if (board->mate_to_white) cout << "Black wins with checkmate!" << endl;
            if (board->stalemate) cout << "The game is drawn due to stalemate!" << endl;
            if (board->ins_material) cout << "The game is drawn due to insufficient material!" << endl;
            return;
        }

        cout << num_turn << ") ";
        board->white_turn ? cout << "White's turn, please enter a move:" : cout
                << "Black's turn, please enter a move:";
        cout << endl;
        err:
        getline(cin, str_move); //getting a string each time
        if (!cin) { return; }               //python tests adaptation
        if (valid_option(str_move)) {
            Move move;                      //temporary move is updated by str_to_move, if spelling is ok
            str_to_move(str_move, move);
            if (!board->make_move(move))    //if move is illegal, print an error message and loop over
            {
                cerr << num_turn << ") " << "Illegal move; please enter a move:" << endl;
                goto err;
            } else {
                num_turn++; //keeping track of number of turns
                cout << *board;
                continue;
            }
        } else {
            cerr << num_turn << ") " << "Invalid input; please enter a move: ";
            goto err;
        }
    }

}

Game::~Game() {
    delete board;
}

/*Checks spelling and if passed a check, converst the string to move
 * for passing it to board by caller*/
bool Game::valid_option(const string &str) {
    int word_counter = 0;
    string temp;
    stringstream s(str);
    while (s >> temp) { word_counter++; }   //Counting words
    if (word_counter < 2 || word_counter > 3 ||
        (board->promotion && word_counter != 3)) //shouldn't be longer than 2 or 3 if promotion
        return false;

    word_counter = 0;
    stringstream ss(str);

    while (ss >> temp) {
        word_counter++;
        if (word_counter == 3) { //promotion third word check
            cout << temp.length();
            if (temp.length() != 1) { return false; }
            char c = temp[0];
            if (board->white_turn) { //checking promotion format

                if (c != 'q' &&
                    c != 'b' &&
                    c != 'r' &&
                    c != 'n') { return false; }
            }
            if (!board->white_turn) {

                if (c != 'Q' &&
                    c != 'B' &&
                    c != 'R' &&
                    c != 'N') { return false; }
            }
            return true;
        }
        //Case of two words. Checks each by special function for squares
        if (!str_square_check(temp)) { return false; }
    }

    return true;
}


/*Translating ASCII to row and column number.
 * In this program since we use 1D array the result is a sum of both indexes*/
int Game::str_to_move(const string &str, Move &move) const {
    switch (str.length()) {
        case 5: {
            int column_number_origin = (((int) str[0] - 56) % 9) + 1;
            int row_number_origin = (((int) str[1] - 28) % 10 + 1) * 10;
            move.setSource(row_number_origin + column_number_origin);

            int column_number_target = (((int) str[3] - 56) % 9) + 1;
            int row_number_target = (((int) str[4] - 28) % 10 + 1) * 10;
            move.setDest(column_number_target + row_number_target);
        }
            break;
        case 7: {
            int column_number_origin = (((int) str[0] - 56) % 9) + 1;
            int row_number_origin = (((int) str[1] - 28) % 10 + 1) * 10;
            move.setSource(row_number_origin + column_number_origin);

            int column_number_target = (((int) str[3] - 56) % 9) + 1;
            int row_number_target = (((int) str[4] - 28) % 10 + 1) * 10;
            move.setDest(column_number_target + row_number_target);

            move.promoted = true;
            Piece piece(str_to_name(str[6]));
            move.setPromoted(piece);
        }
            break;
        default:
            return -99;
    }
    return -99; //fail of the program indication
}


//Spelling check - only capital letters and 1-8 number are allowed
bool Game::str_square_check(const string &str_square) const {
    if (str_square.length() != 2) { return false; }
    if ((int) str_square[0] < 65 ||   //Capital letters A - H
        (int) str_square[0] > 72 ||
        (int) str_square[1] < 49 ||  //Numbers 1 - 8
        (int) str_square[1] > 56)
        return false;
    return true;

}

/*Dictionary, using enum*/
int Game::str_to_name(const char &str_name) const{
    char c = str_name;
    switch (c) {
        case 'q' :
            return WQ;
        case 'r' :
            return WR;
        case 'b' :
            return WB;
        case 'n' :
            return WN;
        case 'Q' :
            return BQ;
        case 'R':
            return BR;
        case 'B':
            return BB;
        case 'N' :
            return BN;
        default:
            cerr << "ERROR WHILE ANALYZING PROMOTION CANDIDATE" << __FILE__ << __LINE__ << endl; //this is for debugging
            return 0;
    }

}
