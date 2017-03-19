#include "RoleCard.h"


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


/************************
/ Base Role Card Class
*************************/
RoleCard::RoleCard(Map* mp) : ReferenceCard(mp)
{
}

RoleCard::RoleCard(const RoleCard& rolec) {
	roleName = rolec.roleName;
	roleColor = rolec.roleColor;
	for (std::string sa : rolec.specialActions) {
		specialActions.push_back(sa);
	}
}

RoleCard::~RoleCard()
{
}


/**********************************
/ Researcher Class Implementations
***********************************/

Researcher::Researcher(Map* mp) : RoleCard(mp)
{
	setRoleName("Researcher");
	setRoleColor("brown");
	setRoleDescription("You may give any 1 of your City cards when you share knowledge. It need not match your city.");
}

Researcher::Researcher(const Researcher& res): RoleCard(res) {
	
}

Researcher::~Researcher()
{
}


/***********************************************************************************
/ Function to share knowledge with another player in the current city.
/ The city card shared DOES NOT have to match the current city the players are in.
/ However, it must still be a city card
/ This is an override of the inherited function from ReferenceCard
************************************************************************************/
int Researcher::shareKnowledge(Pawn* giverPawn, PlayerCard givingCard) {
	std::string cardType = givingCard.getType();

	if (!(cardType == "city")) {
		cout << "Cannot exchange non-city cards." << endl;
		return 0;
	}

	return 1;
}
/*************************
/ End of Researcher Class
**************************/

/*************
/ Medic Class
**************/
Medic::Medic(Map* mp) : RoleCard(mp)
{
	setRoleName("Medic");
	setRoleColor("orange");
	setRoleDescription("Remove ALL cubes of one color when doing Treat Disease.");
}

Medic::Medic(const Medic& med) : RoleCard(med) {

}

Medic::~Medic()
{
}

/****************************************************************************************************************
/ Overidden function from Reference Card.
/ Treats all of the diseases in a city.
/ Should treat all diseases of same color, thus if there are cubes of more than one color in the city, only the
/ cubes of one of the colors will be treated
*****************************************************************************************************************/
int Medic::treatDisease(Pawn* pawn) {
	int currentLocationID = pawn->get_location();
	City currentLocation = getMapRef()->getCityByID(currentLocationID);

	if (!currentLocation.hasDisease()) {
	cout << "Current location does not have any diseases to treat." << endl;
	return 0;
	}

	char zone;
	int amountOfInfection;
	for (int i = 0; i < 4; i++) {
		if (currentLocation.infectionCounters[i] > 0) {
			if (i == 0) zone = 'b';
			else if (i == 1) zone = 'r';
			else if (i == 2) zone = 'u';
			else zone = 'y';

			amountOfInfection = currentLocation.infectionCounters[i];
			break;
		}
	}

	for(int i=0; i< amountOfInfection; i++){
		getMapRef()->treatDisease(currentLocationID, zone);
	}

	cout << "You are a medic! You've treated all of the diseases of one color in city " << currentLocationID << endl;
	return 1;
}
/*********************
/ End of Medic class
**********************/


/*************************
/ Operations Expert Class
*************************/
OperationsExpert::OperationsExpert(Map* mp) : RoleCard(mp)
{
	setRoleName("Operations Expert");
	setRoleColor("lime");
	setRoleDescription("As an action, build a research station in the city you are in (no city card needed)");
	addSpecialAction("specialOperationsMove");
}

OperationsExpert::OperationsExpert(const OperationsExpert &ops) : RoleCard(ops) {
}

OperationsExpert::~OperationsExpert()
{
}

/****************************************************************************************************************
/ Function to build a reserch station without using any city cards
/ This should be an overload of the ReferenceCard function to build a research station
*****************************************************************************************************************/
int OperationsExpert::buildResearchStation(Pawn* pawn, PlayerCard currentCity) {
	//Passes a card for semantics, however it does nothing with the card and the card will not be discarded from the player's hand
	int currentLocationID = pawn->get_location();
	City currentLocation = getMapRef()->getCityByID(currentLocationID);

	//Cannot run this yet, as the city and player card objects have not been implemented
	if (currentLocation.hasResearchStation()){
	cout << "Cannot build research Station; a research station already exists here." << endl;
	return 0;
	}

	//if all the proper conditions are met, build a research center in the current city
	currentLocation.buildResearchStation();
	
	cout << "Research station has been built! \nGood news: You are an operations expert, you do not lose a city card!" << endl;
	return 1;
}

/********************************************************************************************************
/ Special function to  move an operations expert from a city with a research station to any other city,
/ given that they have a city card (does not have to match the destination city).
*********************************************************************************************************/
int OperationsExpert::specialOperationsMove(Pawn* pawn, PlayerCard moveCard) {
	std::string cardType = moveCard.getType();

	if (cardType != "city") {
		cout << "Cannot move without a city card." << endl;
		return 0;
	}
	
	int currentLocationID = pawn->get_location();
	City currentLocation = getMapRef()->getCityByID(currentLocationID);
	//The following requires proper map and city implementation
	if (!currentLocation.hasResearchStation()) {
		cout << "Cannot execute special move from a city that does not have a research station." << endl;
		return 0;
	}

	int newCityID = moveCard.getCityId();
	getMapRef()->movePawn(pawn, newCityID);
	cout << "You have executed your Special Move! Your current location is now " << getMapRef()->getCityByID(pawn->get_location()).name << endl;
	return 1;


}
/*******************************
/ End of OperationsExpert Class
********************************/

/*************************
/ Scientist Class
*************************/
Scientist::Scientist(Map* mp) : RoleCard(mp)
{
	setRoleName("Scientist");
	setRoleColor("White");
	setRoleDescription("You only need 4 cards of the same color to do the Discover a Cure action");
}

Scientist::Scientist(const Scientist& sci) : RoleCard(sci) {

}

Scientist::~Scientist()
{
}

/****************************************************************************************************************
/ Function to cure diseases
/ Only change from Reference card is that it expects 4 cure cards and not 5
*****************************************************************************************************************/
int Scientist::discoverCure(Pawn* pawn, vector<PlayerCard> cure) {

	//Get all the indicated cure cards and make sure they're all city cards
	for (PlayerCard cureCard : cure) {
		std::string cardType = cureCard.getType();
		if (cardType != "city") {
			std::cout << "You must indicate 5 city cards. Please retry." << std::endl;
			return 0;
		}
	}

	//Check if all the cards are the same color
	for (int i = 1; i < 4; i++) {
		if (getMapRef()->getCityByID(cure[i].getCityId()).zone != getMapRef()->getCityByID(cure[i-1].getCityId()).zone) {
			std::cout << "Indicated cards are not all the same color. Cannot Cure disease" << std::endl;
			return false;
		}
	}

	int currentLocationID = pawn->get_location();
	City currentLocation = getMapRef()->getCityByID(currentLocationID);
	//Check if the current location has a research center
	if (!(currentLocation.hasResearchStation())) {
		std::cout << "Cannot cure disease; current city does not have research center." << std::endl;
		return 0;
	}

	char zone = getMapRef()->getCityByID(currentLocationID).zone;

	getMapRef()->cureDisease(zone);

	std::cout << "Player " << pawn->get_playerId() << " has cured a disease! " << std::endl;
	return 1;
}
/*******************************
/ End of Scientist Class
********************************/

/***************************
/ Contingency Planner Class
***************************/
ContingencyPlanner::ContingencyPlanner(Map* mp) : RoleCard(mp)
{
	setRoleName("Contingency Planner");
	setRoleColor("Blue");
	setRoleDescription("As an action, take any discarded event card and store it on this card");
	addSpecialAction("useSpecialEvent");
}

ContingencyPlanner::ContingencyPlanner(const ContingencyPlanner& cp) : RoleCard(cp) {
}


ContingencyPlanner::~ContingencyPlanner()
{
	delete specialEvent;
}

/****************************************************************************************************************
/ Function to pick up a discarded event card
/ Functionality to access the discard pile must be implemented in the future
*****************************************************************************************************************/
int ContingencyPlanner::pickUpSpecialEvent(PlayerCard* sp) {
	if (!specialEvent) {
		specialEvent = sp;
		return 1;
	}
	else {
		cout << "You already have a special Event card stored. Please discard it before storing another." << endl;
		return 0;
	}
}
/****************************************************
/ Function to discard the stored special Event card
****************************************************/
void ContingencyPlanner::discardSpecialEvent() {
	if (specialEvent) {
		delete specialEvent;
		specialEvent = NULL;
	}
	else{
		cout << "No special Event card is being held." << endl;
		return;
	}
}

/************************************************
/ Function to execute the special event being held
*************************************************/
void ContingencyPlanner::playSpecialEvent() {
	//Cannot execute without proper PlayerCard implementation
	if (specialEvent) {
		//specialEvent.executeEvent();
	}
	else {
		cout << "No special Event card is currently being held." << endl;
		return;
	}
}
/********************************
/ End of ContingencyPlanner Class
*********************************/

/***************************
/ QuarantineSpecialist Class
***************************/
QuarantineSpecialist::QuarantineSpecialist(Map* mp) : RoleCard(mp)
{
	setRoleName("Quarantine Specialist");
	setRoleColor("green");
	setRoleDescription("Prevent disease cube placements (and outbreaks) in the city you are in and all cities connected.");
}

QuarantineSpecialist::QuarantineSpecialist(const QuarantineSpecialist& qs) : RoleCard(qs) {

}


QuarantineSpecialist::~QuarantineSpecialist()
{
}

/***********************************
/ End of QuarantineSpecialist Class 
************************************/

/***************************
/ Dispatcher Class
***************************/
Dispatcher::Dispatcher(Map* mp) : RoleCard(mp)
{
	setRoleName("Dispatcher");
	setRoleColor("pink");
	setRoleDescription("Move another player's pawn as if it were yours");
	addSpecialAction("Move another Player");
}

Dispatcher::Dispatcher(const Dispatcher& disp) : RoleCard(disp) {

}
Dispatcher::~Dispatcher()
{
}

/*******************************************************************************
/ Function to move to a city with another pawn already in it
********************************************************************************/
int Dispatcher::specialMoveAnotherPlayer(Pawn* otherPlayer, int newCityID) {
	//Cannot implement without proper City and Map classes
	City newCity = getMapRef()->getCityByID(newCityID);
	if (newCity.pawnList.size()) {
		cout << "Cannot move to a city without Players in it." << endl;
		return 0;
	}

	getMapRef()->movePawn(otherPlayer, newCityID);
	cout << "Moved player " << otherPlayer->get_playerId() << " to city " << newCityID << endl;
	return 1;
	
}
/***********************************
/ End of Dispatcher Class
************************************/





