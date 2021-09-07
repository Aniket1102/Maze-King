//
//  Map.cpp
//

#include <string>
#include <iostream>
#include<cassert>

#include "MapSize.h"
#include "Shape.h"
#include "Map.h"

using namespace std;


Map:: Map()
{
	setRectangle(toPosition(0,0), MAP_SIZE_SOUTH, MAP_SIZE_EAST, SHAPE_SOLID);
	player_starting_position = toPosition(0, 0);
}


Shape Map:: getAt(const Position position)const
{
	Shape shape;
	shape = processedMap[position.south][position.east];
	return shape;
}



void Map:: printMap() const
{
	for (unsigned int s = 0; s < MAP_SIZE_SOUTH; s++)
	{
		for (unsigned int e = 0; e < MAP_SIZE_EAST; e++)
		{
			cout << shapeGetMapChar(processedMap[s][e]);
		}
		cout << endl;
	}
}




bool Map::isOpen(const Position& pos)const
{
	assert(isInMap(pos));

	if (getAt(pos) != SHAPE_SOLID)
		return true;
	else
		return false;
}

bool Map:: isTunnel(const Position& pos)const
{
	assert(isInMap(pos));

	return shapeIsTunnel(processedMap[pos.south][pos.east]);
}

bool Map:: isCavern(const Position& pos)const
{
	assert(isInMap(pos));

	return shapeIsCavern(processedMap[pos.south][pos.east]);
}

unsigned int Map:: getCavernIndex(const Position& pos)const
{
	assert(isInMap(pos));
	assert(isCavern(pos));

	return shapeGetCavernIndex(processedMap[pos.south][pos.east]);
}

void Map:: printDescription(const Position& pos)const
{
	assert(isInMap(pos));
	assert(!(isCavern(pos)));

	if (isTunnel(pos))
	{
		cout << "You are in a tunnel." << endl;

		if (isTunnelStraight(pos))
			cout << "The tunnel is straight here." << endl;
		if (isTunnelDirection(pos, NORTH))
			cout << "You can go north."<<endl;
		if (isTunnelDirection(pos, SOUTH))
			cout << "You can go south."<<endl;
		if (isTunnelDirection(pos, EAST))
			cout << "You can go east."<<endl;
		if (isTunnelDirection(pos, WEST))
			cout << "You can go west."<<endl;
	}

		else
			cout << "You are in solid rock." << endl;
	
	cout << endl;
}



void Map:: setAt(const Position& pos, Shape shape)
{
	assert(isInMap(pos));

	processedMap[pos.south][pos.east] = shape;
}

void Map:: setRectangle(const Position& pos_min,int south_size, int east_size,Shape shape)
{
	assert((south_size > 0) && (east_size > 0));
	assert(isInMap(pos_min, south_size, east_size));

	for (int s = 0; s < south_size; s++)
	{
		for (int e = 0; e < east_size; e++)
		{
			processedMap[pos_min.south + s][pos_min.east + e] = shape;
		}
	}
}



bool Map :: isTunnelStraight(const Position& pos) const
{
	assert(isInMap(pos));

	if (isTunnel(pos))
		return shapeIsTunnelStraight(processedMap[pos.south][pos.east]);
	else
		return false;

}
bool Map::isTunnelDirection(const Position& pos, Direction direction) const
{
	assert((isInMap(pos))&&(direction<DIRECTION_COUNT));

	if (isTunnel(pos) == true)
		return shapeIsTunnelDirection(processedMap[pos.south][pos.east], direction);
	else
		return false;
}


Position Map:: getPlayerStart() const
{
	return player_starting_position;
}
void Map:: setPlayerStart(const Position& start1)
{
	assert(isInMap(start1));

	player_starting_position = start1;
}
