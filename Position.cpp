//
//  Position.cpp
//

#include "MapSize.h"
#include "Direction.h"
#include "Position.h"



Position toPosition(int south, int east)
{
	Position position;
	position.south = south;
	position.east = east;
	return position;
}

bool isInMap(const Position& position)
{
	if (position.south <  0)
		return false;
	if (position.south >= MAP_SIZE_SOUTH)
		return false;
	if (position.east  <  0)
		return false;
	if (position.east >= MAP_SIZE_EAST)
		return false;
	return true;
}

bool isInMap(const Position& pos_min,
	int south_size, int east_size)
{
	if (pos_min.south < 0)
		return false;
	if (pos_min.south + south_size > MAP_SIZE_SOUTH)
		return false;
	if (pos_min.east  < 0)
		return false;
	if (pos_min.east + east_size  > MAP_SIZE_EAST)
		return false;
	return true;
}

Position moveDirection(const Position& position,
	Direction direction)
{
	Position moved = position;

	switch (direction)
	{
	case NORTH:
		moved.south--;
		break;
	case SOUTH:
		moved.south++;
		break;
	case EAST:
		moved.east++;
		break;
	case WEST:
		moved.east--;
		break;
	}

	return moved;
}
