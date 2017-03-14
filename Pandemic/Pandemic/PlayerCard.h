#pragma once
#include <string>

class PlayerCard  {


	std::string cardValue, type,color;
	int id;

public:
	PlayerCard();
	PlayerCard(std::string type, int id, std::string value, std::string color);
	PlayerCard(std::string type, int id, std::string value);
	
	std::string getValue() { return cardValue; }
	
	std::string getType() { return type; } 
	
	int getCityId() { return id; }

	std::string getColour(){ return color; }
};


