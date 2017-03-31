
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "PlayerCard.h"
#include "ReferenceCard.h"
#include "map.h"

using namespace std;

/************************************************************************************************************************************************************************
/ RoleCard class, base class for all roles
/ Designed this as a hierarchy in order to be able to hold a deck of Role Cards
/ I.e. This will allow all types of role cards to be held in the same data structure
/ Also allows for the abstraction of the role cards players can hold (i.e. they can hold a generic RoleCard pointer, but through polymorphism perform specific role tasks
**************************************************************************************************************************************************************************/
class RoleCard : public ReferenceCard
{
public:
	RoleCard(Map* mp);
	RoleCard(const RoleCard& rolec);
	~RoleCard();

	void RoleCard::setRoleName(string name) {
		roleName = name;
	}

	string RoleCard::getRoleName() {
		return roleName;
	}

	void RoleCard::setRoleColor(string color) {
		roleColor = color;
	}

	string RoleCard::getRoleColor() {
		return roleColor;
	}

	void addSpecialAction(string sp){
		specialActions.push_back(sp);
	}

	vector<string> getSpecialActions() {
		return specialActions;
	}

	string getRoleDescription(){
		return roleDescription;
	}

	void setRoleDescription(string desc) {
		roleDescription = desc;
	}

private:
	string roleName;
	string roleColor;
	string roleDescription;
	vector<string> specialActions;
};


/*******************************************************************************************************************************
/ Researcher Role Card Specifications:
/	You may give any 1 of your City cards when you share knowledge. It need not match your city.
/	A player who shares knowledge with you on their turn can take any 1 of your city cards.
/	This functionality is currently not implemented, as sharing knowledge is limited to only giving cards, and not taking.
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
/	Currently, functionality has the medic removing all cubes of any disease from the city. This will be updated when disease objects are implemented
/	Automatically remove cubes of cured diseases from the city you are in (and prevent them from being placed there)
/
/ The second part of this Role's functionality should be implemented in the Map class
/ If a disease has been cured, and the player's current city has disease cubes of that color, then all of those disease cubes must be taken out
/ Such an action will happen every time the player holding the Medic RoleCard changes location.
/ Also, if the medic's current city is infected with a cured disease, he will prevent cubes from being placed there
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
	bool specialUsedThisTurn = false;
public:
	OperationsExpert(Map* mp);
	OperationsExpert(const OperationsExpert &ops);
	virtual ~OperationsExpert();
	virtual int buildResearchStation(Pawn* pawn, PlayerCard currentCity);
	int specialOperationsMove(Pawn* pawn, PlayerCard moveCard);
	void specialWasUsed() {
		specialUsedThisTurn = true;
	}

	void resetSpecialUsed() {
		specialUsedThisTurn = false;
	}
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
	void playSpecialEvent();
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