#pragma once
#include <string>

class PlayerCard  {


	std::string cardValue, type;
	int id;

public:
	PlayerCard();
	PlayerCard(std::string type, int id, std::string value);
	std::string getValue();
	std::string getType();
	int getCityId();
};


