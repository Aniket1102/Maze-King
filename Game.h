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

	bool invariant() const;
	void printDescription() const;
	void move(Direction direction);
	void makeFirstMove(Direction direction);
	void followTunnel(Direction direction);
};