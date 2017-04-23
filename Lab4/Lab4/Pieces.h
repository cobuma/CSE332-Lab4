/*
Pieces.h
Author: Corey Marquardt b.marquardt@wustl.edu
Contains declarations for enums, structs, and
methods related to game pieces
*/
#pragma once
#include <string>
using namespace std;

//  Possible colors for game pieces
enum piece_color { red, black, white, brown, invalid_color, no_color };

struct game_piece {
	game_piece();
	piece_color color_;
	string name_;
	string display_;
};

string color(piece_color color);
piece_color stringToEnum(string str);