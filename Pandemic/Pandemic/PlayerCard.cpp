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

