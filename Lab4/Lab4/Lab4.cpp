/* Lab3.cpp : Defines the entry point for the console application.
Author: Corey Marquardt b.marquardt@wustl.edu
Plays a game of either MagicSquare or NineAlmonds
*/

#include "stdafx.h"
#include "Game.h"
#include "Common.h"
#include <iostream>
#include <memory>
using namespace std;

int main(int argc, char *argv[])
{
	//Variable to store result of setGame
	//GameBase * game;

	//May throw several different exceptions
	try
	{
		GameBase::setGame(argc, argv);
	}

	catch (const exceptions& e)
	{
		cout << "Caught Exception: " << enumToString(e) << endl;
		usage(argv[prg_name], INFO);
		return e;
	}
	
	//Use a shared_ptr to delete any allocated objects
	//shared_ptr<GameBase> game_ptr(game);

	if (GameBase::instance() == 0) {
		return usage(argv[prg_name], INFO);
	}

	//play() may throw an exception if the user decides to quit
	try
	{
		return GameBase::instance()->play();
	}

	//Handle the exception thrown by quitting
	catch (const exception& e) 
	{ 
		cout << "Caught exception " << e.what() << endl;
		return quit;
	}
}

