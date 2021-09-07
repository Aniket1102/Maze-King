//
//  Cavern.cpp
//

#include <iostream>
#include <cassert>

#include "Direction.h"
#include "Position.h"
#include "Cavern.h"
#include "SpeciesCount.h"

using namespace std;

Cavern::Cavern(int south_size1, int east_size1)
	: south_size (south_size1),
	  east_size (east_size1)
{
	south_size = south_size1;
	east_size = east_size1;

	for (unsigned int d = 0; d < DIRECTION_COUNT; d++)
	{
		is_exit[d] = false;
		exit_position[d].south = 0;
		exit_position[d].east = 0;
	}

	assert(invariant());
}

Cavern::Cavern()
	:
	east_size(CAVERN_SIZE_MIN),
	south_size(CAVERN_SIZE_MIN),
	al()
{
	for (unsigned int d = 0; d < DIRECTION_COUNT; d++)
	{
		is_exit[d] = false;
	}
	assert(invariant());
}

int Cavern::getSouthSize()const
{
	assert(invariant());
	return south_size;
}

int Cavern:: getEastSize()const
{
	assert(invariant());
	return east_size;
}



bool Cavern:: isExit(Direction direction)const
{
	assert(invariant());
	assert(direction < DIRECTION_COUNT);
	return is_exit[direction];
}

Position Cavern:: getExitPosition(Direction direction)const
{
	assert(invariant());
	assert(direction < DIRECTION_COUNT);
	assert(isExit(direction));
	return exit_position[direction];
}

void Cavern:: addExit(Direction direction,const Position& position)
{
	assert(invariant());
	assert(direction < DIRECTION_COUNT);
	assert(!(isExit(direction)));
	is_exit[direction] = true;
	exit_position[direction] = position;
	assert(invariant());
}

void Cavern:: print()const
{
	assert(invariant());
	cout << "You are in a cavern " << east_size
		<< "0 ft by " << south_size
		<< "0 ft in size." << endl;

	if (isExit(NORTH))
		cout << "There is a tunnel leading north." << endl;
	if (isExit(SOUTH))
		cout << "There is a tunnel leading south." << endl;
	if (isExit(EAST))
		cout << "There is a tunnel leading east." << endl;
	if (isExit(WEST))
		cout << "There is a tunnel leading west." << endl;
	assert(invariant());
	cout << endl;

	al.print();
}

bool Cavern:: invariant() const
{
	if ((south_size >= CAVERN_SIZE_MIN) && (east_size >= CAVERN_SIZE_MIN))
		return true;
	else
		return false;
}

void Cavern::addAnimal(unsigned int species_number1)
{
	al.add(species_number1);
}

