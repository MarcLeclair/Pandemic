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
	InfectionSave << ctr;
	InfectionSave.close();
}

void Infection::loadInfectionDeck() {
	string line;
	int place = 0;
	ifstream InfectionSave("InfectionDeck.txt");
	if (InfectionSave.is_open())
	{
		while (getline(InfectionSave, line))			//keep going as long as there is another line
		{
			string s = line;
			int ID=std::stoi(s);						 //string to int
			InfectionDeck[place].setInfectionID(ID);
			if (place == 49) {							//this should be the last line
				ctr = ID;
			}
			place++;
		}
	}
}

void Infection::endTurnInfection(Map* map) {
	int cityID = 0;
	if (epidemicVal < 4) {
		cityID = InfectionDeck[ctr].getInfectionID();
		cout << map->getCityByID(cityID).name << " has been infected." << endl;
		map->addDisease(InfectionDeck[ctr].getInfectionID());
		ctr++;
		cityID = InfectionDeck[ctr].getInfectionID();
		cout << map->getCityByID(cityID).name << " has been infected." << endl;
		map->addDisease(InfectionDeck[ctr].getInfectionID());
		ctr++;
	}
	else if (epidemicVal == 4 || epidemicVal == 5) {
		cityID = InfectionDeck[ctr].getInfectionID();
		cout << map->getCityByID(cityID).name << " has been infected." << endl;
		map->addDisease(InfectionDeck[ctr].getInfectionID());
		ctr++;
		cityID = InfectionDeck[ctr].getInfectionID();
		cout << map->getCityByID(cityID).name << " has been infected." << endl;
		map->addDisease(InfectionDeck[ctr].getInfectionID());
		ctr++;
		cityID = InfectionDeck[ctr].getInfectionID();
		cout << map->getCityByID(cityID).name << " has been infected." << endl;
		map->addDisease(InfectionDeck[ctr].getInfectionID());
		ctr++;
	}
	else if (epidemicVal > 5) {
		cityID = InfectionDeck[ctr].getInfectionID();
		cout << map->getCityByID(cityID).name << " has been infected." << endl;
		map->addDisease(InfectionDeck[ctr].getInfectionID());
		ctr++;
		cityID = InfectionDeck[ctr].getInfectionID();
		cout << map->getCityByID(cityID).name << " has been infected." << endl;
		map->addDisease(InfectionDeck[ctr].getInfectionID());
		ctr++;
		cityID = InfectionDeck[ctr].getInfectionID();
		cout << map->getCityByID(cityID).name << " has been infected." << endl;
		map->addDisease(InfectionDeck[ctr].getInfectionID());
		ctr++;
		cityID = InfectionDeck[ctr].getInfectionID();
		cout << map->getCityByID(cityID).name << " has been infected." << endl;
		map->addDisease(InfectionDeck[ctr].getInfectionID());
		ctr++;
	}


}

void Infection::shuffleInfection() {
	int N = InfectionDeck.size();
	for (int i = N - 1; i > 0; i--) {
		int r = rand() % (i + 1);
		swap(InfectionDeck[i], InfectionDeck[r]);
	}
}

void Infection::startInfect(Map* map) {
	//infect 3 cities with 3 cubes
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	int cityID = InfectionDeck[ctr].getInfectionID();
	cout  <<  map->getCityByID(cityID).name <<" has been infected." << endl;
	ctr++;

	map->addDisease(InfectionDeck[ctr].getInfectionID());
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	cityID = InfectionDeck[ctr].getInfectionID();
	cout << map->getCityByID(cityID).name << " has been infected." << endl;
	ctr++;

	map->addDisease(InfectionDeck[ctr].getInfectionID());
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	cityID = InfectionDeck[ctr].getInfectionID();
	cout << map->getCityByID(cityID).name << " has been infected." << endl;
	ctr++;

	//3 cities with 2 blocks each
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	cityID = InfectionDeck[ctr].getInfectionID();
	cout << map->getCityByID(cityID).name << " has been infected." << endl;
	ctr++;

	map->addDisease(InfectionDeck[ctr].getInfectionID());
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	cityID = InfectionDeck[ctr].getInfectionID();
	cout << map->getCityByID(cityID).name << " has been infected." << endl;
	ctr++;

	map->addDisease(InfectionDeck[ctr].getInfectionID());
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	cityID = InfectionDeck[ctr].getInfectionID();
	cout << map->getCityByID(cityID).name << " has been infected." << endl;
	ctr++;

	//3 cities with 1 block each
	map->addDisease(InfectionDeck[ctr].getInfectionID());
	cityID = InfectionDeck[ctr].getInfectionID();
	cout << map->getCityByID(cityID).name << " has been infected." << endl;
	ctr++;

	map->addDisease(InfectionDeck[ctr].getInfectionID());
	cityID = InfectionDeck[ctr].getInfectionID();
	cout << map->getCityByID(cityID).name << " has been infected." << endl;
	ctr++;

	map->addDisease(InfectionDeck[ctr].getInfectionID());
	cityID = InfectionDeck[ctr].getInfectionID();
	cout << map->getCityByID(cityID).name << " has been infected." << endl;
	ctr++;
}

void Infection :: infectEpidemic(Map* map) {
	cout << "\nOh no! An epidemic card has been drawn!" << endl;
	map->addDisease(InfectionDeck[47].getInfectionID());
	map->addDisease(InfectionDeck[47].getInfectionID());
	map->addDisease(InfectionDeck[47].getInfectionID());
	int cityID = InfectionDeck[47].getInfectionID();
	cout << map->getCityByID(cityID).name << " has been infected." << endl;
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
	cout << "Epidemic Infection finished." << endl;
}
