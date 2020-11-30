//
// Created by misha on 29/11/2020.
//
#include <sstream>
#include "Game.h"
#include <string.h>

using namespace std;

void Game::game_loop() {

    board->init();
    cout << *board;

    string str_move;
    while (true) {
        if (board->ins_material || board->mate_to_black || board->mate_to_white || board->stalemate)
            return;
        cout << num_turn << ") ";
        board->white_turn ? cout << "White's turn, please enter a move: \n" : cout
                << "Black's turn, please enter a move: \n";
        err: getline(cin, str_move);
        if (!cin) { return; }
        if (valid_option(str_move)) {
            Move move;
            str_to_move(str_move, move);
            if (!board->make_move(move))
            {
                cerr << num_turn << "Illegal move; please enter a move:" << endl;
                goto err;
            }
            else {
                num_turn++;
                cout << *board;
                continue;
            }
        } else {
            cerr << num_turn << ") " << "Invalid input; please enter a move:" << endl;
            goto err;
        }
    }

}

bool Game::valid_option(string str) {
    int word_counter = 0;
    string temp;
    stringstream s(str);
    while (s >> temp) { word_counter++; }
    if (word_counter < 2 || word_counter > 3 || (board->promotion && word_counter != 3))
        return false;

    word_counter = 0;
    s.str("");
    s << str;

    while (s >> temp) {
        word_counter++;
        if (word_counter == 3) { //promotion
            if (!board->promotion) { return false; }
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

        if (!str_square_check(temp)) { return false; }
    }

    return true;
}

int Game::str_to_move(const string &str, Move &move) const {
    switch (str.length()) {
        case 5: {
            int column_number_origin = (((int) str[0] - 56) % 9) + 1;
            int row_number_origin = (((int) str[1] - 28) % 10 + 1) * 10; //TODO Find a better formula XD
            move.setSource(row_number_origin + column_number_origin);

            int column_number_target = (((int) str[3] - 56) % 9) + 1;
            int row_number_target = (((int) str[4] - 28) % 10 + 1) * 10;
            move.setDest(column_number_target + row_number_target);
        }

            break;
        case 7: {
            int column_number_origin = (((int) str[0] - 56) % 9) + 1;
            int row_number_origin = (((int) str[1] - 28) % 10 + 1) * 10; //TODO Find a better formula XD
            move.setDest(row_number_origin + column_number_origin);

            int column_number_target = (((int) str[3] - 56) % 9) + 1;
            int row_number_target = (((int) str[4] - 28) % 10 + 1) * 10;
            move.setDest(column_number_target + row_number_target);

            move.promoted = true;
            move.setPromoted(str_to_name(str[6]));


        }
            break;
    }
}

bool Game::str_square_check(const string &str_square) const {
    if (str_square.length() != 2) { return false; }
    if (str_square[0] < 65 ||   //Capital letters A - H
        str_square[0] > 72 ||
        (int) str_square[1] < 49 ||  //Numbers 1 - 8
        (int) str_square[1] > 56)
        return false;
    return true;

}

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
            cerr<<"ERROR WHILE ANALYZING PROMOTION CANDIDATE"<< __FILE__<<__LINE__<<endl; //TODO erase whenever after

    }
    return 0;
}
