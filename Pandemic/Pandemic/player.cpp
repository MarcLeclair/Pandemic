
#include "Player.h"
#include <string>
#include <iostream>
#include "ReferenceCard.h"
#include "RoleCard.h"
#include "PlayerCard.h"

using namespace std;

/*************************************************
/ Default Player function for basic functionality
***************************************************/
Player::Player() {

}

/********************************************************************************
/ Player Constructor
/ Assigns the input player ID, and creates a new reference card for the player
/ Creates the player's pawn based on the role card passed
/ Requires a map reference for the reference card and role cards
*********************************************************************************/
Player::Player(int pid, RoleCard* rolec) : Subject()
{
	playerID = pid;
	setReferenceCard(new ReferenceCard());

	setRoleCard(rolec);

	setMyPawn(new Pawn(role->getRoleColor(), playerID));

	//All players start out in Castle Town
	getMyPawn()->set_location(4);
}

/**********************************************************************************
/ Copy Constructor
/ Important for the copying of player objects, since they hold multiple pointers
***********************************************************************************/
Player::Player(const Player& plr) : Subject(){
	playerID = plr.playerID;
	role = plr.role;

	ReferenceCard* tempRef = new ReferenceCard(*plr.refcard);
	refcard = tempRef;

	Pawn* tempPawn = new Pawn(*plr.playerPawn);
	playerPawn = tempPawn;

	for (PlayerCard pc : plr.cardsInHand) {
		PlayerCard* tempPC = new PlayerCard(pc);
		cardsInHand.push_back(*tempPC);
	}
}

/***************************************************************************************************
/ Player destructor
/ Takes care of deleting all the pointers held by the player, including the pawn and reference card
***************************************************************************************************/
Player::~Player()
{
	delete role;
	delete playerPawn;
	delete refcard;
	(getHand()).clear();
}

/******************************************************************************
/ Assignment operator overload
/ Takes care of the pointer assignment when copying/assigning a player object
******************************************************************************/
const Player& Player::operator=(const Player& pl) {
	if (&pl != this) {
		//delete any existing values before assigning new ones to avoid confusion and improper deletion
		delete role;
		cardsInHand.clear();
		delete refcard;
		delete playerPawn;

		playerPawn = new Pawn(*pl.playerPawn);
		refcard = new ReferenceCard(*pl.refcard);
		role = pl.role;

		for (PlayerCard pc : pl.cardsInHand) {
			cardsInHand.push_back(*(new PlayerCard(pc)));
		}

	}
	return *this;
}


/***************************************************************************
/ Function to balance the player's hand when they've drawn too many cards
/ Will result in the chosen card being discarded from the player's hand
****************************************************************************/
void Player::balanceHand(vector<PlayerCard> &discardPile) {
	if (numOfCards > maxCardsInHand) {
		cout << "\nToo many cards in hand, please choose one to discard." << endl;
		displayCardsInHand();

		int cardToDiscard;
		cout << "Card to discard (number): " << endl;
		cin >> cardToDiscard;

		//Make sure the proper index was given and that an integer was passed
		while (cardToDiscard > cardsInHand.size() || cardToDiscard < 1 || cin.fail()) {
			std::cout << "\nInvalid Choice. Please choose again\n" << std::endl;
			displayCardsInHand();
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> cardToDiscard;
		}

		discardCard((cardToDiscard - 1), discardPile);
		//Always set the number of cards in the player's hand
		setNumOfCards();
	}
}

/************************************************************************************************
/ Function to draw a player card from the deck
/ If the player draws a card and ends up with more than the allowed number of cards in his hand,
/ he will automtically be asked to discard a card
************************************************************************************************/
void Player::drawCard(PlayerCard plc, vector<PlayerCard> &discardPile) {
	cardsInHand.push_back(plc);
	setNumOfCards();
	balanceHand(discardPile);
}

/********************************************************************
/ Function to display all of the cards held
/ Iterates through the player's hand and gets the title of the card
/ along with the color, and the card's ID if it is a city card
*********************************************************************/
void Player::displayCardsInHand() {
	int cardNum = 1;
	for (PlayerCard card : cardsInHand) {
		if(card.getType() == "city")
			cout << "\t" << cardNum << ". " << card.getType() << " card "<< card.getColour() << ": " << card.getValue() << "(" << card.getCityId() << ")" <<endl;
		else
			cout << "\t" << cardNum << ". " << card.getType() << " card : " << card.getValue() << endl;
		cardNum++;
	}
}

/***********************************************************************************
/ Function to remove a card from the player's hand
/ Simply accesses the player's hand and deletes the card at the index indicated
/ Does not actually delete the card, just the copy of the card in the player's hand
************************************************************************************/

void Player::discardCard(int disc, vector<PlayerCard> &discardPile) {
	if (cardsInHand.at(disc).getValue() == "event"){
		PlayerCard card = cardsInHand.at(disc);
		cardsInHand.erase(cardsInHand.begin() + disc);
		setNumOfCards();
		discardPile.push_back(card);
	}
	else {
		cardsInHand.erase(cardsInHand.begin() + disc);
		setNumOfCards();
	}
	notify();
}

/**********************************************************************
/ Function to output the possible actions that the player can execute
/ Corresponds to the actions found in the Reference Card class
**********************************************************************/
void Player::outputPossibleActions() {
	vector<string> allActions = refcard->getAllActions();
	int actionNum = 1;
	for (string action : allActions) {
		cout << actionNum << ". " << action << endl;
		actionNum++;
	}
	//For roles that have special moves that can be used as actions
	for (string sp : role->getSpecialActions()) {
		cout << actionNum << ". " << sp << endl;
	}
}

/******************************************************************************
/ Function to allow users to choose an action to execute
/ Will return a number corresponding to the action the user wants to perform
*******************************************************************************/
int Player::requestAction() {
	cout << "\nSpecify by number which action you wish to perform:" << endl;
	outputPossibleActions();
	int newAction;
	cin >> newAction;

	//If the user enters a character other than a number
	while (std::cin.fail()) {
		std::cout << "\nInvalid Choice. Please choose again\n" << std::endl;
		outputPossibleActions();
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> newAction;
	}
	return newAction;
}

/*******************************************************************************
/ Function to output all relevant information about the player
/ Will output the player's role and current location, and their hand of cards
********************************************************************************/
void Player::display_player_info() {
	cout << "\nPlayer " << getPlayerID() << "'s info: " << endl;

	//1) Pawn information
	cout << "    Player is a " << getRole() << " in Location " << getCurrentLocation() << endl;
	cout << "    Player's role description: " << role->getRoleDescription() << endl;

	//3 PlayerCards information
	cout << "    Player's current hand: " << endl;
	displayCardsInHand();

}

/**************************************************************
/ Function to execute the drive function on this player's pawn
/ The player's pawn and the new city ID are passed to the
/ function executed by the role card.
/ If the function is successful, the playerview will be updated
***************************************************************/
int Player::drive(int newCityID) {
	int success= role->drive(playerPawn, newCityID);
	if (success > 0)
		notify(); //If the action worked, notify all the observers
	return success;
}

/********************************************************************
/ Function to execute a direct flight function on this player's pawn
/ The card from the player's hand that the player wishes to play
/ is found and passed to the function from role card.
/ If the function is a success, the playerview will be updated
*********************************************************************/
int Player::direct_flight(int cardIndex) {
	PlayerCard destination = cardsInHand[cardIndex];
	int success =  role->directFlight(playerPawn, destination);
	if (success > 0)
		notify(); //If the action worked, notify all the observers
	return success;
}

/********************************************************************************
/ Function to execute a charter flight to another city
/ The card the player wishes to play will be selected from their hand
/ This card and the player's pawn will be passed to the function from role card
/ If the function succeeds, the playerview will be notified
*******************************************************************************/
int Player::charter_flight(int cardIndex, int newCityID) {
	PlayerCard destination = cardsInHand[cardIndex];
	int success = role->charterFlight(playerPawn, destination, newCityID);
	if (success > 0)
		notify(); //If the action worked, notify all the observers
	return success;
}

/***********************************************************************************
/ Function to execute a shuttle flight to another city with a research station
/ The player's pawn and a new city id will be passed to the function from role card
/ Upon success the playerview will be notified
************************************************************************************/
int Player::shuttle_flight(int newCityID) {
	int success = role->shuttleFlight(playerPawn, newCityID);
	if (success > 0)
		notify(); //If the action worked, notify all the observers
	return success;
}

/***********************************************************
/ Function to build a research station in your current city
/ Retrieves the card the from the player's hand that they wish to play
/ Passes this card and the player's pawn to the function in role card
/ If the function succeeds, the playerview is updated
************************************************************/
int Player::build_research_station(int cardIndex) {
	PlayerCard currentCity = cardsInHand[cardIndex];
	int success = role->buildResearchStation(playerPawn, currentCity);
	if (success > 0)
		notify(); //If the action worked, notify all the observers
	return success;
}

/******************************************************
/ Function to treat a disease cube in the current city
/ Passes the player's pawn to the function in role card
*******************************************************/
int Player::treat_disease() {
	int success = role->treatDisease(playerPawn);
	return success;
}

/********************************************************************************************
/ Function to give one of your city cards to another player
/ Takes the hand passed to the function and finds the card that the players wish to exchange
/ Then passes this card and the player's pawn to the function in role card
/ Upon success, the playerview is notified
*********************************************************************************************/
int Player::share_knowledge( vector<PlayerCard> givingHand, int exchangeCard) {
	PlayerCard givingCard = givingHand[exchangeCard];
	int success = role->shareKnowledge(playerPawn, givingCard);
	if (success > 0)
		notify(); //If the action worked, notify all the observers
	return success;
}

/**************************************************************************
/ Function to cure a disease
/ Finds all indicated cards that the player wishes to pass to the function
/ Then passes all cards plus the player's pawn to the function in role card
/ Upon success, the playerview is notified
*****************************************************************************/
int Player::discover_cure(vector<int> cure) {
	vector<PlayerCard> cureCards;
	for (int i = 0; i < cure.size(); i++) {
		cureCards.push_back(cardsInHand[cure[i]]);
	}
	int success = role->discoverCure(playerPawn, cureCards);
	if (success > 0)
		notify(); //If the action worked, notify all the observers
	return success;
}