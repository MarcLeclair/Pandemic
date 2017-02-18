#pragma once

#include <string>
#include "DeckOfCard.h"
class Card: public DeckOfCard {


	std::string cardValue;

public:
	Card();
	Card(std::string value); 
	std::string getValue(); // return city (for player cards);
	/*Card operator!=(const Card& cardToCompare);*/
	bool isEqual(Card card2);
private:
		
};


