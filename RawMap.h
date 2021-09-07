//
//  RawMap.h
//
//  A module to represent the game map in its raw form, as it is
//    specified in the data file.
//

#pragma once

#include <string>

#include "MapSize.h"
#include "Shape.h"
#include "Cavern.h"
#include "AnimalList.h"




void rawMapLoad(char raw[][MAP_SIZE_EAST],
	const std::string& filename);
void rawMapPrint(const char raw[][MAP_SIZE_EAST]);
bool rawMapIsOpen(const char raw[][MAP_SIZE_EAST],
	int south, int east);
bool rawMapIsCavern(const char raw[][MAP_SIZE_EAST],
	int south, int east);
int rawMapGetCavernSouthSize(const char raw[][MAP_SIZE_EAST],
	int south, int east);
int rawMapGetCavernEastSize(const char raw[][MAP_SIZE_EAST],
	int south, int east);
int rawMapFindExitToSouth(const char raw[][MAP_SIZE_EAST],
	int south, int east,
	int max_distance);
int rawMapFindExitToEast(const char raw[][MAP_SIZE_EAST],
	int south, int east,
	int max_distance);

Shape rawMapCalculateShape(const char raw[][MAP_SIZE_EAST],
	int south, int east);
Cavern rawMapCalculateCavern(const char raw[][MAP_SIZE_EAST],
	int south, int east);

Position rawMapGetPlayerStart(const char raw[][MAP_SIZE_EAST]);

bool animalCheck(const char raw[][MAP_SIZE_EAST], int south, int east);
unsigned int getSpeciesNumber(const char raw[][MAP_SIZE_EAST], int south, int east);



