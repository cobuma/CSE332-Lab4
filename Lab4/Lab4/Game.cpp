/*
Game.cpp
Author: Corey Marquardt b.marquardt@wustl.edu
Contains function definitions related to the Game Base game.
Primary methods include turn(), prompt(), and play().  Derives
*/
#include "stdafx.h"
#include "Game.h"
#include "Common.h"
#include "MagicSquareGame.h"
#include "NineAlmondGame.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <memory>
#include <algorithm>

using namespace std;

shared_ptr<GameBase> GameBase::game_ptr = nullptr;

int GameBase::play()
{
	unsigned int turn_count = 0;
	int quitResponse;
	bool isDone = false;
	bool isStalemate = false;
	print();

	while (!isDone && !isStalemate)
	{
		quitResponse = turn();

		if (quitResponse == quit)
		{
			cout << "User quit the game after " << turn_count << " turns." << endl;
			return quit;
		}

		++turn_count;

		isDone = done();
		isStalemate = stalemate();
	}

	if (isDone)
	{
		cout << "Game completed in " << turn_count << " turns." << endl;
		return success;
	}

	if (isStalemate)
	{
		cout << "Stalemate reached after " << turn_count << " turns." << endl;
		return no_valid_turns;
	}
}

void GameBase::saveGame()
{
	string input;
	cout << "Save Game (YyNn)?" << endl;
	cin >> input;
	return;
}

void GameBase::setGame(int argc, char * argv[])
{
	string almond_game = "NineAlmonds";
	string magic_square = "MagicSquare";

	if (game_ptr != nullptr) {
		/*throw exception("game pointer is not a null_ptr");*/
		throw gameptr_not_null;
	}
	if (argc < exp_num_args)
	{
		// Change to throwing an exception
		//throw exception("insufficient arguments");
		throw insufficient_args;
	}

	string passed_arg = argv[game_name];

	//Set up a Nine Almonds game, only accepts the name of the game as an argument
	if (passed_arg == almond_game && argc == exp_num_args)
	{
		//NineAlmondsGame *almondGame = new NineAlmondsGame;
		game_ptr = make_shared<NineAlmondsGame>();
		return;
	}

	//Set up a Magic Square game, according to passed arguments
	if (passed_arg == magic_square)
	{
		int default_dim = 3;
		int default_min = 1;

		if (argc == exp_num_args) {
			//Default dimension for the game is 3, starting int is 1
			//MagicSquareGame *magicSquareGame = new MagicSquareGame(default_dim, default_min);
			game_ptr = make_shared<MagicSquareGame>(default_dim, default_min);
			return;
		}

		if (argc == option_args1) {
			int dim = stoi(argv[dim_arg]);

			//Make sure the board dimension is at least 1
			if (dim < 1)
			{
				// change to exception
				//throw exception("Bad board dimensions");
				throw bad_board_dims;
			}
			//MagicSquareGame *magicSquareGame = new MagicSquareGame(dim, default_min);
			game_ptr = make_shared<MagicSquareGame>(dim, default_min);
			return;
		}
		if (argc == option_args2) {
			int dim = stoi(argv[dim_arg]);

			//Make sure the board dimension is at least 1
			if (dim < 1)
			{
				//Change to throwing exception
				throw bad_board_dims;
			}
			string min = argv[min_arg];
			//MagicSquareGame *magicSquareGame = new MagicSquareGame(dim, stoi(min));
			game_ptr = make_shared<MagicSquareGame>(dim, stoi(min));
			return;
		}
	}
	//change to exception
	throw unexpected_args;
}

shared_ptr<GameBase> GameBase::instance()
{
	if (game_ptr == nullptr) {
		throw exception("nullptr error");
	}
	return game_ptr;
}

//  Prompt the user to input valid coordinates
int GameBase::prompt(unsigned int & x_in, unsigned int & y_in)
{
	while (true) {
		string input;
		cout << "\nPlease input 'quit' or the coordinate of a valid board position \nas a comma-seperated pair, e.g. '0,0':" << endl;
		cin >> input;
		tolower(input);

		if (input == "quit")
		{
			return quit;
		}

		replace(input.begin(), input.end(), ',', ' ');
		istringstream iss(input);

		if (input.size() == dimension_inputs && iss >> x_in && iss >> y_in)
		{
			if (x_in < _dimension && y_in < _dimension)
			{
				return got_coords;
			}
			cout << "valid coordinates fall within the range (0,0) to ("
				<< _dimension - 1 << "," << _dimension - 1 << ")" << endl;
		}
		cout << "!!Invalid Input!!" << endl;
	}
}

GameBase::GameBase():_max_disp_len(2)
{
}

string enumToString(exceptions exception)
{
	switch (exception)
	{
	case gameptr_not_null:
		return "gameptr_not_null";
		break;
	case insufficient_args:
		return "insufficient_args";
		break;
	case bad_board_dims:
		return "bad_board_dims";
		break;
	case unexpected_args:
		return "unexpected_args";
		break;
	default:
		return "unsupported exception!";
	}
}
