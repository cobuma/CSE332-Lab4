/*
Common.h
Author: Corey Marquardt b.marquardt@wustl.edu
Contains useful declarations, enums, etc. common to many
assignments for CSE 332
Contains enumeration of important indices and of possible return
values.
*/

#pragma once
#include <vector>
#include <string>

#define INFO "<GameName> <MagicSquareBoardDim> <MagicSquareInitialPiece>"

using namespace std;

enum indices { prg_name, file_name, exp_num_args, game_name = 1, dim_arg = 2, min_arg = 3, option_args1 = 3, option_args2 = 4 };
enum return_vals { success, wrong_args, got_coords, no_valid_turns, quit, bad_allocation };

int usage(const string & name, const string & info);
void tolower(string & string);