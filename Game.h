#pragma once

#include "MapSize.h"
#include "Direction.h"
#include "Shape.h"
#include "RawMap.h"
#include "Map.h"
#include "Cavern.h"
#include "Position.h"
#include "CavernManager.h"

class Game
{
private:
	Map map;
	Position playerPosition;
	CavernManager cm;

	bool invariant() const;public:	Game(const std::string& filename);
	void printDescription() const;
	void move(Direction direction);	bool canMakeFirstMove(Direction direction) const;
	void makeFirstMove(Direction direction);
	void followTunnel(Direction direction);
};