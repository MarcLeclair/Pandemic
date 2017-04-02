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
	int epidemicVal; // the value of the infection rate on the map to see how many infection cards are drawn
	int ctr = 0; //keeps place in the deck

public:
	Infection();
	Infection(int); //defines Infection with an integer, being the location's ID
	void endTurnInfection(Map*); //draws a single infection card and adds respective amount of cubes
	void startInfect(Map*); //beginning 9 card draws for board start state
	void infectEpidemic(Map*); //infection cards if epidemic card drawn
	void makeDeck(); //instantiates vector with 48 IDs
	int getInfectionID(); //gives the location ID of the caard drawn
	void setInfectionID(int); //sets location ID
	void saveInfectionDeck(); //saves deck
	void loadInfectionDeck(); //loads it

	/*void startInfect() {
	int counter = 0;
	while (counter < 3) {
	getLocation(roll (0,2));
	if (getCubes() == 0) {
	cubes += 3;
	counter++;
	}
	counter++; //just to break for demo purposes
	}
	while (counter < 6) {
	getLocation(roll(0,2));
	cubes = 2;
	counter++;
	}
	while(counter < 9) {
	getLocation(roll(0,2));
	cubes = 1;
	counter++;
	}*/
};