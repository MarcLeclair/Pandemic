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

//void Infection::saveInfectionDeck() {
//	ofstream InfectionSave;
//	InfectionSave.open("InfectionDeck.txt");
//	for (int i = 0; i < InfectionDeck.size(); i++) {
//		InfectionSave << InfectionDeck[i].getInfectionID() << endl;
//	}
//	InfectionSave << ctr;
//	InfectionSave.close();
//}
//
//void Infection::loadInfectionDeck() {
//	string line;
//	int place = 0;
//	ifstream InfectionSave("InfectionDeck.txt");
//	if (InfectionSave.is_open())
//	{
//		while (getline(InfectionSave, line))			//keep going as long as there is another line
//		{
//			string s = line;
//			int ID=std::stoi(s);						 //string to int
//			InfectionDeck[place].setInfectionID(ID);
//			if (place == 49) {							//this should be the last line
//				ctr = ID;
//			}
//			place++;
//		}
//	}
//}
