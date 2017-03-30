#pragma once

#include <string>

class PlayerCard  {



public:

	 enum cardType
	{ 
		 EVENT, 
		 CITY, 
		 EPIDEMIC,
		 NOTHING
	 };
	 inline const char* ToString(cardType v)
	 {
		 switch (v)
		 {
		 case EVENT:   return "event";
		 case CITY:   return "city";
		 case EPIDEMIC: return "epidemic";
		 case NOTHING: return "nothing";
		 default:      return "error: no card type";
		 }
	 }
	PlayerCard();
	PlayerCard(cardType type, int id, std::string value, std::string color);
	PlayerCard(cardType type, std::string name, std::string value);
	
	std::string getValue() { return cardValue; }
	
	std::string getType() { return ToString(this->type); } 
	
	int getCityId() { return id; }

	std::string getColour(){ return color; }

	private:
		cardType type;

		std::string name, cardValue, color;
		int id;


};


