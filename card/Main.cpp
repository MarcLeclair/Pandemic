#include "DeckOfCard.h"
#include "PlayerCard.h"
#include "ReferenceCards.h"
#include "Player.h"
#include <fstream>
using namespace std;

int main() {

	size_t pos = 0;
	string tempParse = ",";
	string cityInfo, tempString;
	vector<string> tempInfo;

	fstream citiesFile("locations.txt");
	if (citiesFile.is_open()) {
		while (citiesFile.good()) {
			
			getline(citiesFile, cityInfo);

			while ((pos = cityInfo.find(tempParse) != string::npos)) {
				tempString = cityInfo.substr(0, pos);
				cityInfo.erase(0, pos + tempParse.length());
				tempInfo.push_back(tempString);
			}
		}
	}

	cout << "Instantiating Deck of  Cities" << endl;
	
	for (string str : tempInfo) {
		cout << str << endl;
	}
}