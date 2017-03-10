/*
/ Claudia Della Serra, 26766048
/ COMP 345, Advanced Programming with C++
/
*/

#include "RoleCard.h"


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


/************************
/ Base Role Card Class
*************************/
RoleCard::RoleCard() : ReferenceCard()
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

Researcher::Researcher() : RoleCard()
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
int Researcher::shareKnowledge(Pawn* giverPawn, std::vector<PlayerCard> givingHand, std::vector<PlayerCard> receivingHand, int exchangeCard) {
	PlayerCard givingCard = givingHand.at(exchangeCard);
	std::string cardType = givingCard.getType();

	if (!(cardType == "City")) {
		cout << "Cannot exchange non-city cards." << endl;
		return 0;
	}

	//If you get here, it means the sharing knowledge is valid
	receivingHand.push_back(givingCard);
	cout << "Player " << giverPawn->get_playerId() << " has given a card to another player in " << giverPawn->get_location() << ". " << endl;
	return 1;
}
/*************************
/ End of Researcher Class
**************************/

/*************
/ Medic Class
**************/
Medic::Medic() : RoleCard()
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
/ Should treat all diseases of same color (this functionality will come once disease objects have been created)
*****************************************************************************************************************/
int Medic::treatDisease(Pawn* pawn) {
	int currentLocationID = pawn->get_location();
	City currentLocation = getMapRef()->getCityByID(currentLocationID);
	//Cannot implement yet due to city objects not being implemented
	if (!currentLocation.hasDisease()) {
	cout << "Current location does not have any diseases to treat." << endl;
	return 0;
	}
	int amountOfInfection = 0;
	for (int i = 0; i < 4; i++) {
		amountOfInfection += currentLocation.infectionCounters[i];
	}

	for(int i=0; i< amountOfInfection; i++){
		currentLocation.treatDisease();
	}

	cout << "You are a medic! You've treated all of the diseases in city " << currentLocationID << endl;
	return 1;
}
/*********************
/ End of Medic class
**********************/


/*************************
/ Operations Expert Class
*************************/
OperationsExpert::OperationsExpert() : RoleCard()
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
int OperationsExpert::buildResearchStation(Pawn* pawn, std::vector<PlayerCard*> hand, int cardIndex) {
	//Takes in a hand and card for semantics purposes, however does not do anything with them
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
int OperationsExpert::specialOperationsMove(Pawn* pawn, std::vector<PlayerCard> hand, int cardIndex) {
	PlayerCard moveCard = hand.at(cardIndex);
	std::string cardType = moveCard.getType();

	if (cardType != "City") {
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
	pawn->set_location(newCityID);
	cout << "You have executed your Special Move! Your current location is now " << pawn->get_location() << endl;
	return 1;


}
/*******************************
/ End of OperationsExpert Class
********************************/

/*************************
/ Scientist Class
*************************/
Scientist::Scientist() : RoleCard()
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
int Scientist::discoverCure(Pawn* pawn, std::vector<PlayerCard> hand, std::vector<int> cure) {
	PlayerCard cureCards[4];

	if (cure.size() > 4) {
		cout << "You have passed too many cards to this functions, please retry." << endl;
		return 0;
	}

	//Get all the indicated cure cards and make sure they're all city cards
	for (int i = 0; i < 4; i++) {
		PlayerCard cureCard = hand.at(cure[i]);
		std::string cardType = cureCard.getType();
		if (!(cardType == "City")) {
			cout << "Card at index " << cure[i] << " is not a city card. Cannot cure" << endl;
			return 0;
		}
		cureCards[i] = cureCard;
	}

	//Check if all the cards are the same color
	for (int i = 1; i < 4; i++) {
		if (cureCards[i].getColor() != cureCards[i - 1].getColor()) {
			cout << "Indicated cards are not all the same color. Cannot Cure disease" << endl;
			return false;
		}
	}

	int currentLocationID = pawn->get_location();
	City currentLocation = getMapRef()->getCityByID(currentLocationID);
	//Check if the current location has a research center
	if (!(currentLocation.hasResearchStation())) {
		cout << "Cannot cure disease; current city does not have research center." << endl;
		return 0;
	}

	getMapRef()->cureDisease();
	cout << "Player " << pawn->get_playerId() << " has cured a disease! " << endl;
	return 1;
}
/*******************************
/ End of Scientist Class
********************************/

/***************************
/ Contingency Planner Class
***************************/
ContingencyPlanner::ContingencyPlanner() : RoleCard()
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
QuarantineSpecialist::QuarantineSpecialist() : RoleCard()
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
Dispatcher::Dispatcher() : RoleCard()
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
int Dispatcher::specialMoveAnotherPlayer(Pawn* pawn, int newCityID, int playerID) {
	//Cannot implement without proper City and Map classes
	City newCity = getMapRef()->getCityByID(newCityID);
	if (newCity.pawnList.size()) {
		cout << "Cannot move to a city without Players in it." << endl;
		return 0;
	}

	Pawn otherPlayer = newCity.getPawnByID(playerID);
	
	otherPlayer.set_location(newCityID);
	cout << "Moved player " << otherPlayer.get_location()<< " to city " << newCityID << endl;
	return 1;
	
}
/***********************************
/ End of Dispatcher Class
************************************/





