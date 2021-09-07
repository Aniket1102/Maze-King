//
//  Map.h
//
//  A module to represent the game map.
//

#pragma once

#include "MapSize.h"
#include "Shape.h"
#include "Position.h"




class Map
{
private:
	char processedMap[MAP_SIZE_SOUTH][MAP_SIZE_EAST];

	//
	//  getAt
	//
	//  Purpose: To return the starting_position as it is a privare variable.
	//  Parameter(s):
	//    <1> const Position position
	//  Precondition(s): N/A
	//  Returns: Shape
	//  Side Effect: N/A
	//            
	//
	Shape getAt(const Position position)const;
	Position player_starting_position;
public:
	// Default constructor
	Map();

	//
	//  printMap
	//
	//  Purpose: To print the map on screen
	//  Parameter(s): none
	//  Precondition(s):N/A
	//  Returns: N/A
	//  Side Effect: N/A
	//
	void printMap() const;

	//  isOpen
	//
	//  Purpose: To know specific position in the map is open or not.
	//  Parameter(s):
	//    <1> const Position pos
	//  Precondition(s):
	//    <1> isInMap(pos)
	//  Returns: bool
	//  Side Effect: N/A
	//
	bool isOpen(const Position& pos) const;

	//
	//  isTunnel
	//
	//  Purpose: To determine whether there is a tunnel is not
	//  Parameter(s):
	//    <1> const Position& pos
	//  Precondition(s):
	//    <1> isInMap(pos)
	//  Returns: bool Variable
	//  Side Effect: N/A
	//
	bool isTunnel(const Position& pos) const;

	//
	//  isCavern
	//
	//  Purpose: To determine whether there is a Cavern or not
	//  Parameter(s):
	//    <1> const Position pos
	//  Precondition(s):
	//    <1> isInMap(pos)
	//  Returns: bool Variable
	//  Side Effect: N/A
	//
	bool isCavern(const Position& pos) const;

	//
	//  getCavernIndex
	//
	//  Purpose: To return index of cavern found
	//  Parameter(s):
	//    <1> const Position pos
	//  Precondition(s):
	//    <1> isInMap(pos)
	//    <2> isCavern(pos)
	//  Returns: unsigned int
	//  Side Effect: N/A
	//
	unsigned int getCavernIndex(const Position& pos) const;

	//
	//  printDescription
	//
	//  Purpose: Prints the direction in which user can go
	//  Parameter(s):
	//    <1> const Position pos
	//  Precondition(s):
	//    <1> isInMap(pos)
	//    <2> not isCavern(pos)
	//  Returns: N/A
	//  Side Effect: N/A
	//
	void printDescription(const Position& pos) const;

	//
	//  setAt
	//
	//  Purpose: changes the raw map characters to appropriate shape
	//  Parameter(s):
	//    <1> const Position pos
	//    <2> const shape
	//  Precondition(s):
	//    <1> isInMap(pos)
	//  Returns: N/A
	//  Side Effect: changes raw map to processed map
	//
	void setAt(const Position& pos,Shape shape);

	//
	//  setRectangle
	//
	//  Purpose: It sets all elements of the map array in the specified area to the specified shape
	//  Parameter(s):
	//    <1> const Position pos
	//    <2> integer south_size
	//  Precondition(s):
	//    <1> south_size > 0) && (east_size > 0)
	//    <2> isInMap(pos_min, south_size, east_size) 
	//  Returns: N/A
	//  Side Effect: it sets all elements to in rectangle shape
	//
	void setRectangle(const Position& pos_min,int south_size, int east_size,Shape shape);

	//
	//  isTunnelStraight
	//
	//  Purpose: It determines if in specific position the tunnel is straight or not
	//  Parameter(s):
	//    <1> const Position pos
	//  Precondition(s):
	//    <1> (isInMap(pos)
	//  Returns: bool variable
	//  Side Effect: N/A
	//
	bool isTunnelStraight(const Position& pos) const;

	//
	//  isTunnelDirection
	//
	//  Purpose: It determines the direction in which player can go
	//  Parameter(s):
	//    <1> const Position pos
	//    <2> Direction direction 
	//  Precondition(s):
	//    <1> (isInMap(pos))
	//    <2> (direction<DIRECTION_COUNT)
	//  Returns: bool variable
	//  Side Effect: N/A
	//
	bool isTunnelDirection(const Position& pos,Direction direction) const;

	//
	//  getPlayerStart
	//
	//  Purpose: returns players starting position
	//  Parameter(s): none
	//  Precondition(s): N/A
	//  Returns: Position Variable
	//  Side Effect: N/A
	//
    Position getPlayerStart() const;

	//
	//  setPlayerStart
	//
	//  Purpose: It assigns newposition to starting position
	//  Parameter(s):
	//    <1> const Position start1
	//  Precondition(s):
	//    <1> isInMap(start1)
	//  Returns: N/A
	//  Side Effect: N/A
	//
	void setPlayerStart(const Position& start1);
};
