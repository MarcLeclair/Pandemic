#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <iterator>
#include <random>
#include <queue>

#include "DeckOfCard.h"
#include "map.h"
using namespace std;

class Infection
{
private:
	vector<Infection> InfectionDeck;
	vector<Infection> InfectionDeckDiscard;
	int locationID;
	int ctr = 0;

public:
	Infection();
	Infection(int); //defines Infection with an integer, being the location's ID
	void endTurnInfection(Map); //draws a single infection card and adds respective amount of cubes
	void shuffleInfection(); //shuffles the infection deck
	void startInfect(Map); //beginning 9 card draws for board start state
	void infectEpidemic(Map); //infection cards if epidemic card drawn
	void makeDeck(); //instantiates vector with 48 IDs
	int getInfectionID(); //gives the location ID of the caard drawn

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