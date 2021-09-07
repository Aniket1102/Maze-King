//
//  Main.cpp
//
//  CS 115 Assignment 
//
//

#include <string>
#include <iostream>
#include <fstream>


#include "Direction.h"
#include "Game.h"

using namespace std;



int main()
{
	char newPosition;
	
	Game game("map5.txt");
	

	do
	{ 
		game.printDescription();
		cout <<"Next?";
		cin >> newPosition;
		
		switch (newPosition)
		{
		case 'n':
			game.move(NORTH);
			break;
		case 's':
			game.move(SOUTH);
			break;
		case 'e':
			game.move(EAST);
			break;
		case 'w':
			game.move(WEST);
			break;

		default:
			cout << " " << endl;
		}
	}
	while (newPosition != 'q');
	
	// wait for user to confirm quit

	cout << "Press [ENTER] to continue...";
	string dummy;
	getline(cin, dummy);

	return 0;
}
