#pragma once


struct Element
{
	unsigned int speciesNumber;
	unsigned int animalCount;
	Element *next;
};

class AnimalList
{
public:
	
    AnimalList();
	AnimalList(const AnimalList& animal_list1);
	~AnimalList();
	AnimalList& operator= (const AnimalList& animal_list1);
	void print() const;
	void add(unsigned int species_number1);
	Element * helpFun(unsigned int species_number1);

private:
	Element* head;
	Element* copyLinkedList(const Element* p_old_head) const;
	void deleteLinkedList(Element* p_list_head) const;
	bool invariant() const;
};
