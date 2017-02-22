#include "card.h"

Card::Card(std::string value) {
	cardValue = value;
}

Card::Card() {
	cardValue = "";
};


bool Card::isEqual(Card card2) {
	std::string valueOfCard2 = card2.getValue();
	if (valueOfCard2.compare(cardValue)) {
		return true;
	}
	else
		return false;
}

std::string Card::getValue() {
	return cardValue;
}