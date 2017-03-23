
#include "Player.h"
#include <string>
#include <iostream>
#include "ReferenceCard.h"
#include "RoleCard.h"
#include "PlayerCard.h"

using namespace std;

Player::Player() {
}


Player::Player(int pid, RoleCard* rolec, Map* mp) : Subject()
{
	playerID = pid;
	ReferenceCard* myReference = new ReferenceCard(mp);
	setReferenceCard(*myReference);

	setRoleCard(rolec);

	Pawn* myPawn = new Pawn(role->getRoleColor(), playerID);
	setMyPawn(*myPawn);

	//All players start out in Bridge of Eldin. This corresponds to cityID 0
	getMyPawn()->set_location(1);
}

//Copy Constructor
Player::Player(const Player& plr) : Subject(){
	playerID = plr.playerID;
	role = plr.role;

	ReferenceCard* tempRef = new ReferenceCard(plr.refcard);
	refcard = *tempRef;

	Pawn* tempPawn = new Pawn(plr.playerPawn);
	playerPawn = *tempPawn;

	for (PlayerCard pc : plr.cardsInHand) {
		PlayerCard* tempPC = new PlayerCard(pc);
		cardsInHand.push_back(*tempPC);
	}
}

//Don't need to explicitly delete the objects being held as they are allocated on the heap, only the RoleCard, which is a pointer
Player::~Player()
{
	delete role;
	(getHand()).clear();
}

/***************************************************************************
/ Function to balance the player's hand when they've drawn too many cards
/ Will result in the chosen card being discarded from the player's hand
****************************************************************************/
void Player::balanceHand() {
	if (numOfCards > maxCardsInHand) {
		cout << "\nToo many cards in hand, please choose one to discard." << endl;
		displayCardsInHand();

		int cardToDiscard;
		cout << "Card to discard (number): " << endl;
		cin >> cardToDiscard;

		while (cardToDiscard > cardsInHand.size() || cardToDiscard < 1) {
			cout << "Invalid card number. Please try again." << endl;
			cin >> cardToDiscard;
		}

		discardCard((cardToDiscard - 1));

		setNumOfCards();
	}
}

/************************************************************************************************
/ Function to draw a player card from the deck
/ If the player draws a card and ends up with more than the allowed number of cards in his hand,
/ he will automtically be asked to discard a card
************************************************************************************************/
void Player::drawCard(PlayerCard plc) {
	cardsInHand.push_back(plc);
	setNumOfCards();
	balanceHand();
}

/********************************************************************
/ Function to display all of the cards held
/ Iterates through the player's hand and gets the title of the card
*********************************************************************/
void Player::displayCardsInHand() {
	int cardNum = 1;
	for (PlayerCard card : cardsInHand) {
		cout << "\t" << cardNum << ". " << card.getType() << " card "<< card.getColour() << ": " << card.getValue() << "(" << card.getCityId() << ")" <<endl;
		cardNum++;
	}
}

/*******************************************************************************
/ Function to remove a card from the player's hand
/ Simply accesses the player's hand and deletes the card at the index indicated
*******************************************************************************/
void Player::discardCard(int disc) {
	cardsInHand.erase(cardsInHand.begin() + disc);
	setNumOfCards();
}

/**********************************************************************
/ Function to output the possible actions that the player can execute
/ Corresponds to the actions found in the Reference Card class
**********************************************************************/
void Player::outputPossibleActions() {
	vector<string> allActions = refcard.getAllActions();
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
	return newAction;
}

void Player::display_player_info() {
	cout << "\nPlayer " << getPlayerID() << "'s info: " << endl;

	//1) Pawn information
	cout << "    Player is a " << getRole() << " in Location " << getCurrentLocation() << endl;

	//3 PlayerCards information
	cout << "    Player's hand status: " << endl;
	displayCardsInHand();

}

/**************************************************************
/ Function to execute the drive function on this player's pawn
***************************************************************/
int Player::drive(int newCityID) {
	int success= role->drive(&playerPawn, newCityID);
	if (success > 0)
		notify(); //If the action worked, notify all the observers
	return success;
}

/********************************************************************
/ Function to execute a direct flight function on this player's pawn
*********************************************************************/
int Player::direct_flight(int cardIndex) {
	PlayerCard destination = cardsInHand[cardIndex];
	int success =  role->directFlight(&playerPawn, destination);
	if (success > 0)
		notify(); //If the action worked, notify all the observers
	return success;
}

/*********************************************************
/ Function to execute a charter flight to another city
*********************************************************/
int Player::charter_flight(int cardIndex, int newCityID) {
	PlayerCard destination = cardsInHand[cardIndex];
	int success = role->charterFlight(&playerPawn, destination, newCityID);
	if (success > 0)
		notify(); //If the action worked, notify all the observers
	return success;
}

/******************************************************************************
/ Function to execute a shuttle flight to another city with a research station
*******************************************************************************/
int Player::shuttle_flight(int newCityID) {
	int success = role->shuttleFlight(&playerPawn, newCityID);
	if (success > 0)
		notify(); //If the action worked, notify all the observers
	return success;
}

/***********************************************************
/ Function to build a research station in your current city
************************************************************/
int Player::build_research_station(int cardIndex) {
	PlayerCard currentCity = cardsInHand[cardIndex];
	int success = role->buildResearchStation(&playerPawn, currentCity);
	if (success > 0)
		notify(); //If the action worked, notify all the observers
	return success;
}

/******************************************************
/ Function to treat a disease cube in the current city
*******************************************************/
int Player::treat_disease() {
	int success = role->treatDisease(&playerPawn);
	if (success > 0)
		notify(); //If the action worked, notify all the observers
	return success;
}

/************************************************************
/ Function to give one of your city cards to another player
*************************************************************/
int Player::share_knowledge( vector<PlayerCard> receivingHand, int exchangeCard) {
	PlayerCard givingCard = cardsInHand[exchangeCard];
	int success = role->shareKnowledge(&playerPawn, givingCard);
	if (success > 0)
		notify(); //If the action worked, notify all the observers
	return success;
}

/******************************
/ Function to cure a disease
******************************/
int Player::discover_cure(vector<int> cure) {
	vector<PlayerCard> cureCards;
	for (int i = 0; i < cure.size(); i++) {
		cureCards.push_back(cardsInHand[cure[i]]);
	}
	int success = role->discoverCure(&playerPawn, cureCards);
	if (success > 0)
		notify(); //If the action worked, notify all the observers
	return success;
}