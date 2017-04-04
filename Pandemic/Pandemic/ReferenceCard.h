#pragma once
#include <string>
#include <vector>
#include "PlayerCard.h"
#include "possession.h"
#include "map.h"

using namespace std;

/*************************************************************************************************************
/ Class responsible for the definition of all actions players can take
/ Base class for all role cards, which inherit and override these functions
/ For the most part, functions defined here are inherited and untouched.
**************************************************************************************************************/
class ReferenceCard
{
public:
	ReferenceCard();
	ReferenceCard(Map* mp);
	ReferenceCard(const ReferenceCard& rc);
	const ReferenceCard& operator=(const ReferenceCard& rc);
	~ReferenceCard();

	std::vector<std::string> getAllActions() {
		return allActions;
	}

	//These four functions will change the player's location to the new city, if preconditions are met
	//they will return integers based on whether they have succeeded or not
	int drive(Pawn* pawn, int newCityID);
	virtual int directFlight(Pawn* pawn, PlayerCard dest);
	virtual int charterFlight(Pawn* pawn, PlayerCard dest, int newCityID);
	virtual int shuttleFlight(Pawn* pawn, int newCityID);

	//These functions allow a player to change things on their current city, or interact with other players
	virtual int buildResearchStation(Pawn* pawn, PlayerCard currentCity);
	virtual int treatDisease(Pawn* pawn);
	virtual int shareKnowledge(Pawn* pawn, PlayerCard givingCard);
	virtual int discoverCure(Pawn* pawn, vector<PlayerCard> cure);

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




