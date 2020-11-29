//
// Created by misha on 29/11/2020.
//
#include <sstream>
#include "Game.h"

string  Game::get_input() {
    string test;
    getline(cin, test);
//    if(!cin) {return;}
    stringstream s(test);
    string temp;
    int nwords = 0;
    while(s >> temp) nwords++;
    if (nwords != 3) cerr << counter << ") " "Invalid input; please enter a move: " << endl;



}
