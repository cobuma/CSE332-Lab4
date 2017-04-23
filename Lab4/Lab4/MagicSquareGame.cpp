/*
MagicSquareGame.cpp
Author: Corey Marquardt b.marquardt@wustl.edu
Contains function definitions related to the Nine Almonds game.
Primary methods include turn(), prompt(), and play(), as well
as helper methods like checkValid().
*/
#include "stdafx.h"
#include "Game.h"
#include "MagicSquareGame.h"
#include "Common.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

MagicSquareGame::MagicSquareGame(int dim, int min) {
	_dimension = dim;
	_min = min;
	for (size_t i = min; i < (_dimension*_dimension)+min; ++i)
	{
		available_pieces.push_back(i);
		_sum_of_pieces += i;
	}
	//  initailize pieces vector to contain only "blank" game pieces
	while (size(_pieces) < (_dimension * _dimension))
	{
		game_piece piece;
		_pieces.push_back(piece);
		//_max_disp_len = piece.display_.length();
	}
}

bool MagicSquareGame::done()
{
	bool ans = true;
	//See if all spots on the board have a piece...
	for (size_t i = 0; i < _pieces.size(); ++i)
	{
		if (_pieces[i].name_ == "") {
			return false;
		}
	}

	//Alright, so every spot is occupied.  Now we need to see if the sum along every row, column,
	//and diagonal is equal to the magic number...

	//The magic number--for a 3X3 board, this turns out to be 15
	//int magic_num = _dimension * (_dimension*_dimension + 1) / 2;
	int magic_num = _sum_of_pieces / _dimension;
	
	//std has the stoi() function to convert strings to int.  The only way for the entire program to have
	//progressed to the below calculation is if every board position has some integer piece on display.

	// Check sums along rows...
	int row_sum;
	for (size_t i = 0; i < _dimension; ++i)
	{
		row_sum = 0;
		for (size_t j = 0; j < _dimension; ++j)
		{
			row_sum += stoi(_pieces[_dimension*i + j].display_);
		}
		if (row_sum != magic_num) { return false; }
	}
	/*int sum_row1 = stoi(_pieces[0].display_) + stoi(_pieces[1].display_) + stoi(_pieces[2].display_);
	int sum_row2 = stoi(_pieces[3].display_) + stoi(_pieces[4].display_) + stoi(_pieces[5].display_);
	int sum_row3 = stoi(_pieces[6].display_) + stoi(_pieces[7].display_) + stoi(_pieces[8].display_);

	if (sum_row1 != magic_num | sum_row2 != magic_num | sum_row3 != magic_num)
	{
		return false;
	}*/

	//sum columns
	int col_sum;
	for (size_t i = 0; i < _dimension; ++i)
	{
		col_sum = 0;
		for (size_t j = 0; j < _dimension; ++j)
		{
			col_sum += stoi(_pieces[_dimension*j + i].display_);
		}
		if (col_sum != magic_num) { return false; }
	}
	/*int sum_col1 = stoi(_pieces[0].display_) + stoi(_pieces[3].display_) + stoi(_pieces[6].display_);
	int sum_col2 = stoi(_pieces[1].display_) + stoi(_pieces[4].display_) + stoi(_pieces[7].display_);
	int sum_col3 = stoi(_pieces[2].display_) + stoi(_pieces[5].display_) + stoi(_pieces[8].display_);

	if (sum_col1 != magic_num | sum_col2 != magic_num | sum_col3 != magic_num)
	{
		return false;
	}*/

	//sum diagonals
	int dg_sum = 0;
	for (size_t i = 0; i < _dimension; ++i)
	{
		dg_sum += stoi(_pieces[(_dimension + 1)*i].display_);
	}
	if (dg_sum != magic_num) { return false; }

	dg_sum = 0;
	for (size_t i = 0; i < _dimension; ++i)
	{
		dg_sum += stoi(_pieces[(_dimension - 1)*(i + 1)].display_);
	}
	if (dg_sum != magic_num) { return false; }
	/*int sum_dg1 = stoi(_pieces[0].display_) + stoi(_pieces[4].display_) + stoi(_pieces[8].display_);
	int sum_dg2 = stoi(_pieces[2].display_) + stoi(_pieces[4].display_) + stoi(_pieces[6].display_);

	if (sum_dg1 != magic_num | sum_dg2 != magic_num)
	{
		return false;
	}*/
	//for (size_t i = 0; i < _dimension; ++i)
	//{
	//	for (size_t j = 0; j < _dimension; ++j)
	//	{
	//		stoi(_pieces[i*_dimension + j].display_)
	//		//_pieces[_dimension * i + j].name_.
	//	}

	//}
 
	return true;
}

bool MagicSquareGame::stalemate()
{

	//Return false if there are still empty spots on the board
	for (size_t i = 0; i < _pieces.size(); ++i)
	{
		if (_pieces[i].name_ == "") {
			return false;
		}
	}
	//Alright, so every spot is occupied.  Now we need to see if the sum along every row, column,
	//and diagonal is equal to the magic number...

	//The magic number--for a 3X3 board, this turns out to be 15
	//int magic_num = _dimension * (_dimension*_dimension + 1) / 2;
	int magic_num = _sum_of_pieces / _dimension;

	//std has the stoi() function to convert strings to int.  The only way for the entire program to have
	//progressed to the below calculation is if every board position has some integer piece on display.

	// Check sums along rows...
	int row_sum;
	for (size_t i = 0; i < _dimension; ++i)
	{
		row_sum = 0;
		for (size_t j = 0; j < _dimension; ++j)
		{
			row_sum += stoi(_pieces[_dimension*i + j].display_);
		}
		if (row_sum != magic_num) { return true; }
	}
	/*int sum_row1 = stoi(_pieces[0].display_) + stoi(_pieces[1].display_) + stoi(_pieces[2].display_);
	int sum_row2 = stoi(_pieces[3].display_) + stoi(_pieces[4].display_) + stoi(_pieces[5].display_);
	int sum_row3 = stoi(_pieces[6].display_) + stoi(_pieces[7].display_) + stoi(_pieces[8].display_);

	if (sum_row1 != magic_num | sum_row2 != magic_num | sum_row3 != magic_num)
	{
		return true;
	}*/

	//sum columns
	int col_sum;
	for (size_t i = 0; i < _dimension; ++i)
	{
		col_sum = 0;
		for (size_t j = 0; j < _dimension; ++j)
		{
			col_sum += stoi(_pieces[_dimension*j + i].display_);
		}
		if (col_sum != magic_num) { return true; }
	}
	/*int sum_col1 = stoi(_pieces[0].display_) + stoi(_pieces[3].display_) + stoi(_pieces[6].display_);
	int sum_col2 = stoi(_pieces[1].display_) + stoi(_pieces[4].display_) + stoi(_pieces[7].display_);
	int sum_col3 = stoi(_pieces[2].display_) + stoi(_pieces[5].display_) + stoi(_pieces[8].display_);

	if (sum_col1 != magic_num | sum_col2 != magic_num | sum_col3 != magic_num)
	{
		return true;
	}*/

	//sum diagonals
	int dg_sum = 0;
	for (size_t i = 0; i < _dimension; ++i)
	{
		dg_sum += stoi(_pieces[(_dimension+1)*i].display_);
	}
	if (dg_sum != magic_num) { return true; }

	dg_sum = 0;
	for (size_t i = 0; i < _dimension; ++i)
	{
		dg_sum += stoi(_pieces[(_dimension - 1)*(i+1)].display_);
	}
	if (dg_sum != magic_num) { return true; }

	/*int sum_dg1 = stoi(_pieces[0].display_) + stoi(_pieces[4].display_) + stoi(_pieces[8].display_);
	int sum_dg2 = stoi(_pieces[2].display_) + stoi(_pieces[4].display_) + stoi(_pieces[6].display_);

	if (sum_dg1 != magic_num | sum_dg2 != magic_num)
	{
		return true;
	}*/
	//for (size_t i = 0; i < _dimension; ++i)
	//{
	//	for (size_t j = 0; j < _dimension; ++j)
	//	{
	//		stoi(_pieces[i*_dimension + j].display_)
	//		//_pieces[_dimension * i + j].name_.
	//	}

	//}
	return false;
}

bool MagicSquareGame::checkValid(unsigned int x1, unsigned int y1)
{
	if (_pieces[_dimension*y1 + x1].name_ == "integer") 
	{
		return false;
	}
	return true;
}

int MagicSquareGame::turn()
{
	ostringstream oss;
	//  continueTurn is used later on to store the user's response for continuing their turn
	string continue_turn;

	//  (x1, y1) and (x2, y2) are the begin and end points, respectivley, for the user's move
	unsigned int x1, y1;

	bool gotValidMove = false;

	//  input1 and input2 are used to tell if the user wants to quit
	unsigned int input1, input2;

	//  begin and end are used to index the _pieces vector when we check for valid moves
	unsigned int begin, end;

	//  Unless gotValidMove is true, we repeatedly ask the player to provide coordinates for a valid move
	while (!gotValidMove)
	{
		try 
		{
			prompt(input1);
		}
		catch (const exception &e)
		{
			throw e;
		}
		//prompt(input1);
		if ((input2 = GameBase::prompt(x1, y1)) == quit)
		{
			return quit;
		}

		begin = _dimension*y1 + x1;
		//end = _dimension*y2 + x2;

		//  if checkValidMove returns true, we can exit the current while loop
		gotValidMove = checkValid(x1, y1);
	}

	// Execute the valid move
	makePiece(_pieces[begin], input1);
	//makeBlank(_pieces[(begin + end) / 2]);
	//makeAlmond(_pieces[end]);
	
	//Erase the chosen piece from the list of available pieces...
	auto to_remove = remove(available_pieces.begin(), available_pieces.end(), input1);
	available_pieces.erase(to_remove, available_pieces.end());

	// Print out the updated game board and ask if player would like to continue the turn
	cout << *this << endl;

	/*oss << x1 << "," << y1 << " to " << x2 << "," << y2;
	cout << oss.str() << endl;*/
	/*cout << "\nContinue this turn (YyNn)?" << endl;
	cin >> continue_turn;
	tolower(continue_turn);*/

	// Make sure the user has provided an appropriate YyNn response
	/*while (continue_turn != "y" && continue_turn != "n")
	{
		cout << "\nContinue this turn (YyNn)?" << endl;
		cin >> continue_turn;
		tolower(continue_turn);
	}*/

	// Optionally continue the turn
	//while (continue_turn == "y")
	//{
	//	x1 = x2;
	//	y1 = y2;
	//	begin = end;
	//	gotValidMove = false;
	//	while (!gotValidMove)
	//	{
	//		input2 = prompt(x2, y2);
	//		if (input2 == quit)
	//		{
	//			return quit;
	//		}
	//		end = _dimension*y2 + x2;
	//		gotValidMove = checkValid(x1, y1, x2, y2);
	//	}

	//	// Execute the valid move
	//	makeBlank(_pieces[begin]);
	//	makeBlank(_pieces[(begin + end) / 2]);
	//	makeAlmond(_pieces[end]);

	//	// Print out the updated game board and ask if player would like to continue the turn
	//	cout << *this << endl;
	//	oss << " to " << x2 << "," << y2;
	//	cout << oss.str() << endl;
	//	cout << "\nContinue this turn (YyNn)?" << endl;
	//	cin >> continue_turn;
	//	tolower(continue_turn);

	//	while (continue_turn != "y" && continue_turn != "n")
	//	{
	//		cout << "\nContinue this turn (YyNn)?" << endl;
	//		cin >> continue_turn;
	//		tolower(continue_turn);
	//	}
	//}
	/*if (continue_turn == "n") {
		return success;
	}*/
	return success;
}

void MagicSquareGame::prompt(unsigned int & x)
{
	while (true) {
		string input;
		cout << "\nPlease input 'quit' or the value of an available piece, e.g. '5':" << endl;
		cin >> input;
		tolower(input);

		if (input == "quit")
		{
			GameBase::saveGame();
			throw exception("quit");
		}

		//replace(input.begin(), input.end(), ',', ' ');;
		istringstream iss(input);

		if (iss >> x)
		{
			/*if (x < _dimension && y_in < _dimension)
			{
				return;
			}*/
			if (find(available_pieces.begin(), available_pieces.end(), x) != available_pieces.end())
			{
				return;
			}
			/*cout << "valid coordinates fall within the range (0,0) to ("
				<< _dimension - 1 << "," << _dimension - 1 << ")" << endl;*/
		}
		cout << "!!Invalid Input!!" << endl;
		cout << "\nAvailable piece are: ";
		for (size_t i = 0; i < available_pieces.size(); ++i)
		{
			cout << available_pieces[i] << ' ';
		}
		cout << endl;
	}
}

void MagicSquareGame::makePiece(game_piece & piece, unsigned int x)
{
	piece.color_ = no_color;
	piece.display_ = to_string(x);
	piece.name_ = "integer";
}

void MagicSquareGame::print()
{
	cout << *this;
}

//I decided to print out the gameboard with extra space between the rows and columns.  I think this
//makes the board easier to read.
ostream & operator<<(ostream & out, const MagicSquareGame & game)
{
	int dim = game._dimension;
	int width = game._max_disp_len + 1;
	out << '\n';
	for (size_t i = 0; i < dim; ++i) {

		// The variable h keeps track of the height of the row of the game board we are printing.
		// The rows must be printed out in descending order.
		unsigned int h = (dim - 1) - i;
		out << '\n' << h;
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
	out << "\nX";
	for (size_t i = 0; i < dim; ++i) {
		out << setw(width)
			<< i;
	}
	out << '\n' << "Available Pieces: ";
	for (size_t i = 0; i < game.available_pieces.size(); ++i)
	{
		out << game.available_pieces[i] << ' ';
	}
	out << endl;
	//out << "X 0 1 2 3 4 " << endl;
	return out;
	// TODO: insert return statement here
}
