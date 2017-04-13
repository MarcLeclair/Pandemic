#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <iterator>
#include <random>
#include <queue>
#include <fstream>

#include "DeckOfCard.h"
#include "map.h"
using namespace std;

class Infection
{
private:
	vector<Infection> InfectionDeck; //the deck 
	vector<Infection> InfectionDeckDiscard; //temp deck to shuffle discarded cards
	int locationID; //the infection card's locationID

public:
	Infection();
	Infection(int); //defines Infection with an integer, being the location's ID

	int getInfectionID(); //gives the location ID of the caard drawn
	void setInfectionID(int); //sets location ID
	//void saveInfectionDeck(); //saves deck
	//void loadInfectionDeck(); //loads it

};