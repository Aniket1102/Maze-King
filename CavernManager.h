#pragma once

#include "Cavern.h"
#include "Position.h"
#include "Shape.h"

const int CAVERN_CAPACITY = 4;
class CavernManager
{
private:
	Cavern *cavern;	int cavernNumber;	bool invariant() const;	int capacity;
	void copy(const CavernManager& cavern_manager1);
	void expand();

public:
	//
	// default constructor
	//
	// Purpose:  it assigns no. of caverns to zero
	// Parameter(s):
	//  <1> parameter: N/A
	// Postcondition(s):
	//  <1> cavernNumber <= CAVERN_MAX
	// Returns: N/A
	// Side effect: N/A
	//
	CavernManager();

	//
	// isEmpty
	//
	// Purpose:  it returns true if there are no caverns and false otherwise
	// Parameter(s):
	//  <1> parameter: N/A
	// Precondition(s):
	//  <1> cavernNumber <= CAVERN_MAX
	// Returns: bool Variable
	// Side effect: N/A
	//
	bool isEmpty() const;


	//
	// getCount
	//
	// Purpose: it returns how many caverns are in the CavernManager
	// Parameter(s):
	//  <1> parameter: N/A
	// Precondition(s):
	//  <1> cavernNumber <= CAVERN_MAX
	// Returns: unsigned int variable
	// Side effect: N/A
	//
	unsigned int getCount() const;

	//
	// get
	//
	// Purpose:  it returns a constant reference to the specified Cavern. 
	// Parameter(s):
	//  <1> parameter: unsigned integer index
	// Precondition(s):
	//  <1> cavernNumber <= CAVERN_MAX
	//  <2> index >= 0;
    // Returns: Constant Cavern variable
	// Side effect: N/A
	//
	const Cavern& get(unsigned int index) const;

	//
	// getBack
	//
	// Purpose: it returns a constant reference to the Cavern that was most recently added 
	// Parameter(s):
	//  <1> parameter: N/A
	// Precondition(s):
	//  <1> cavernNumber <= CAVERN_MAX
	//  <2> !(isEmpty())
	// Returns: Constant Cavern variable
	// Side effect: N/A
	//
	const Cavern& getBack() const;

	//
	// getBackShape
	//
	// Purpose: it returns the tunnel shape for the most-recently-added cavern.
	// Parameter(s):
	//  <1> parameter: N/A
	// Precondition(s):
	//  <1> cavernNumber <= CAVERN_MAX
	//  <2> !(isEmpty())
	// Returns: Shape variable
	// Side effect: N/A
	//
	Shape getBackShape() const;

	//
	// add
	//
	// Purpose:  it inserts the specified cavern into the array and increments the cavern count
	// Parameter(s):
	//  <1> parameter: Cavern& cavern1
	// Precondition(s):
	//  <1> cavernNumber <= CAVERN_MAX
	//  <2> !(isFull())
	// Returns: N/A
	// Side effect: N/A
	//
	void add(const Cavern& cavern1);


	CavernManager(const CavernManager& cavern_manager1);
	~CavernManager();
	CavernManager& operator= (const CavernManager& cavern_manager1);
	unsigned int getCapacity() const;
};