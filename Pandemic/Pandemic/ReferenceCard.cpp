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

	//Check if the cities are connected
	if( !(current.connectsTo(newCityID))){
		cout << "Sorry, cannot drive there; cities not connected." << endl;
		return 0;
	}

	//Set the pawn's location to the new city ID
	mapRef->movePawn(pawn, newCityID);

	cout << "Player " << pawn->get_playerId() << " drove to " << mapRef->getCityByID(pawn->get_location()).name  << "(" << pawn->get_location() << "). " << endl;
	return 1;
}

/********************************************************************************
/ Function to fly player to a city corresponding to the city card in his/her hand
/ Checks to make sure the card is a city card
/ If checks are passed, the player is flown to the new city
*********************************************************************************/
int ReferenceCard::directFlight(Pawn* pawn, PlayerCard dest) {
	string cardType = dest.getType();

	if (cardType != "city") {
		cout << "Indicated card is not a city card." << endl;
		return 0;
	}
	
	//Get the city ID of your destination from the card you passed
	int newCityID = dest.getCityId();
	mapRef->movePawn(pawn, newCityID);
	cout << "Player " << pawn->get_playerId() << " took a direct flight to " << mapRef->getCityByID(pawn->get_location()).name << "(" << pawn->get_location() << "). " << endl;
	return 1;
}


/**************************************************************************************************
/ Function to fly player to any city when the player is in a city and holds that city's Player card
/ Must check whether the card passed is a valid city card
/ Must check player's current location is equal to the card's city ID
/ Player will be moved to the city they have indicated
**************************************************************************************************/
int ReferenceCard::charterFlight(Pawn* pawn, PlayerCard dest, int newCityID) {
	string cardType = dest.getType();

	if (cardType != "city") {
		cout << "Cannot make Charter Flight. Indicated card is not a city card." << endl;
		return 0;
	}

	int currentLocation = pawn->get_location();

	if (currentLocation != dest.getCityId()) {
		cout << "Cannot make charter flight; indicated card does not match current city." << endl;
		return 0;
	}

	//Move the pawn to the city ID they want to go to
	mapRef->movePawn(pawn, newCityID);
	cout << "Player " << pawn->get_playerId() << " took a charter flight to " << mapRef->getCityByID(pawn->get_location()).name << "(" << pawn->get_location() << "). " << endl;
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
		cout << "Cannot make shuttle flight; one of the cities does not have a research station" << endl;
		return 0;
	}

	//If both places have research stations, change the player's location
	mapRef->movePawn(pawn, newCityID);

	cout << "Player " << pawn->get_playerId() << " took a shuttle flight to " << mapRef->getCityByID(pawn->get_location()).name << "(" << pawn->get_location() << "). " << endl;
	return 1;
}

/**********************************************************************************
/ Function to build a research station in a city
/ Must make sure that the player passes in a card matching the city they are in
/ Must also make sure the current city does not have a research station already
***********************************************************************************/
int ReferenceCard::buildResearchStation(Pawn* pawn, PlayerCard currentCity) {
	string cardType = currentCity.getType();

	if (!(cardType == "city")) {
		cout << "Cannot build a research station, indicated card is not a city card" << endl;
		return 0;
	}

	//Get pawn's current location to obtain information
	int currentLocationID = pawn->get_location();
	City currentLocation = mapRef->getCityByID(currentLocationID);

	if (!(currentCity.getCityId() == currentLocationID) || currentLocation.hasResearchStation()){
		cout << "Cannot build research Station. City card does not match current location, or a research station already exists here." << endl;
		return 0;
	}
	
	//if all the proper conditions are met, build a research center in the current city
	mapRef->addResearchStation(currentLocationID);
	
	cout << "Research station has been built!" << endl;
	return 1;
}

/*******************************************************************************
/ Function to treat one disease cube in a city
/ If there are diseases to be cured in the city, the Player will treat one cube
*******************************************************************************/
int ReferenceCard::treatDisease(Pawn* pawn) {

	int currentLocationID = pawn->get_location();
	City currentLocation = mapRef->getCityByID(currentLocationID);

	//Check if there are any disease cubes in the city
	if (!(currentLocation.hasDisease())) {
		cout << "Current location does not have any diseases to treat." << endl;
		return 0;
	}
	
	mapRef->treatDisease(currentLocationID);

	cout << "Player " << pawn->get_playerId() << " has helped treat a disease in " << mapRef->getCityByID(pawn->get_location()).name << "(" << pawn->get_location() << "). " << endl;
	return 1;
}


/*********************************************************************************************************
/ Function to give a card to another player in the current city
/ Only the checks will be performed in this method, as the actual passing of the card is done in the
/ game class, which has access to players
***********************************************************************************************************/
int ReferenceCard::shareKnowledge(Pawn* giverPawn, PlayerCard givingCard) {
	string cardType = givingCard.getType();

	//Check if the card being passed is a city card
	if (!(cardType == "city")) {
		cout << "Cannot exchange non-city cards." << endl;
		return 0;
	}

	//Check if the card being passed matches the current location
	int currentLocation = giverPawn->get_location();
	if (givingCard.getCityId() != currentLocation) {
		cout << "Exchange card must match current city. Cannot share knowledge." << endl;
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
int ReferenceCard::discoverCure(Pawn* pawn, vector<PlayerCard> cure) {

	//Get all the indicated cure cards and make sure they're all city cards
	for (PlayerCard cureCard : cure) {
		string cardType = cureCard.getType();
		if (!(cardType == "city")) {
			cout << "You must indicate 5 city cards. Please retry."<< endl;
			return 0;
		}
	}

	//Check if all the cards are the same color
	for (int i = 1; i < 5; i++) {
		if (mapRef->getCityByID(cure[i].getCityId()).zone != mapRef->getCityByID(cure[i-1].getCityId()).zone){
			cout << "Indicated cards are not all the same color. Cannot Cure disease" << endl;
			return false;
		}
	}

	int currentLocationID = pawn->get_location();
	City currentLocation = mapRef->getCityByID(currentLocationID);
	//Check if the current location has a research center
	if (!(currentLocation.hasResearchStation())) {
		cout << "Cannot cure disease; current city does not have research center." << endl;
		return 0;
	}

	//Get the zone of the city and cure it using that zone
	char zone = mapRef->getCityByID(cure[0].getCityId()).zone;	
	mapRef->cureDisease(zone);

	cout << "Player " << pawn->get_playerId() << " has cured a disease! " << endl;
	return 1;
}
