#include <iostream>
#include <fstream>
#include <cassert>

#include "MapSize.h"
#include "Direction.h"
#include "Shape.h"
#include "RawMap.h"
#include "Map.h"
#include "Cavern.h"
#include "Position.h" 
#include "Game.h"

using namespace std;

Game::Game(const  std::string& filename)
{
	char raw[MAP_SIZE_SOUTH][MAP_SIZE_EAST];
	rawMapLoad(raw, filename);
	rawMapPrint(raw);
	cout << endl;

	playerPosition = toPosition(0, 0);
	map.setPlayerStart(rawMapGetPlayerStart(raw));
	playerPosition = map.getPlayerStart();
		
	for (unsigned int s = 0; s < MAP_SIZE_SOUTH; s++)
	{
		for (unsigned int e = 0; e < MAP_SIZE_EAST; e++)
		{
			
			if (!map.isCavern(toPosition(s, e)))
			{
				if (!rawMapIsCavern(raw, s, e))
				{



					Shape shape = rawMapCalculateShape(raw, s, e);
					map.setAt(toPosition(s, e), shape);
				}
				else
				{
					
					cm.add(rawMapCalculateCavern(raw, s, e));
					
					Cavern c = cm.getBack();
					
					int   south_size = c.getSouthSize();
					int   east_size = c.getEastSize();
					Shape cavern_shape = cm.getBackShape();
				
					map.setRectangle(toPosition(s, e), south_size, east_size, cavern_shape);
					
				}
			}
		}
	}


	map.printMap();
	assert(invariant());
	
}

void Game::printDescription() const
{
	assert(invariant());

	if (isInMap(playerPosition))
	{
		if (map.isCavern(playerPosition))
		{
			unsigned int cavern_index = map.getCavernIndex(playerPosition);
			Cavern c = cm.get(cavern_index);
			c.print();
		}
		else
		{
			map.printDescription(playerPosition);
		}
	}
	else
	{
		cout << "You are somewhere outside the map." << endl;
		cout << endl;
	}

}

void Game::move(Direction direction)
{
	assert(invariant());
	assert(direction >= 0);
	if (!(canMakeFirstMove(direction)))
	{
		cout<< "There is no way to go in that direction." << endl;
	}
	else
	{
			makeFirstMove(direction);
			followTunnel(direction);
	}
	assert(invariant());
}



bool Game::canMakeFirstMove(Direction direction) const
{
	assert(invariant());
	assert(direction >= 0);

	int index;
	if (map.isCavern(playerPosition))
	{
		index = map.getCavernIndex(playerPosition);
		Cavern cavern = cm.get(index);
		if (cavern.isExit(direction))
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	else
	{
		if (map.isTunnelDirection(playerPosition, direction))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
	
	void Game::makeFirstMove(Direction direction)
	{
		assert(invariant());
		assert(direction >= 0);

		int index;
		if (map.isCavern(playerPosition))
		{
			index = map.getCavernIndex(playerPosition);
			Cavern cavern = cm.get(index);
			playerPosition = cavern.getExitPosition(direction);
			cout << "You leave the cavern and start walking..." << endl;
		}
		else
		{
			playerPosition=moveDirection(playerPosition,direction);
			cout << "You start walking..." << endl;
		}
		assert(invariant());
	}

	void Game::followTunnel(Direction direction)
	{
		assert(invariant());
		assert(direction >= 0);

		cout << "10 ft..." << endl;
		int i = 0;
		while (map.isTunnelStraight(playerPosition))
		{
			playerPosition = moveDirection(playerPosition, direction);
			cout << (i + 2) << "0 ft..." << endl;
			i++;
		}
		assert(invariant());
	}



   
	bool Game::invariant() const
	{
		if ((isInMap(playerPosition)) && (map.isOpen(playerPosition)))
			return true;
		else
			return false;
	}