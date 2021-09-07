//
//  RawMap.cpp
//

#include <cstdlib>  // for exit
#include <string>
#include <iostream>
#include <fstream>
#include <cassert>

#include "MapSize.h"
#include "Shape.h"
#include "RawMap.h"


using namespace std;



void rawMapLoad(char raw[][MAP_SIZE_EAST],
	const string& filename)
{
	ifstream fin(filename.c_str());

	if (!fin)
	{
		cerr << "Error: Could not open map file" << endl;
		cerr << "Aborting..." << endl;
		exit(1);
	}

	for (unsigned int s = 0; s < MAP_SIZE_SOUTH; s++)
	{
		for (unsigned int e = 0; e < MAP_SIZE_EAST; e++)
		{
			raw[s][e] = fin.get();
		}
		fin.ignore(1000, '\n');  // ignore anything else on line
	}
}

void rawMapPrint(const char raw[][MAP_SIZE_EAST])
{
	for (unsigned int s = 0; s < MAP_SIZE_SOUTH; s++)
	{
		for (unsigned int e = 0; e < MAP_SIZE_EAST; e++)
		{
			cout << raw[s][e];
		}
		cout << endl;
	}
}

bool rawMapIsOpen(const char raw[][MAP_SIZE_EAST],
	int south, int east)
{
	if (south < 0)
		return false;
	if (south >= MAP_SIZE_SOUTH)
		return false;
	if (east < 0)
		return false;
	if (east >= MAP_SIZE_EAST)
		return false;
	if (raw[south][east] == '#')
		return false;
	return true;
}

bool rawMapIsCavern(const char raw[][MAP_SIZE_EAST],
	int south, int east)
{
	if (!rawMapIsOpen(raw, south, east))
		return false;
	if (!rawMapIsOpen(raw, south, east + 1))
		return false;
	if (!rawMapIsOpen(raw, south + 1, east))
		return false;
	if (!rawMapIsOpen(raw, south + 1, east + 1))
		return false;
	return true;
}

int rawMapGetCavernSouthSize(const char raw[][MAP_SIZE_EAST],
	int south, int east)
{
	for (int s = 0; s < MAP_SIZE_SOUTH + 1; s++)  // loop ends on return below
	{
		if (!rawMapIsOpen(raw, south + s, east) ||    // check current position
			!rawMapIsOpen(raw, south + s, east + 1))  // check position to the east
		{
			return s;  // stop when you find the end of the cavern
		}
	}

	cout << "Error in rawMapGetCavernSouthSize(" << south << ", " << east
		<< "): Could not find end of cavern" << endl;
	return 0;  // should never happen
}

int rawMapGetCavernEastSize(const char raw[][MAP_SIZE_EAST],
	int south, int east)
{
	for (int e = 0; e < MAP_SIZE_EAST + 1; e++)  // loop ends on return below
	{
		if (!rawMapIsOpen(raw, south, east + e) ||  // check current position
			!rawMapIsOpen(raw, south + 1, east + e))    // check position to the south
		{
			return e;  // stop when you find the end of the cavern
		}
	}

	cout << "Error in rawMapGetCavernEastSize(" << south << ", " << east
		<< "): Could not find end of cavern" << endl;
	return 0;
}

int rawMapFindExitToSouth(const char raw[][MAP_SIZE_EAST],
	int south, int east,
	int max_distance)
{
	for (int i = 0; i < max_distance; i++)
	{
		if (rawMapIsOpen(raw, south, east + i))
			return i;
	}
	return -1;
}

int rawMapFindExitToEast(const char raw[][MAP_SIZE_EAST],
	int south, int east,
	int max_distance)
{
	for (int i = 0; i < max_distance; i++)
	{
		if (rawMapIsOpen(raw, south + i, east))
			return i;
	}
	return -1;
}



Shape rawMapCalculateShape(const char raw[][MAP_SIZE_EAST],
	int south, int east)
{
	if (!rawMapIsOpen(raw, south, east))
		return SHAPE_SOLID;

	bool is_open_north = rawMapIsOpen(raw, south - 1, east);
	bool is_open_south = rawMapIsOpen(raw, south + 1, east);
	bool is_open_east = rawMapIsOpen(raw, south, east + 1);
	bool is_open_west = rawMapIsOpen(raw, south, east - 1);

	return shapeCalculate(is_open_north,
		is_open_south,
		is_open_east,
		is_open_west);
}

Cavern rawMapCalculateCavern(const char raw[][MAP_SIZE_EAST],
	int south, int east)
{
	int south_size = rawMapGetCavernSouthSize(raw, south, east);
	int east_size = rawMapGetCavernEastSize(raw, south, east);

	Cavern cavern (south_size, east_size);

	int exit_north = rawMapFindExitToSouth(raw, south - 1, east, east_size);
	int exit_south = rawMapFindExitToSouth(raw, south + south_size, east, east_size);
	int exit_east = rawMapFindExitToEast(raw, south, east + east_size, south_size);
	int exit_west = rawMapFindExitToEast(raw, south, east - 1, south_size);

	if (exit_north != -1)
		cavern.addExit(NORTH, toPosition(south - 1, east + exit_north));
	if (exit_south != -1)
		cavern.addExit(SOUTH, toPosition(south + south_size, east + exit_south));
	if (exit_east != -1)
		cavern.addExit(EAST, toPosition(south + exit_east, east + east_size));
	if (exit_west != -1)
		cavern.addExit(WEST, toPosition(south + exit_west, east - 1));



	for (unsigned int s = south; s < (south+ south_size); s++)
	{
		for (unsigned int e = east; e < (east+east_size); e++)
		{
			if (animalCheck(raw, s, e) == true)
			{
				unsigned int Number = getSpeciesNumber(raw, s, e);
				cavern.addAnimal(Number);
			}
		}
	}
	return cavern;
}

Position rawMapGetPlayerStart(const char raw[][MAP_SIZE_EAST])
{
	for (unsigned int i = 0; i < MAP_SIZE_SOUTH; i++)
	{
		for (unsigned int j = 0; j < MAP_SIZE_EAST; j++)
		{
			if (raw[i][j] == '@')
				return toPosition(i, j);
		}
	}
	return toPosition(0, 0);
}

bool animalCheck(const char raw[][MAP_SIZE_EAST], int south, int east)
{
	if ((raw[south][east] >= 'A') && (raw[south][east] < +'A' + NO_OF_Species))
	{
		return true;
	}
	else
	{
		return false;
	}
}

unsigned int getSpeciesNumber(const char raw[][MAP_SIZE_EAST], int south, int east)
{
	assert(animalCheck(raw, south, east));
	unsigned int no = raw[south][east] - 'A';
	return no;
}
