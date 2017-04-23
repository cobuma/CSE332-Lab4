/*
NineAlmondGame.h
Author: Corey Marquardt b.marquardt@wustl.edu
Contains declarations for the NineAlmonds class
and extraction operator.
*/
#pragma once
#include <string>
#include <vector>
#include "Pieces.h"
#include "Game.h"
using namespace std;

class NineAlmondsGame : public GameBase {
	friend ostream &operator<< (ostream &out, const NineAlmondsGame &game);
public:
	NineAlmondsGame();
	virtual bool done();
	virtual bool stalemate();
	bool checkValid(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
	virtual int turn();
	//virtual int prompt(unsigned int & x_in, unsigned int & y_in);
	int getDimension();
	virtual void print();
	void makeBlank(game_piece& piece);
	void makeAlmond(game_piece& piece);
};

//  extraction operator prints out the present state of the game board
ostream &operator<< (ostream &out, const NineAlmondsGame &game);