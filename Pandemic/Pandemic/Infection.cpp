#include "Infection.h"

Infection::Infection() {

}

Infection::Infection(int ID) {
	locationID = ID;
}

int Infection::getInfectionID() {
	return locationID;
}

void Infection::setInfectionID(int ID) {
	locationID = ID;
}

void Infection::makeDeck() {
	for (int i = 0; i < 48; i++) {
		InfectionDeck.push_back(Infection(i+1));
	}
}

void Infection::saveInfectionDeck() {
	ofstream InfectionSave;
	InfectionSave.open("InfectionDeck.txt");
	for (int i = 0; i < InfectionDeck.size(); i++) {
		InfectionSave << InfectionDeck[i].getInfectionID() << endl;
	}
	InfectionSave.close();
}

void Infection::loadInfectionDeck() {
	string line;
	ifstream mapFile("InfectionDeck.txt");
	if (mapFile.is_open())
	{
		while (getline(mapFile, line))
		{

}

void Infection::endTurnInfection(Map* map) {
	if (epidemicVal < 4) {
		map->addDisease(InfectionDeck[ctr].getInfectionID());
		map->addDisease(InfectionDeck[ctr].getInfectionID());
	}
	else if (epidemicVal == 4 || epidemicVal == 5) {
		map->addDisease(InfectionDeck[ctr].getInfectionID());
		map->addDisease(InfectionDeck[ctr].getInfectionID());
		map->addDisease(InfectionDeck[ctr].getInfectionID());
	}
	else if (epidemicVal > 5) {
		map->addDisease(InfectionDeck[ctr].getInfectionID());
		map->addDisease(InfectionDeck[ctr].getInfectionID());
		map->addDisease(InfectionDeck[ctr].getInfectionID());
		map->addDisease(InfectionDeck[ctr].getInfectionID());
	}
	ctr++;
}

void Infection::shuffleInfection() {
	int N = InfectionDeck.size();
	for (int i = N - 1; i > 0; i--) {
		int r = rand() % (i + 1);
		swap(InfectionDeck[i], InfectionDeck[r]);
	}
}

void Infection::startInfect(Map* map) {
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	cout << City[ctr].name() << " has been infected." << endl;
	ctr++;
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	ctr++;
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	ctr++;
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	ctr++;
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	ctr++;
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	ctr++;
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	ctr++;
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	ctr++;
	map->addDisease(InfectionDeck[ctr].getInfectionID());
}

void Infection :: infectEpidemic(Map* map) {
	map->addDisease(InfectionDeck[48].getInfectionID());
	map->addDisease(InfectionDeck[48].getInfectionID());
	map->addDisease(InfectionDeck[48].getInfectionID());
	//move it to front
	std::vector<Infection>::iterator it;
	//it = vector<InfectionDeck>.rend();
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

	//increase epidemic value
	epidemicVal++;
}
