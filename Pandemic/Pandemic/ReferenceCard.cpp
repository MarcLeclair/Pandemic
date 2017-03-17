#include "ReferenceCard.h"
#include <string>
#include <vector>
#include <iostream>


ReferenceCard::ReferenceCard() {}
ReferenceCard::ReferenceCard(Map* mp) : mapRef(mp){}
ReferenceCard::~ReferenceCard(){}

ReferenceCard::ReferenceCard(const ReferenceCard& rc) {
	mapRef = rc.mapRef;
}


/********************************************************************************************************
/ Function to drive to a connected city
/ Checks the player's current location's connections against the id of the new city
/ If the cities are connected, the player is moved to the new city
*********************************************************************************************************/
int ReferenceCard::drive(Pawn* pawn, int newCityID){
	//Gets the player's current city. Should return a city object
	int currentLocationID = pawn->get_location();
	City current = mapRef->getCityByID(currentLocationID);

	cout << "Obtained current city " << endl;

	//Check if the cities are connected
	if( !(current.connectsTo(newCityID))){
		std::cout << "Sorry, cannot drive there; cities not connected." << std::endl;
		return 0;
	}

	//Set the pawn's location to the new city ID
	mapRef->movePawn(pawn, newCityID);

	std::cout << "Player " << pawn->get_playerId() << " drove to " << pawn->get_location() << ". " << std::endl;
	return 1;
}

/********************************************************************************
/ Function to fly player to a city corresponding to the city card in his/her hand
/ Checks to make sure the card is a city card
/ If checks are passed, the player is flown to the new city
*********************************************************************************/
int ReferenceCard::directFlight(Pawn* pawn, PlayerCard dest) {
	std::string cardType = dest.getType();

	if (cardType != "city") {
		std::cout << "Indicated card is not a city card." << std::endl;
		return 0;
	}
	
	//Cannot perform this without city cards and city object full implementation
	int newCityID = dest.getCityId();
	mapRef->movePawn(pawn, newCityID);
	std::cout << "Player " << pawn->get_playerId() << " took a direct flight to " << pawn->get_location() << ". " << std::endl;
	return 1;
}


/**************************************************************************************************
/ Function to fly player to any city when the player is in a city and holds that city's Player card
/ Must check player's current location is equal to the card's city ID
/ Player will be moved to the city they have indicated
**************************************************************************************************/
int ReferenceCard::charterFlight(Pawn* pawn, PlayerCard dest, int newCityID) {
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

	std::cout << "Player " << pawn->get_playerId() << " took a charter flight to " << pawn->get_location() << ". " << std::endl;
	return 1;
}

/***************************************************************************************************
/ Function to fly player from a city with a research station to another city with a research station
/ Must check if the players current city has a research station
/ Must also check if the city corresponding to the city on the Player Card has a research station
****************************************************************************************************/
int ReferenceCard::shuttleFlight(Pawn* pawn, int newCityID) {
	int currentLocationID = pawn->get_location();
	City currentLocation = mapRef->getCityByID(currentLocationID);

	//get the city object at the newCity id, then make sure both cities have research stations
	City newCity = mapRef->getCityByID(newCityID);
	if (!(newCity.hasResearchStation()) || !(currentLocation.hasResearchStation())){
		std::cout << "Cannot make shuttle flight; one of the cities does not have a research station" << std::endl;
		return 0;
	}

	//If both places have research stations, change the player's location
	mapRef->movePawn(pawn, newCityID);

	std::cout << "Player " << pawn->get_playerId() << " took a shuttle flight to " << pawn->get_location() << ". " << std::endl;
	return 1;
}

/**********************************************************************************
/ Function to build a research station in a city
/ Must make sure that the player passes in a card matching the city they are in
/ Must also make sure the current city does not have a research station already
***********************************************************************************/
int ReferenceCard::buildResearchStation(Pawn* pawn, PlayerCard currentCity) {
	std::string cardType = currentCity.getType();

	if (!(cardType == "city")) {
		std::cout << "Cannot build a research station, indicated card is not a city card" << std::endl;
		return 0;
	}

	int currentLocationID = pawn->get_location();
	City currentLocation = mapRef->getCityByID(currentLocationID);

	if (!(currentCity.getCityId() == currentLocationID) || currentLocation.hasResearchStation()){
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
int ReferenceCard::treatDisease(Pawn* pawn) {

	int currentLocationID = pawn->get_location();
	City currentLocation = mapRef->getCityByID(currentLocationID);	//Cannot implement yet due to city objects not being implemented
	if (!(currentLocation.hasDisease())) {
		std::cout << "Current location does not have any diseases to treat." << std::endl;
		return 0;
	}
	
	mapRef->treatDisease(currentLocationID);

	std::cout << "Player " << pawn->get_playerId() << " has helped treat a disease in " << pawn->get_location() << ". " << std::endl;
	return 1;
}


/*********************************************************************************************************
/ Function to give a card to another player in the current city
/ The giving player will have their hand reduced, and the receiving player will have their hand increased
/ the card being passed must be checked against the id of the current city
/ We are constraining functionality so that the current player is the giving player. Only the current player
/ can give a card to the player of their choosing.
***********************************************************************************************************/
int ReferenceCard::shareKnowledge(Pawn* giverPawn, PlayerCard givingCard, std::vector<PlayerCard> receivingHand) {
	std::string cardType = givingCard.getType();

	if (!(cardType == "city")) {
		std::cout << "Cannot exchange non-city cards." << std::endl;
		return 0;
	}

	int currentLocation = giverPawn->get_location();
	if (!(givingCard.getCityId() != currentLocation)) {
		std::cout << "Exchange card must match current city. Cannot share knowledge." << std::endl;
		return 0;
	}

	//If you get here, it means the sharing knowledge is valid
	receivingHand.push_back(givingCard);
	std::cout << "Player " << giverPawn->get_playerId() << " has given a card to another player in " << giverPawn->get_location() << ". " << std::endl;
	return 1;
}

/**************************************************************
/ Takes in an array of 5 player cards, all of the same color
/ This function will cure a disease of the corresponding color
/ Must only be executed in a city with a research station
***************************************************************/
int ReferenceCard::discoverCure(Pawn* pawn, vector<PlayerCard> cure) {

	//Get all the indicated cure cards and make sure they're all city cards
	for (PlayerCard cureCard : cure) {
		std::string cardType = cureCard.getType();
		if (!(cardType == "city")) {
			std::cout << "You must indicate 5 city cards. Please retry."<< std::endl;
			return 0;
		}
	}

	//Check if all the cards are the same color
	for (int i = 1; i < 5; i++) {
		if (cure[i].getColour() != cure[i - 1].getColour()) {
			std::cout << "Indicated cards are not all the same color. Cannot Cure disease" << std::endl;
			return false;
		}
	}

	int currentLocationID = pawn->get_location();
	City currentLocation = mapRef->getCityByID(currentLocationID);
	//Check if the current location has a research center
	if (!(currentLocation.hasResearchStation())) {
		std::cout << "Cannot cure disease; current city does not have research center." << std::endl;
		return 0;
	}

	string cureColor = cure[0].getColour();
	char zone;

	//assign a zone id to the color for curing purposes
	if (cureColor == "black")
		zone = 'b';
	else if (cureColor == "blue")
		zone = 'u';
	else if (cureColor == "red")
		zone = 'r';
	else
		zone = 'y';


	mapRef->cureDisease(zone);

	std::cout << "Player " << pawn->get_playerId() << " has cured a disease! " << std::endl;
	return 1;
}
