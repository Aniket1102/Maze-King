#include <iostream>
#include <cassert>

#include "AnimalList.h"
#include "SpeciesCount.h"

using namespace std;
AnimalList::AnimalList()
{
	head = NULL;
	assert(invariant());
}

void AnimalList:: deleteLinkedList(Element* p_list_head) const
{
	assert(invariant());
	if (p_list_head != NULL)
	{
		Element *pCurrent = NULL;
		Element *pNext = p_list_head;

		while (pNext != NULL)
		{
			pCurrent = pNext;
			pNext = pCurrent->next;
			delete pCurrent;
		}

	}
}

AnimalList:: ~AnimalList()
{
	assert(invariant());
	deleteLinkedList(head);
}

Element* AnimalList::copyLinkedList(const Element* p_old_head) const
{
	assert(invariant());
	if (p_old_head == NULL)
		return NULL;

	// The head has to be handled seperately
	Element *pNewHead = new Element;

	pNewHead->speciesNumber = p_old_head->speciesNumber;
	pNewHead->animalCount = p_old_head->animalCount;

	// Copy the rest of the linked list
	Element *pNewPrev = pNewHead;
	const Element *pOldPrev = p_old_head;
	while (pOldPrev->next != NULL)  // still Nodes to copy
	{
		// make a new Node for our copy linked list
		pNewPrev->next = new Element;

		// advance both linked lists 1 position
		pNewPrev = pNewPrev->next;
		pOldPrev = pOldPrev->next;

		// copy the data
		pNewPrev->speciesNumber = pOldPrev->speciesNumber;
		pNewPrev->animalCount = pOldPrev->animalCount;

	}

	// set the end of the new linked list to nullptr
	pNewPrev->next = NULL;

	return pNewHead;
}

AnimalList :: AnimalList(const AnimalList& animal_list1)
{
	copyLinkedList(head);

}

AnimalList&  AnimalList :: operator= (const AnimalList& animal_list1)
{
	if (&animal_list1 != this)
	{
		deleteLinkedList(head);
		copyLinkedList(head);
	}
	return *this;
	assert(invariant());
}

void AnimalList::print() const
{
	assert(invariant());
	
	Element *p=head;

	while (p != NULL)
	{
		if (p->animalCount == 1)
		{
			cout << "There is a " << animalColony[p->animalCount][30] << " here" << endl;
		}
		else 
			cout<< "There are "<< p->animalCount <<" "<<animalColony[p->animalCount][30] << " here" << endl;
		p = p->next;
	}
}

void AnimalList :: add(unsigned int species_number1)
{
	assert(invariant());
	for (Element* p = head; p != NULL; p = p->next)
	{
		if (species_number1 == p->speciesNumber)
		{
			p->animalCount++;

			return;
		}
	}
	Element* newElement = new Element;
	newElement->speciesNumber = species_number1;
	newElement->animalCount = 1;

	if (helpFun(species_number1) == NULL)
	{
		newElement->next = head;
		head = newElement;
	}

	else
	{
		newElement->next=helpFun(species_number1)->next;
		helpFun(species_number1)->next = newElement;
	}
	assert(invariant());
}

Element * AnimalList::helpFun(unsigned int species_number1)
{
	Element* prevPtr = NULL;
	Element* currPtr = head;
	while (currPtr != NULL && currPtr->speciesNumber < species_number1)
	{
		prevPtr = currPtr;
		currPtr = currPtr->next;
	}
	return prevPtr;
}

bool AnimalList::invariant() const{	for (Element* p = head; p != NULL; p = p->next)
	{
		if (p->animalCount <1 && p->speciesNumber>= NO_OF_Species)
		{
			p->animalCount++;

			return false;
		}
	}	return true;}