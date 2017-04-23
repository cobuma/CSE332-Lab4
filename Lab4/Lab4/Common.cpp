/*
Common.cpp
Author: Corey Marquardt b.marquardt@wustl.edu
Definitions for functions common to many assignments
for CSE 332
*/
#include "stdafx.h"
#include "Common.h"
#include <iostream>
#include <sstream>

int usage(const string & name, const string & info)
{
	//cout << "Error Code " << wrong_args << ": unexpected arguments" << endl;
	cout << "usage: " << name << " " << info << endl;
	return wrong_args;
}

void tolower(string & string)
{
	for (size_t i = 0; i < string.size(); ++i)
	{
		//  upper case chars are ASCII vals 65 - 90
		if ((string[i] >= 65) && (string[i] <= 90))
		{
			// converting to lower case involves adding 32 
			// to character
			string[i] = string[i] + 32;
		}
	}
}