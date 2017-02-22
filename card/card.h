#pragma once
#include <string>


class Card {


	std::string cardValue;

public:
	Card();
	Card(std::string value); 
	std::string getValue(); // return city (for player cards);
	/*Card operator!=(const Card& cardToCompare);*/
	bool isEqual(Card card2);
private:
};


	