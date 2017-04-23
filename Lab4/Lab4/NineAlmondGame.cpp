/*
NineAlmondGame.cpp
Author: Corey Marquardt b.marquardt@wustl.edu
Contains function definitions related to the Nine Almonds game.
Primary methods include turn(), prompt(), and play(), as well
as helper methods like checkValid().
*/
#include "stdafx.h"
#include "Game.h"
#include "NineAlmondGame.h"
#include "Common.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Default constructor for NineAlmondsGame class
NineAlmondsGame::NineAlmondsGame()
{
	//  The game is played on a 5x5 board
	_dimension = 5;

	//  initailize pieces vector to contain only "blank" game pieces
	while (size(_pieces) < (_dimension * _dimension))
	{
		game_piece piece;
		_pieces.push_back(piece);
		//_max_disp_len = piece.display_.length();
	}

	//  The middle nine positions--(1,1) through (3,3)--should contain brown almond pieces, displayed with and 'A'
	int position;
	for (size_t row = 1; row < 4; ++row)
	{
		for (size_t column = 1; column < 4; ++column)
		{
			position = _dimension * row + column;
			_pieces[position].color_ = stringToEnum("brown");
			_pieces[position].display_ = "A";
			_pieces[position].name_ = "almond";
		}
		string almond = "A";
		_max_disp_len = almond.length();
	}
}

// Returns true only if there is a single piece located in the center of the board
bool NineAlmondsGame::done()
{
	bool ans = true;
	for (size_t length = 0; length < _pieces.size(); ++length)
	{
		switch (length)
		{
		case 12:
			if (_pieces[length].name_ == "")
			{
				ans = false;
			}
			break;
		default:
			if (_pieces[length].name_ == "almond")
			{
				ans = false;
			}
			break;
		}
	}
	return ans;
}

//  Stalemate should return true only if done() returns false and no valid moves remain
bool NineAlmondsGame::stalemate()
{
	unsigned int begin;
	if (done())
	{
		return false;
	}
	// if valid moves remain, return false...
	// We iterate through all board positions (x1, y1) to see if any valid moves are possible
	for (unsigned int y1 = 0; y1 < _dimension; ++y1)
	{
		for (unsigned int x1 = 0; x1 < _dimension; ++x1)
		{
			begin = _dimension * y1 + x1;

			//  As a possible start point for valid moves we consider only those positions already containing an almond
			if (_pieces[begin].display_ == "A")
			{
				//  From a possible start point, we consider all other board positions to see if a valid move is possible...
				for (unsigned int y2 = 0; y2 < _dimension; ++y2)
				{
					for (unsigned int x2 = 0; x2 < _dimension; ++x2)
					{
						if (checkValid(x1, y1, x2, y2))
						{
							return false;
						}
					}
				}
			}
		}
	}
	// By this point, we know the game is not finished, yet no valid moves remain.  We return
	// true to indicate a stalemate.
	return true;
}

//  Checks to see if a valid move may be made between two passed coordinates, (x1, y1) and (x2, y2)
bool NineAlmondsGame::checkValid(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
	//  The following variables are used to index into the _pieces vector
	unsigned int midpoint;
	unsigned int begin, end;

	// check for valid horizontal moves, where only the x coordinates differ by 2
	if ((x1 - x2 == 2 || x2 - x1 == 2) && (y1 - y2 == 0))
	{
		begin = _dimension*y1 + x1;
		end = _dimension*y2 + x2;
		midpoint = (begin + end) / 2;

		if (_pieces[begin].display_ == "A" && _pieces[midpoint].display_ == "A")
		{
			if (_pieces[end].display_ == " ")
			{
				return true;
			}
		}
	}

	//check for valid vertical moves
	if ((y1 - y2 == 2 || y2 - y1 == 2) && (x1 - x2 == 0))
	{
		begin = _dimension*y1 + x1;
		end = _dimension*y2 + x2;
		midpoint = (begin + end) / 2;

		if (_pieces[begin].display_ == "A" && _pieces[midpoint].display_ == "A")
		{
			if (_pieces[end].display_ == " ")
			{
				return true;
			}
		}
	}

	//check for valid diagonal moves 
	if ((x1 - x2 == 2 || x2 - x1 == 2) && (y1 - y2 == 2 || y2 - y1 == 2))
	{
		begin = _dimension*y1 + x1;
		end = _dimension*y2 + x2;
		midpoint = (begin + end) / 2;

		if (_pieces[begin].display_ == "A" && _pieces[midpoint].display_ == "A")
		{
			if (_pieces[end].display_ == " ")
			{
				return true;
			}
		}
	}
	return false;
}

//  Gets user input to move almonds on the game board
int NineAlmondsGame::turn()
{
	ostringstream oss;
	//  continueTurn is used later on to store the user's response for continuing their turn
	string continue_turn;

	//  (x1, y1) and (x2, y2) are the begin and end points, respectivley, for the user's move
	unsigned int x1, y1,
		x2, y2;

	bool gotValidMove = false;

	//  input1 and input2 are used to tell if the user wants to quit
	int input1, input2;

	//  begin and end are used to index the _pieces vector when we check for valid moves
	unsigned int begin, end;

	//  Unless gotValidMove is true, we repeatedly ask the player to provide coordinates for a valid move
	while (!gotValidMove)
	{
		if ((input1 = prompt(x1, y1)) == quit || (input2 = prompt(x2, y2)) == quit)
		{
			GameBase::saveGame();
			return quit;
		}

		begin = _dimension*y1 + x1;
		end = _dimension*y2 + x2;

		//  if checkValidMove returns true, we can exit the current while loop
		gotValidMove = checkValid(x1, y1, x2, y2);
	}

	// Execute the valid move
	makeBlank(_pieces[begin]);
	makeBlank(_pieces[(begin + end) / 2]);
	makeAlmond(_pieces[end]);

	// Print out the updated game board and ask if player would like to continue the turn
	cout << *this << endl;
	oss << x1 << "," << y1 << " to " << x2 << "," << y2;
	cout << oss.str() << endl;

	//End the turn if the game is successfully completed, or stalemate is reached
	if (done()) { return success; }
	if (stalemate()) { return no_valid_turns; }

	cout << "\nContinue this turn (YyNn)?" << endl;
	cin >> continue_turn;
	tolower(continue_turn);

	// Make sure the user has provided an appropriate YyNn response
	while (continue_turn != "y" && continue_turn != "n")
	{
		cout << "\nContinue this turn (YyNn)?" << endl;
		cin >> continue_turn;
		tolower(continue_turn);
	}

	// Optionally continue the turn
	while (continue_turn == "y")
	{
		x1 = x2;
		y1 = y2;
		begin = end;
		gotValidMove = false;
		while (!gotValidMove)
		{
			input2 = prompt(x2, y2);
			if (input2 == quit)
			{
				GameBase::saveGame();
				return quit;
			}
			end = _dimension*y2 + x2;
			gotValidMove = checkValid(x1, y1, x2, y2);
		}

		// Execute the valid move
		makeBlank(_pieces[begin]);
		makeBlank(_pieces[(begin + end) / 2]);
		makeAlmond(_pieces[end]);

		// Print out the updated game board and ask if player would like to continue the turn
		cout << *this << endl;
		oss << " to " << x2 << "," << y2;
		cout << oss.str() << endl;

		//End the turn if the game is successfully completed, or stalemate is reached
		if (done()) { return success; }
		if (stalemate()) { return no_valid_turns; }

		cout << "\nContinue this turn (YyNn)?" << endl;
		cin >> continue_turn;
		tolower(continue_turn);

		while (continue_turn != "y" && continue_turn != "n")
		{
			cout << "\nContinue this turn (YyNn)?" << endl;
			cin >> continue_turn;
			tolower(continue_turn);
		}
	}
	if (continue_turn == "n") {
		return success;
	}
}

int NineAlmondsGame::getDimension()
{
	return _dimension;
}

void NineAlmondsGame::print()
{
	cout << *this;
}

void NineAlmondsGame::makeBlank(game_piece& piece)
{
	piece.color_ = no_color;
	piece.display_ = " ";
	piece.name_ = "";
}

void NineAlmondsGame::makeAlmond(game_piece& piece)
{
	piece.color_ = brown;
	piece.display_ = "A";
	piece.name_ = "almond";
}

ostream & operator<<(ostream & out, const NineAlmondsGame & game)
{
	int dim = game._dimension;
	int width = game._max_disp_len + 1;
	for (size_t i = 0; i < dim; ++i) {

		// The variable h keeps track of the height of the row of the game board we are printing.
		// The rows must be printed out in descending order.
		unsigned int h = (dim - 1) - i;
		out << h;
		game_piece piece;
		// Now we print out all pieces for a given row
		for (size_t j = 0; j < dim; ++j) {
			piece = game._pieces[dim * h + j];
			out << setw(width)
				<< piece.display_;
		}

		//  Move on to printing out a new row...
		out << '\n';
	}
	out << "X";
	for (size_t i = 0; i < 5; ++i) {
		out << setw(width)
			<< i;
	}
	out << endl;
	//out << "X 0 1 2 3 4 " << endl;
	return out;
}