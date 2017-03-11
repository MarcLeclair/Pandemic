#include "PlayerCards.h"


PlayerCard::PlayerCard() {
	type = "";
	id = 0;
	cardValue = "";
}
PlayerCard::PlayerCard(std::string type, int id, std::string value, std::string color) {
	this->id = id;
	cardValue = value;
	this->type = type;
	this->color = color;
}
PlayerCard::PlayerCard(std::string type, int id, std::string value) { // event card constructor 
	this->id = id;
	cardValue = value;
	this->type = type;
};

std::string PlayerCard::getValue() {
	return cardValue;
}

std::string PlayerCard::getType() {
	return type;
}

int PlayerCard::getCityId() {
	return id;
}
