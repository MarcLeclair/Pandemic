
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "PlayerCard.h"
#include "ReferenceCard.h"
#include "map.h"
#include "Strategy.h"

using namespace std;

/************************************************************************************************************************************************************************
/ RoleCard class, base class for all roles
/ This will allow all types of role cards to be held in the same data structure for initial distribution
/ Also allows for the abstraction of the role cards players can hold (i.e. they can hold a generic RoleCard pointer, but through polymorphism perform specific role tasks)
**************************************************************************************************************************************************************************/
class RoleCard : public Strategy
{
public:
	RoleCard(Map* mp);
	RoleCard(const RoleCard& rolec);
	~RoleCard();
	const RoleCard& operator=(const RoleCard& rc);

	//These four functions will change the player's location to the new city, if preconditions are met
	//they will return integers based on whether they have succeeded or not
	int drive(Pawn* pawn, int newCityID);
	virtual int directFlight(Pawn* pawn, PlayerCard dest);
	virtual int charterFlight(Pawn* pawn, PlayerCard dest, int newCityID);
	virtual int shuttleFlight(Pawn* pawn, int newCityID);


	virtual int buildResearchStation(Pawn* pawn, PlayerCard currentCity);
	virtual int treatDisease(Pawn* pawn);
	virtual int shareKnowledge(Pawn* pawn, PlayerCard givingCard);
	virtual int discoverCure(Pawn* pawn, vector<PlayerCard> cure);


	Map* getMapRef() {
		return mapRef;
	}

	string RoleCard::getRoleName() {
		return roleName;
	}

	string RoleCard::getRoleColor() {
		return roleColor;
	}

	vector<string> getSpecialActions() {
		return specialActions;
	}

	string getRoleDescription() {
		return roleDescription;
	}

	void RoleCard::setRoleName(string name) {
		roleName = name;
	}

	void RoleCard::setRoleColor(string color) {
		roleColor = color;
	}

	void addSpecialAction(string sp) {
		specialActions.push_back(sp);
	}

	void setRoleDescription(string desc) {
		roleDescription = desc;
	}

private:
	string roleName;
	string roleColor;
	string roleDescription;
	vector<string> specialActions;
	Map* mapRef;
};


/*******************************************************************************************************************************
/ Researcher Role Card Specifications:
/	You may give any 1 of your City cards when you share knowledge. It need not match your city.
/	A player who shares knowledge with you on their turn can take any 1 of your city cards.
********************************************************************************************************************************/
class Researcher :
	public RoleCard
{
public:
	Researcher(Map* mp);
	Researcher(const Researcher& res);
	virtual ~Researcher();
	virtual int shareKnowledge(Pawn* giverPawn, PlayerCard givingCard);
};



/*********************************************************************************************************************************************************
/ Medic Role Card Specifications:
/	Remove ALL cubes of one color when doing Treat Disease.
/	Automatically remove cubes of cured diseases from the city you are in (and prevent them from being placed there)
**********************************************************************************************************************************************************/
class Medic :
	public RoleCard
{
public:
	Medic(Map* mp);
	Medic (const Medic& med);
	virtual ~Medic();
	virtual int treatDisease(Pawn* pawn);
};

/****************************************************************************************************
/ Operations Expert Role Card Specifications:
/	As an action, build a research station in the city you are in (no city card needed)
/	Once per turn, as an action, move from a research station to any city by discarding any City card
*****************************************************************************************************/
class OperationsExpert : public RoleCard
{
	//Special boolean for the operations expert to keep track of if his action was used
	bool specialUsedThisTurn = false;
public:
	OperationsExpert(Map* mp);
	OperationsExpert(const OperationsExpert &ops);
	virtual ~OperationsExpert();
	virtual int buildResearchStation(Pawn* pawn, PlayerCard currentCity);
	int specialOperationsMove(Pawn* pawn, PlayerCard moveCard);

	void specialWasUsed() {	specialUsedThisTurn = true;	}

	void resetSpecialUsed() {	specialUsedThisTurn = false;}
};


/****************************************************************************************************
/ Scientist Role Card Specifications:
/	You only need 4 cards of the same color to do the Discover a Cure action
*****************************************************************************************************/
class Scientist :
	public RoleCard
{
public:
	Scientist(Map* mp);
	Scientist(const Scientist& sci);
	virtual ~Scientist();
	virtual int discoverCure(Pawn* pawn, vector<PlayerCard> cure);
};

/****************************************************************************************************
/Contingency Planner Role Card Specifications:
/	As an action, take any discarded event card and store it on this card
/	When you play the stored even card, remove it from the game.
/	Limit: 1 event card on this card at a time, which is not part of your hand
*****************************************************************************************************/
class ContingencyPlanner :
	public RoleCard
{
public:
	ContingencyPlanner(Map* mp);
	ContingencyPlanner(const ContingencyPlanner& cp);
	virtual ~ContingencyPlanner();
	int pickUpSpecialEvent(PlayerCard* sp);
	void discardSpecialEvent();
private:
	PlayerCard* specialEvent;
};

/****************************************************************************************************
/Quarantine Specialist Role Card Specifications:
/	Prevent disease cube placements (and outbreaks) in the city you are in and all cities connected.
/
/ This class's Specifications must be implemented in the Map class
/ In the Map class, if a city contains a player holding this RoleCard, that city cannot suffer
/ an outbreak or be infected.
*****************************************************************************************************/
class QuarantineSpecialist :
	public RoleCard
{
public:
	QuarantineSpecialist(Map* mp);
	QuarantineSpecialist(const QuarantineSpecialist& qs);
	virtual ~QuarantineSpecialist();
};

/****************************************************************************************************
/Dispatcher Role Card Specifications:
/	Move another player's pawn as if it were yours
/	As an action, move any pawn to a city with another pawn
/	Get permission before moving another player's pawn
/
/ We will be implementing this function to control only the current player's pawn for the time being
/ The player will only be able to move to a city with another pawn in it.
*****************************************************************************************************/
class Dispatcher :
	public RoleCard
{
public:
	Dispatcher(Map* mp);
	Dispatcher(const Dispatcher& disp);
	virtual ~Dispatcher();
	int specialMoveAnotherPlayer(Pawn* otherPlayer, int newCityID);
};