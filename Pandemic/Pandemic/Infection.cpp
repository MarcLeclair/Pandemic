#include "Infection.h"
#include "map.h"
#include "DeckOfCard.h"

Infection::Infection() {

}

DeckOfCard<Infection> InfectionDeck = new DeckOfCard(toInfect);

void Infection::startInfect() {
	getTopCard();
}


void Infection::shuffleInfection() {
	InfectionDeck.shuffleDeck;
}

void Infection::drawInfection() {
	getTopCard();
}

void Infection :: infectEpidemic() {
	getBottomCard();
	for (int i; i <= toInfectDiscard.size(); i++) {
		InfectionDeck.push() = toInfectDiscard.pop;
	}
}