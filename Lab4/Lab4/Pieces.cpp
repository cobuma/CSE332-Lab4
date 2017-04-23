/*
Pieces.cpp
Author: Corey Marquardt b.marquardt@wustl.edu
Contains function definitions related to the game pieces.
Methods include a default constructor for game_piece struct.
color() converts a enum type for the name of a color to a string.
stringToEnum() takes in a string and returns an enum type corresponding
to the color specified by the string.
*/
#include "stdafx.h"
#include "Common.h"
#include "Pieces.h"

//  Default constuctor: new gamepieces are colorless, nameless, and display a blank
game_piece::game_piece()
	: color_(no_color), name_(""), display_(" ") {}

//  Returns a lower case string corresponding to the passed color
string color(piece_color color)
{
	switch (color)
	{
	case red:
		return "red";
		break;
	case black:
		return "black";
		break;
	case white:
		return "white";
		break;
	case brown:
		return "brown";
		break;
	case invalid_color:
		return "invalid color";
		break;
	case no_color:
		return "no color";
		break;
	default:
		break;
	}
}

//  From an input string, returns corresponding element of enum type
piece_color stringToEnum(string str) {
	tolower(str);
	if (str == "red")
	{
		return piece_color::red;
	}
	else if (str == "black")
	{
		return piece_color::black;
	}
	else if (str == "white")
	{
		return piece_color::white;
	}
	else if (str == "brown")
	{
		return piece_color::brown;
	}
	//  blanks and tabs are considered colorless
	else if (str == " " || str == "\t")
	{
		return piece_color::no_color;
	}
	else
	{
		return piece_color::invalid_color;
	}
}