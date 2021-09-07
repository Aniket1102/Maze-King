#include <iostream>
#include <cassert>

#include "Position.h"
#include "Cavern.h"
#include "CavernManager.h"


using namespace std;


CavernManager::CavernManager()
{
	capacity = CAVERN_CAPACITY;
	cavern = new Cavern[CAVERN_CAPACITY];
	assert(invariant());
}



bool CavernManager::isEmpty() const
{
	assert(invariant());

	if (cavernNumber == 0)
		return true;
	else
		return false;
}





unsigned int CavernManager::getCount() const
{
	assert(invariant());

	return cavernNumber;
}

const Cavern&  CavernManager::get(unsigned int index) const
{
	assert(invariant());

	assert(index >= 0);
	return cavern[index];
}

const Cavern&  CavernManager::getBack() const
{
	assert(invariant());

	assert(!(isEmpty()));
	return cavern[cavernNumber-1];
}

Shape CavernManager::getBackShape() const
{
	assert(invariant());
	assert(!(isEmpty()));
	return  shapeGetCavernShape(cavernNumber-1);
}

void CavernManager::add(const Cavern& cavern1)
{
	assert(invariant());
	if (cavernNumber==capacity)
	expand();
	cavern[cavernNumber] = cavern1;
	cavernNumber++;

	assert(invariant());
}



CavernManager::CavernManager(const CavernManager& cavern_manager1)
{
	copy(cavern_manager1);
	assert(invariant());
}
CavernManager::~CavernManager()
{
	assert(invariant());
	delete[] cavern;
}
CavernManager&  CavernManager::operator= (const CavernManager& cavern_manager1)
{
	if (&cavern_manager1 != this)
	{
		delete[] cavern;
		copy(cavern_manager1);
	}
	return *this;
	assert(invariant());
}

unsigned int CavernManager :: getCapacity() const
{
	assert(invariant());
	return capacity;
}

void CavernManager :: copy(const CavernManager& cavern_manager1)
{
	assert(invariant());
	cavernNumber = cavern_manager1.cavernNumber;
	capacity = cavern_manager1.capacity;
	cavern = new Cavern[capacity];
	
	for (int i = 0; i < capacity; i++)
	{
		cavern[i] = cavern_manager1.cavern[i];
	}
	assert(invariant());
}

void CavernManager:: expand()
{
	assert(invariant());
	Cavern *cavern1;
	cavern1 = new Cavern[2*capacity];

	for (int i = 0; i < capacity; i++)
	{
		cavern1[i] = cavern[i];
	}
	delete[] cavern;
	cavern = cavern1;
	capacity = capacity * 2;
	assert(invariant());
}

bool CavernManager::invariant() const
{
	if (((capacity >= CAVERN_CAPACITY)) && ((cavernNumber <= capacity)))
		return true;
	else
		return false;
}