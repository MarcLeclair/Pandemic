#pragma once
#include <card.h>

class PlayerCard : public Card {

	std::string cardValue,type;
	int id;
	int *arrOfConnectedCity[];
public:
	void getCardId();
	PlayerCard(std::string type, std::string value, int id, int *connectedCity[]);
	std::string getValue();
	std::string getType();
};
