/********************************************************************
/ Claudia Della Serra, 26766048
/ COMP 345 Assignment 3
/ Player Strategy Pattern

/ This module represents the RoleCard class and all of its subclasses.
/ The role card is the concrete Strategy which extends the abstract
/ Strategy class. All roles inherite from this class, and implement
/ specific actions in their own way, to exhibit their special role
/ characteristics.
*********************************************************************/

#include "RoleCard.h"


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


/************************
/ Base Role Card Class
*************************/
RoleCard::RoleCard(Map* mp) : Strategy()
{
	mapRef = mp;
}

RoleCard::RoleCard(const RoleCard& rolec) {
	roleName = rolec.roleName;
	roleColor = rolec.roleColor;
	for (std::string sa : rolec.specialActions) {
		specialActions.push_back(sa);
	}
}

const RoleCard& RoleCard::operator=(const RoleCard& rc) {
	if (&rc != this) {
		roleName = rc.roleName;
		roleColor = rc.roleColor;
		for (std::string sa : rc.specialActions) {
			specialActions.push_back(sa);
		}
	}
	return *this;
}

RoleCard::~RoleCard()
{
}

/********************************************************************************************************
/ Function to drive to a connected city
/ Checks the player's current location's connections against the id of the new city
/ If the cities are connected, the player is moved to the new city
*********************************************************************************************************/
int RoleCard::drive(Pawn* pawn, int newCityID) {
	//Gets the player's current city. Should return a city object
	int currentLocationID = pawn->get_location();
	City* current = mapRef->getCityByID(currentLocationID);

	//Check if the cities are connected
	if (!(current->connectsTo(newCityID))) {
		std::cout << "Sorry, cannot drive there; cities not connected." << std::endl;
		return 0;
	}

	//Set the pawn's location to the new city ID
	mapRef->movePawn(pawn, newCityID);

	std::cout << "Player " << pawn->get_playerId() << " drove to " << mapRef->getCityByID(pawn->get_location())->name << "(" << pawn->get_location() << "). " << std::endl;
	return 1;
}

/********************************************************************************
/ Function to fly player to a city corresponding to the city card in his/her hand
/ Checks to make sure the card is a city card
/ If checks are passed, the player is flown to the new city
*********************************************************************************/
int RoleCard::directFlight(Pawn* pawn, PlayerCard dest) {
	std::string cardType = dest.getType();

	if (cardType != "city") {
		std::cout << "Indicated card is not a city card." << std::endl;
		return 0;
	}

	//Cannot perform this without city cards and city object full implementation
	int newCityID = dest.getCityId();
	mapRef->movePawn(pawn, newCityID);
	std::cout << "Player " << pawn->get_playerId() << " took a direct flight to " << mapRef->getCityByID(pawn->get_location())->name << "(" << pawn->get_location() << "). " << std::endl;
	return 1;
}


/**************************************************************************************************
/ Function to fly player to any city when the player is in a city and holds that city's Player card
/ Must check player's current location is equal to the card's city ID
/ Player will be moved to the city they have indicated
**************************************************************************************************/
int RoleCard::charterFlight(Pawn* pawn, PlayerCard dest, int newCityID) {
	std::string cardType = dest.getType();

	if (cardType != "city") {
		std::cout << "Cannot make Charter Flight. Indicated card is not a city card." << std::endl;
		return 0;
	}

	int currentLocation = pawn->get_location();

	if (currentLocation != dest.getCityId()) {
		std::cout << "Cannot make charter flight; indicated card does not match current city." << std::endl;
		return 0;
	}

	mapRef->movePawn(pawn, newCityID);

	std::cout << "Player " << pawn->get_playerId() << " took a charter flight to " << mapRef->getCityByID(pawn->get_location())->name << "(" << pawn->get_location() << "). " << std::endl;
	return 1;
}

/***************************************************************************************************
/ Function to fly player from a city with a research station to another city with a research station
/ Must check if the players current city has a research station
/ Must also check if the city corresponding to the city on the Player Card has a research station
****************************************************************************************************/
int RoleCard::shuttleFlight(Pawn* pawn, int newCityID) {
	int currentLocationID = pawn->get_location();
	City* currentLocation = mapRef->getCityByID(currentLocationID);

	//get the city object at the newCity id, then make sure both cities have research stations
	City* newCity = mapRef->getCityByID(newCityID);
	if (!(newCity->hasResearchStation()) || !(currentLocation->hasResearchStation())) {
		std::cout << "Cannot make shuttle flight; one of the cities does not have a research station" << std::endl;
		return 0;
	}

	//If both places have research stations, change the player's location
	mapRef->movePawn(pawn, newCityID);

	std::cout << "Player " << pawn->get_playerId() << " took a shuttle flight to " << mapRef->getCityByID(pawn->get_location())->name << "(" << pawn->get_location() << "). " << std::endl;
	return 1;
}

/**********************************************************************************
/ Function to build a research station in a city
/ Must make sure that the player passes in a card matching the city they are in
/ Must also make sure the current city does not have a research station already
***********************************************************************************/
int RoleCard::buildResearchStation(Pawn* pawn, PlayerCard currentCity) {
	std::string cardType = currentCity.getType();

	if (!(cardType == "city")) {
		std::cout << "Cannot build a research station, indicated card is not a city card" << std::endl;
		return 0;
	}

	int currentLocationID = pawn->get_location();
	City* currentLocation = mapRef->getCityByID(currentLocationID);

	if (!(currentCity.getCityId() == currentLocationID) || currentLocation->hasResearchStation()) {
		std::cout << "Cannot build research Station. City card does not match current location, or a research station already exists here." << std::endl;
		return 0;
	}

	//if all the proper conditions are met, build a research center in the current city
	mapRef->addResearchStation(currentLocationID);

	std::cout << "Research station has been built!" << std::endl;
	return 1;
}

/*******************************************************************************
/ Function to treat one disease cube in a city
/ If there are diseases to be cured in the city, the Player will treat one cube
*******************************************************************************/
int RoleCard::treatDisease(Pawn* pawn) {

	int currentLocationID = pawn->get_location();
	City* currentLocation = mapRef->getCityByID(currentLocationID);	//Cannot implement yet due to city objects not being implemented
	if (!(currentLocation->hasDisease())) {
		std::cout << "Current location does not have any diseases to treat." << std::endl;
		return 0;
	}

	mapRef->treatDisease(currentLocationID);

	std::cout << "Player " << pawn->get_playerId() << " has helped treat a disease in " << mapRef->getCityByID(pawn->get_location())->name << "(" << pawn->get_location() << "). " << std::endl;
	return 1;
}


/*********************************************************************************************************
/ Function to give a card to another player in the current city
/ The giving player will have their hand reduced, and the receiving player will have their hand increased
/ the card being passed must be checked against the id of the current city
/ We are constraining functionality so that the current player is the giving player. Only the current player
/ can give a card to the player of their choosing.
***********************************************************************************************************/
int RoleCard::shareKnowledge(Pawn* giverPawn, PlayerCard givingCard) {
	std::string cardType = givingCard.getType();

	if (!(cardType == "city")) {
		std::cout << "Cannot exchange non-city cards." << std::endl;
		return 0;
	}

	int currentLocation = giverPawn->get_location();
	if (givingCard.getCityId() != currentLocation) {
		std::cout << "Exchange card must match current city. Cannot share knowledge." << std::endl;
		return 0;
	}

	//If you get here, it means all checks have passed and the game class can perform the share of knowledge
	return 1;
}

/**************************************************************
/ Takes in an array of 5 player cards, all of the same color
/ This function will cure a disease of the corresponding color
/ Must only be executed in a city with a research station
***************************************************************/
int RoleCard::discoverCure(Pawn* pawn, vector<PlayerCard> cure) {

	//Get all the indicated cure cards and make sure they're all city cards
	for (PlayerCard cureCard : cure) {
		std::string cardType = cureCard.getType();
		if (!(cardType == "city")) {
			std::cout << "You must indicate 5 city cards. Please retry." << std::endl;
			return 0;
		}
	}

	//Check if all the cards are the same color
	for (int i = 1; i < 5; i++) {
		if (mapRef->getCityByID(cure[i].getCityId())->zone != mapRef->getCityByID(cure[i - 1].getCityId())->zone) {
			std::cout << "Indicated cards are not all the same color. Cannot Cure disease" << std::endl;
			return false;
		}
	}

	int currentLocationID = pawn->get_location();
	City* currentLocation = mapRef->getCityByID(currentLocationID);
	//Check if the current location has a research center
	if (!(currentLocation->hasResearchStation())) {
		std::cout << "Cannot cure disease; current city does not have research center." << std::endl;
		return 0;
	}

	char zone = mapRef->getCityByID(cure[0].getCityId())->zone;

	mapRef->cureDisease(zone);

	std::cout << "Player " << pawn->get_playerId() << " has cured a disease! " << std::endl;
	return 1;
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
	City* currentLocation = getMapRef()->getCityByID(currentLocationID);

	if (!currentLocation->hasDisease()) {
	cout << "Current location does not have any diseases to treat." << endl;
	return 0;
	}

	char zone;
	int amountOfInfection;
	for (int i = 0; i < 4; i++) {
		if (currentLocation->infectionCounters[i] > 0) {
			if (i == 0) zone = 'b';
			else if (i == 1) zone = 'r';
			else if (i == 2) zone = 'u';
			else zone = 'y';

			amountOfInfection = currentLocation->infectionCounters[i];
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
	addSpecialAction("Research Station to Any City Move");
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
	City* currentLocation = getMapRef()->getCityByID(currentLocationID);

	//Cannot run this yet, as the city and player card objects have not been implemented
	if (currentLocation->hasResearchStation()){
	cout << "Cannot build research Station; a research station already exists here." << endl;
	return 0;
	}

	//if all the proper conditions are met, build a research center in the current city
	getMapRef()->addResearchStation(currentLocationID);
	
	cout << "Research station has been built! \nGood news: You are an operations expert, you do not lose a city card!" << endl;
	return 1;
}

/********************************************************************************************************
/ Special function to  move an operations expert from a city with a research station to any other city,
/ given that they have a city card (does not have to match the destination city).
*********************************************************************************************************/
int OperationsExpert::specialOperationsMove(Pawn* pawn, PlayerCard moveCard) {
	if (specialUsedThisTurn) {
		cout << "Sorry, you can only use this action once per turn!" << endl;
		return 0;
	}

	std::string cardType = moveCard.getType();

	if (cardType != "city") {
		cout << "Cannot move without a city card." << endl;
		return 0;
	}
	
	int currentLocationID = pawn->get_location();
	City* currentLocation = getMapRef()->getCityByID(currentLocationID);
	//The following requires proper map and city implementation
	if (!currentLocation->hasResearchStation()) {
		cout << "Cannot execute special move from a city that does not have a research station." << endl;
		return 0;
	}

	int newCityID = moveCard.getCityId();
	getMapRef()->movePawn(pawn, newCityID);
	cout << "You have executed your Special Move! Your current location is now " << getMapRef()->getCityByID(pawn->get_location())->name << endl;
	specialWasUsed();
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
		if (getMapRef()->getCityByID(cure[i].getCityId())->zone != getMapRef()->getCityByID(cure[i-1].getCityId())->zone) {
			std::cout << "Indicated cards are not all the same color. Cannot Cure disease" << std::endl;
			return false;
		}
	}

	int currentLocationID = pawn->get_location();
	City* currentLocation = getMapRef()->getCityByID(currentLocationID);
	//Check if the current location has a research center
	if (!(currentLocation->hasResearchStation())) {
		std::cout << "Cannot cure disease; current city does not have research center." << std::endl;
		return 0;
	}

	char zone = getMapRef()->getCityByID(cure[0].getCityId())->zone;

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
	addSpecialAction("Pick up Special Event Card");
}

ContingencyPlanner::ContingencyPlanner(const ContingencyPlanner& cp) : RoleCard(cp) {
}


ContingencyPlanner::~ContingencyPlanner()
{
	delete specialEvent;
}

/******************************************************************************************************
/ Function that returns a boolean discerning whether the player is holding a special event card or not
*******************************************************************************************************/
bool ContingencyPlanner::hasSpecialEvent() {
	if (specialEvent) {
		return true;
	}
	return false;
}

/****************************************************************************************************************
/ Function to pick up a discarded event card
/ Functionality to access the discard pile must be implemented in the future
*****************************************************************************************************************/
int ContingencyPlanner::pickUpSpecialEvent(vector<PlayerCard> &discardPile) {
	if (!specialEvent) {
		int newEventCard = -1;
		cout << "Sorting through the discarded events! Which would you like to pick up?" << endl;
		do {
			cin.clear();
			cin.ignore(256, '\n');
			for (int cardIndex = 0; cardIndex < discardPile.size(); cardIndex++) {
				cout << cardIndex + 1 << ". " << discardPile[cardIndex].getName() << endl;
			}
			cin >> newEventCard;
		} while (newEventCard < 0 || newEventCard > discardPile.size() || cin.fail());

		specialEvent = new PlayerCard(discardPile[newEventCard - 1]);
		&discardPile.erase(discardPile.begin() + (newEventCard - 1));
		return 1;
	}
	else {
		cout << "You already have a special Event card stored. Please discard it before storing another." << endl;
		return 0;
	}
}

/***********************************************************
/ Function to show the value of their special event card
************************************************************/
void ContingencyPlanner::showSpecialEvent() {
	if (specialEvent) {
		cout << specialEvent->getValue();
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
/ Checks if there is at least one other pawn in the destination city
/ If yes, it moves the player to that city
********************************************************************************/
int Dispatcher::specialMoveAnotherPlayer(Pawn* otherPlayer, int newCityID) {
	City* newCity = getMapRef()->getCityByID(newCityID);
	if (newCity->pawnRefList.size() < 1) {
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





