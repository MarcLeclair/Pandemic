#pragma once
#include <card.h>
class ReferenceCards : public Card {

	std::string build,treat,share,discover; //holds value for information for player
	
public:
	ReferenceCards(); // creates a reference card
	void displayReferences(); // display references
};