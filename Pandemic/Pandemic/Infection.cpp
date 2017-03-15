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
	for (int i = N - 1; i > 0; --i) {
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



void Infection :: infectEpidemic() {
	addDisease(InfectionDeck[48].getInfectionID());
	addDisease(InfectionDeck[48].getInfectionID());
	addDisease(InfectionDeck[48].getInfectionID());
	//move it to front

	//reshuffle up until ctr+1

	//reset ctr
}
