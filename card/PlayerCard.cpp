#include "PlayerCard.h"


PlayerCard::PlayerCard(std::string type, std::string value, int id, int *connectedCity []){
	this->id = id;
	*arrOfConnectedCity = *connectedCity;
	cardValue = value;
	this->type = type;
};

std::string PlayerCard::getValue() {
	return cardValue;
}

std::string PlayerCard::getType() {
	return type;
}

int PlayerCard::getCardId() {
	return id;
}