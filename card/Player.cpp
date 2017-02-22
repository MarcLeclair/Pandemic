#include "Player.h"

Player::Player() {

	pawn = Pawn();
	referenceCard = ReferenceCards();
}

Player::Player(std::vector<PlayerCard> playerCards) {

	currentPlayerCards = playerCards;
	pawn = Pawn();
	referenceCard = ReferenceCards();
}

bool Player::checkIfPlayerHasCard(std::string type, std::string nameOfCity) {

	for (PlayerCard card : currentPlayerCards) {
		if (type.compare(card.getType())) {
			if (nameOfCity.compare(card.getValue())) {
				return true;
			}
		}
	}
	return false;
}