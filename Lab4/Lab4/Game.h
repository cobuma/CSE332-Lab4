/*
Game.h
Author: Corey Marquardt b.marquardt@wustl.edu
Contains declarations for the GameBase class
*/
#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Pieces.h"
using namespace std;

enum game_properties { dimension_inputs = 3, };
enum exceptions { gameptr_not_null, insufficient_args, bad_board_dims, unexpected_args };

class GameBase {
protected:
	static shared_ptr<GameBase> game_ptr;
	unsigned int _dimension;
	int _max_disp_len;
	vector<game_piece> _pieces;
public:
	GameBase();
	int play();
	static void saveGame();
	static void setGame(int argc, char * argv[]);
	static shared_ptr<GameBase> instance();
	virtual void print() = 0;
	virtual bool done() = 0;
	virtual bool stalemate() = 0;
	virtual int turn() = 0;
	virtual int prompt(unsigned int & x_in, unsigned int & y_in);
};

string enumToString(exceptions);