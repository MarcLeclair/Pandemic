#include "Infection.h"

Infection::Infection() {

}

Infection::Infection(int ID) {
	locationID = ID;
}

int Infection::getInfectionID() {
	return locationID;
}

void Infection::makeDeck() {
	for (int i = 0; i < 48; i++) {
		InfectionDeck.push_back(Infection(i+1));
	}
}


void Infection::drawInfection() {
	getTopCard();
}

void Infection::shuffleInfection() {
	int N = InfectionDeck.size();
	for (int i = N - 1; i > 0; --i) {
		int r = rand() % (i + 1);
		swap(InfectionDeck[i], InfectionDeck[r]);
	}
}

void Infection::startInfect() {
	getTopCard();
}



void Infection :: infectEpidemic() {
	getBottomCard();
	for (int i; i <= toInfectDiscard.size(); i++) {
		InfectionDeck.push() = toInfectDiscard.pop;
	}
}
