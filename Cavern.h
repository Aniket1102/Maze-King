//
//  Cavern.h
//
//  A module to represent a rectangular cavern on the map.
//

#pragma once

#include "Direction.h"
#include "Position.h"
#include "Animallist.h"
#include "Shape.h"
#include "SpeciesCount.h"



//
//  CAVERN_SIZE_MIN
//
//  The minimum size of a cavern.  The same constant is used for
//    both dimensions.
//
const unsigned int CAVERN_SIZE_MIN = 2;
const unsigned int CAVERN_MAX = 25;



//
//  Cavern
//
//  A record to represent a rectangular cavern on the map.  A
//    cavern has two sizes: [north-]south and east[-west].
//    There are up two 4 exits, with are distinguished by the
//    direction they lead.
//

class Cavern
{
private:
	AnimalList al;
	int south_size;
	int east_size;
	

	bool is_exit[DIRECTION_COUNT];
	Position exit_position[DIRECTION_COUNT];

	bool invariant() const;
public:
	
	Cavern();
	Cavern(int south_size1, int east_size1);
	int getSouthSize() const;
	int getEastSize() const;
	bool isExit(Direction direction) const;
	Position getExitPosition(Direction direction) const;
	void addExit(Direction direction,const Position& position);
	void print() const;
	void addAnimal(unsigned int species_number1);
};


