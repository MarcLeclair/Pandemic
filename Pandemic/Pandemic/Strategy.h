/********************************************************************
/ This class is an abstract Strategy base class for the Strategy Pattern
/ Rather than having a compute() method, this class defines the interface
/ for the methods that the player can execute during his or her turn.
/ The concrete Strategies will be, firstly the RoleCard class,
/ which will implement the basic functionality of the player's actions.
/ Each specifc role will be a derived class of the RoleCard class, and will
/ change the implementation of certain functions (i.e. their special function)
/ as well as add their own functionality as well
*********************************************************************/
#pragma once

#include "possession.h"
#include "PlayerCard.h"
#include <string>

using namespace std;

class Strategy
{
public:
	Strategy();
	virtual ~Strategy();

	virtual int drive(Pawn* pawn, int newCityID) = 0;
	virtual int directFlight(Pawn* pawn, PlayerCard dest) = 0;
	virtual int charterFlight(Pawn* pawn, PlayerCard dest, int newCityID) = 0;
	virtual int shuttleFlight(Pawn* pawn, int newCityID) = 0;


	virtual int buildResearchStation(Pawn* pawn, PlayerCard currentCity) = 0;
	virtual int treatDisease(Pawn* pawn) = 0;
	virtual int shareKnowledge(Pawn* pawn, PlayerCard givingCard) = 0;
	virtual int discoverCure(Pawn* pawn, vector<PlayerCard> cure) = 0;

	virtual string getRoleColor() = 0;
	virtual string getRoleName() = 0;
	virtual string getRoleDescription() = 0;
	virtual vector<string> getSpecialActions() = 0;
};

