#include "PlayerCard.h"


PlayerCard::PlayerCard() {
	type = NOTHING;
	id = 0;
	cardValue = "";
}
PlayerCard::PlayerCard(cardType type, int id, std::string value, std::string color) {
	this->id = id;
	cardValue = value;
	this->type = type;
	this->color = color;
}
PlayerCard::PlayerCard(cardType type, std::string name, std::string value) { // event card constructor 
	this->name = name;
	cardValue = value;
	this->type = type;
};

PlayerCard::PlayerCard(const PlayerCard& plrcrd) {
	name = plrcrd.name;
	type = plrcrd.type;
	id = plrcrd.id;
	cardValue = plrcrd.cardValue;
	color = plrcrd.color;
}

void PlayerCard::setName(cardType type, std::string str) {
	if (type == EVENT) 
		name = str; 
	else if(type == CITY) {
		cardValue = str;
	}


};

