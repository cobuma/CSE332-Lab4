/*
MagicSquareGame.h
Author: Corey Marquardt b.marquardt@wustl.edu
Contains declarations for the MagicSquareGame class
and extraction operator.
*/
#pragma once
#include <string>
#include <vector>
#include "Pieces.h"
#include "Game.h"
using namespace std;

class MagicSquareGame : public GameBase {
	friend ostream &operator<<(ostream &out, const MagicSquareGame &game);
	vector<int> available_pieces;
	vector<game_piece> _pieces;
	int _min;
	int _sum_of_pieces;
public:
	MagicSquareGame(int dim, int min);
	virtual bool done();
	virtual bool stalemate();
	bool checkValid(unsigned int x1, unsigned int y1);
	virtual int turn();
	//virtual int prompt(unsigned int & x_in, unsigned int & y_in);
	//int getDimension();
	virtual void print();
	virtual void prompt(unsigned int &x);
	//void makeBlank(game_piece& piece);
	void makePiece(game_piece& piece, unsigned int x);
};

//  extraction operator prints out the present state of the game board
ostream &operator<< (ostream &out, const MagicSquareGame &game);
