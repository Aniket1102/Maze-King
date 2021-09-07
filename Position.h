//
//  Position.h
//
//  A module to represent a position on the map.
//

#pragma once

#include "Direction.h"



//
//  Position
//
//  A record to represent a position on the map.
//
struct Position
{
	int south;
	int east;
};

Position toPosition(int south, int east);
bool isInMap(const Position& position);
bool isInMap(const Position& pos_min,
	int south_size, int east_size);
Position moveDirection(const Position& position,
	Direction direction);



