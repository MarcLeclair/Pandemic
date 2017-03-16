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


void Infection::drawInfection(Map map) {
	map.addDisease(InfectionDeck[ctr].getInfectionID());
	ctr++;
}

void Infection::shuffleInfection() {
	int N = InfectionDeck.size();
	for (int i = N - 1; i > 0; i--) {
		int r = rand() % (i + 1);
		swap(InfectionDeck[i], InfectionDeck[r]);
	}
}

void Infection::startInfect(Map map) {
	map.addDisease(InfectionDeck[ctr].getInfectionID());
	map.addDisease(InfectionDeck[ctr].getInfectionID());
	map.addDisease(InfectionDeck[ctr].getInfectionID());
	ctr++;
	map.addDisease(InfectionDeck[ctr].getInfectionID());
	map.addDisease(InfectionDeck[ctr].getInfectionID());
	map.addDisease(InfectionDeck[ctr].getInfectionID());
	ctr++;
	map.addDisease(InfectionDeck[ctr].getInfectionID());
	map.addDisease(InfectionDeck[ctr].getInfectionID());
	map.addDisease(InfectionDeck[ctr].getInfectionID());
}



void Infection :: infectEpidemic(Map map) {
	map.addDisease(InfectionDeck[48].getInfectionID());
	map.addDisease(InfectionDeck[48].getInfectionID());
	map.addDisease(InfectionDeck[48].getInfectionID());
	//move it to front
	std::vector<Infection>::iterator it;
	//it = InfectionDeck.rend();
	for (int i = 0; i <= ctr+1; i++) {
		InfectionDeckDiscard.push_back(InfectionDeck[i]);
	}

	//reshuffle discard pile and put it back on top
	int N = InfectionDeckDiscard.size();
	for (int i = N - 1; i > 0; i--) {
		int r = rand() % (i + 1);
		swap(InfectionDeckDiscard[i], InfectionDeckDiscard[r]);
	}

	for (int i = 0; i <= ctr + 1; i++) {
		InfectionDeck[i] = InfectionDeckDiscard[i];
	}

	//reset ctr
	ctr = 0;
}
