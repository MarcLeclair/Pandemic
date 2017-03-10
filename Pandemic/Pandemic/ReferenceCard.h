/*
/ Claudia Della Serra, 26766048
/ COMP 345, Advanced Programming with C++
/
/ Assignment 1 ReferenceCard Class
*/

#pragma once
#include <string>
#include <vector>
#include "PlayerCards.h"
#include "possession.h"
#include "map.h"

/*************************************************************************************************************
/ Class responsible for the definition of all actions players can take
/ While this gives the basic functioning of actions, some functions may be overridden in RoleCard subclasses
/ For the most part, functions defined here are inherited and untouched.
**************************************************************************************************************/
class ReferenceCard
{
public:
	ReferenceCard();
	ReferenceCard(Map* mp);
	ReferenceCard(const ReferenceCard& rc);
	~ReferenceCard();

	std::vector<std::string> getAllActions() {
		return allActions;
	}

	//These four functions will change the player's location to the new city, if preconditions are met
	//they will return integers based on whether they have succeeded or not
	int drive(Pawn* pawn, int newCityID);
	virtual int directFlight(Pawn* pawn, std::vector<PlayerCard> hand, int cardIndex);
	virtual int charterFlight(Pawn* pawn, std::vector<PlayerCard> hand, int cardIndex, int newCityID);
	virtual int shuttleFlight(Pawn* pawn, int newCityID);


	virtual int buildResearchStation(Pawn* pawn, std::vector<PlayerCard> hand, int cardIndex);
	virtual int treatDisease(Pawn* pawn);
	virtual int shareKnowledge(Pawn* pawn, std::vector<PlayerCard> givingHand, std::vector<PlayerCard> receivingHand, int exchangeCard);
	virtual int discoverCure(Pawn* pawn, std::vector<PlayerCard> hand, std::vector<int> cure);

	Map* getMapRef() {
		return mapRef;
	}

private:
	std::vector<std::string> allActions = {
		"Drive/Ferry",
		"Direct Flight",
		"Charter Flight",
		"Shuttle Flight",
		"Build Research Station",
		"Treat Disease",
		"Share Knowledge",
		"Discover Cure"
	};
	Map* mapRef;
};




