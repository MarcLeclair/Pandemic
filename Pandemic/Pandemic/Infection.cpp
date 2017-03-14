#include "Infection.h"
#include "map.h"
#include "DeckOfCard.h"

Infection::Infection() {

}

DeckOfCard<Infection> InfectionDeck = new DeckOfCard(toInfect);

void Infection::startInfect() {

}


void Infection::shuffleInfection() {
	InfectionDeck.shuffleDeck;
}

void Infection::drawInfection() {
	getTopCard();
}