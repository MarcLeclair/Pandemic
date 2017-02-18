#pragma once
#include <card.h>

class PlayerCard : public Card {

	std::string cardValue;
public:
	PlayerCard(std::string value);

};
