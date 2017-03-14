
#include "Player.h"
#include <string>
#include <iostream>
#include "ReferenceCard.h"
#include "RoleCard.h"
#include "PlayerCard.h"

using namespace std;

Player::Player() {
}


Player::Player(int pid, RoleCard* rolec)
{
	playerID = pid;
	ReferenceCard* myReference = new ReferenceCard();
	setReferenceCard(*myReference);

	setRoleCard(rolec);

	Pawn* myPawn = new Pawn(role->getRoleColor(), playerID);
	setMyPawn(*myPawn);

	//All players start out in Bridge of Eldin. This corresponds to cityID 0
	getMyPawn()->set_location(1);
}

//Copy Constructor
Player::Player(const Player& plr) {
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
		cout << "Too many cards in hand, please choose one to discard." << endl;
		displayCardsInHand();

		int cardToDiscard;
		cout << "Card to discard (number): " << endl;
		cin >> cardToDiscard;

		while (cardToDiscard > cardsInHand.size() - 1 || cardToDiscard < 1) {
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
		cout << "\t" << cardNum << ". " << card.getType() << " card: " << card.getValue() << endl;
		cardNum++;
	}
}

/*******************************************************************************
/ Function to remove a card from the player's hand
/ Simply accesses the player's hand and deletes the card at the index indicated
*******************************************************************************/
void Player::discardCard(int disc) {
	cardsInHand.erase(cardsInHand.begin() + disc);
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
	cout << "Specify by number which action you wish to perform:" << endl;
	outputPossibleActions();
	int newAction;
	cin >> newAction;
	while (newAction > refcard.getAllActions().size()) {
		cout << "Invalid action ID. Please Try Again." << endl;
	}
	return newAction - 1;
}

/**************************************************************
/ Function to execute the drive function on this player's pawn
***************************************************************/
int Player::drive(int newCityID) {
	return role->drive(&playerPawn, newCityID);
}

/********************************************************************
/ Function to execute a direct flight function on this player's pawn
*********************************************************************/
int Player::direct_flight(int cardIndex) {
	PlayerCard destination = cardsInHand[cardIndex];
	return role->directFlight(&playerPawn, destination);
}

/*********************************************************
/ Function to execute a charter flight to another city
*********************************************************/
int Player::charter_flight(int cardIndex, int newCityID) {
	PlayerCard destination = cardsInHand[cardIndex];
	return role->charterFlight(&playerPawn, destination, newCityID);
}

/******************************************************************************
/ Function to execute a shuttle flight to another city with a research station
*******************************************************************************/
int Player::shuttle_flight(int newCityID) {
	return role->shuttleFlight(&playerPawn, newCityID);
}

/***********************************************************
/ Function to build a research station in your current city
************************************************************/
int Player::build_research_station(int cardIndex) {
	PlayerCard currentCity = cardsInHand[cardIndex];
	return role->buildResearchStation(&playerPawn, currentCity);
}

/******************************************************
/ Function to treat a disease cube in the current city
*******************************************************/
int Player::treat_disease() {
	return role->treatDisease(&playerPawn);
}

/************************************************************
/ Function to give one of your city cards to another player
*************************************************************/
int Player::share_knowledge( vector<PlayerCard> receivingHand, int exchangeCard) {
	PlayerCard givingCard = cardsInHand[exchangeCard];
	return role->shareKnowledge(&playerPawn, givingCard, receivingHand);
}

/******************************
/ Function to cure a disease
******************************/
int Player::discover_cure(vector<int> cure) {
	vector<PlayerCard> cureCards;
	for (int i = 0; i < cure.size(); i++) {
		cureCards.push_back(cardsInHand[cure[i]]);
	}
	return role->discoverCure(&playerPawn, cureCards);
}



/*******************************************************************************************
/ Function to perform an action
/ Will get the user's requested action and call this action from the reference card class
/ Functions are called from the Role card classes as these are subclasses of reference cards
/ Through polymorphism, roles will execute certain functions differently
********************************************************************************************/
int Player::performAction() {
	int action = requestAction();
	int success = 0;
	int redo = 0;
	int newCityID;
	int cardIndex;
	vector<int> cure;

	//While the reference card should be executing these commands, the role cards are the ones that do the job
	//This is due to the fact that the role cards have special implementations of some of the functions defined in ReferenceCard
	ReferenceCard* ref = getRoleCard();
	switch (action) {
	case 1: //drive
		do {
			//Poll the user for the city they want to drive to
			cout << "Please indicate the city ID you wish to drive to." << endl;
			cin >> newCityID;
			success = ref->drive(getMyPawn(), newCityID);

			if (success == 0) { //If the drive didn't work, i.e. if the city requested isn't connected
				cout << "Oops! Looks like your action didn't work. Press 0 to retry the action, or 1 to pick another action." << endl;
				cin >> redo;
			}
			else { //if the drive worked, we don't want to retry
				redo = 1;
			}
		} while (redo == 0);
		break;

	case 2: //direct flight
		do {
			do {
				cout << "Please choose the city you wish to fly to." << endl;
				displayCardsInHand();
				cin >> cardIndex;
			} while (cardIndex > cardsInHand.size() - 1 || cardIndex < 1);

			success = ref->directFlight(getMyPawn(), getHand(), cardIndex);

			if (success == 0) { //If the flight didn't work
				cout << "Oops! Looks like your action didn't work. Press 0 to retry the action, or 1 to pick another action." << endl;
				cin >> redo;
			}
			else { //it worked, we don't want to retry
				redo = 1;
			}
		} while (redo == 0);

		break;
	case 3: //charter flight
		do {
			do { //Poll the user for the city they'd like to go to, and the city card they'd like to discard
				cout << "Please choose the city you wish to take a Charter flight to." << endl;
				cin >> newCityID;
				cout << "Please choose the city card you wish to discard." << endl;
				displayCardsInHand();
				cin >> cardIndex;
			} while (cardIndex > cardsInHand.size() - 1 || cardIndex < 1 || newCityID >48 || newCityID < 1);

			success = ref->charterFlight(getMyPawn(), getHand(), cardIndex, newCityID);

			if (success == 0) { //If the action didn't work
				cout << "Oops! Looks like your action didn't work. Press 0 to retry the action, or 1 to pick another action." << endl;
				cin >> redo;
			}
			else { //it worked, we don't want to retry
				redo = 1;
			}
		} while (redo == 0);
		break;
	case 4: //shuttle flight
		do {
			do {
				cout << "Please indicate the city ID you wish to shuttle." << endl;
				cin >> newCityID;
			} while (newCityID > 48 || newCityID < 1);

			success = ref->shuttleFlight(getMyPawn(), newCityID);

			if (success == 0) { //If the action didn't work
				cout << "Oops! Looks like your action didn't work. Press 0 to retry the action, or 1 to pick another action." << endl;
				cin >> redo;
			}
			else { //it worked, we don't want to retry
				redo = 1;
			}
		} while (redo == 0);
		break;
	case 5: //build research station
		do {
			do {
				cout << "Please select the city card for this city. If you are an Operations Expert, choose any card! " << endl;
				displayCardsInHand();
				cin >> cardIndex;
			} while (cardIndex > cardsInHand.size() - 1 || cardIndex < 1);

			success = ref->buildResearchStation(getMyPawn(), getHand(), cardIndex);

			if (success == 0) { //If the action didn't work
				cout << "Oops! Looks like your action didn't work. Press 0 to retry the action, or 1 to pick another action." << endl;
				cin >> redo;
			}
			else { //it worked, we don't want to retry
				redo = 1;
			}
		} while (redo == 0);

		if (success != 0 && getRole() != "Operations Expert") { //if we succeeded and we are not an Operations Expert
			discardCard(cardIndex);
		}
		break;
	case 6: //treat disease
		do {
			cout << "Treating disease in current city." << endl;
			success = ref->treatDisease(getMyPawn());

			if (success == 0) { //If the action didn't work
				cout << "Oops! Looks like your action didn't work. Press 0 to retry the action, or 1 to pick another action." << endl;
				cin >> redo;
			}
			else { //it worked, we don't want to retry
				redo = 1;
			}
		} while (redo == 0);
		break;
	case 7: //share knowledge
		do {
			int playerID;
			Player* receiver;
			vector<PlayerCard> receivingHand;

			cout << "Which player would you like to share knowledge with?" << endl;
			cin >> playerID;

			//This part requires properly implemented City class
			/*if (!(getCurrentLocation().playerIsInCity(playerID))) {
			cout << "Cannot share knowledge, player " << playerID << " is not in the current location with you." << endl;
			}
			else {
			receiver = getCurrentLocation().getPlayer(playerID);
			receivingHand = receiver.getHand();
			}*/

			cout << "Which card would you like to give to the player?" << endl;
			displayCardsInHand();
			cin >> cardIndex;
			success = ref->shareKnowledge(getMyPawn(), getHand(), receivingHand, cardIndex);

			//Balance the receiving player's hand, in case they've acquired too many cards
			//receiver.balanceHand();

			if (success == 0) { //If the action didn't work
				cout << "Oops! Looks like your action didn't work. Press 0 to retry the action, or 1 to pick another action." << endl;
				cin >> redo;
			}
			else { //it worked, we don't want to retry
				redo = 1;
			}
		} while (redo == 0);

		if (success != 0) { //if we succeeded, the giver needs to get rid of the card they gave
			discardCard(cardIndex);
		}
		break;
	case 8: //cure a disease
		do {
			int count = 0;
			while (count < 5) {
				cout << "Indicate card " << count + 1 << " of cure cards." << endl;
				displayCardsInHand();
				cin >> cardIndex;
				cure.push_back(cardIndex);
			}
			success = (*ref).discoverCure(getMyPawn(), getHand(), cure);

			if (success == 0) { //If the action didn't work
				cout << "Oops! Looks like your action didn't work. Press 0 to retry the action, or 1 to pick another action." << endl;
				cin >> redo;
			}
			else { //it worked, we don't want to retry
				redo = 1;
			}
		} while (redo == 0);

		if (success != 0) { //If it worked, we need to discard the cards used
			for (int i = 0; i < cure.size(); i++) {
				discardCard(cure[i]);
			}
		}
		break;
	case 9:
		do {
			//This case can constitute a different action, as Contingency Planner, Operations Expert, and Dispatcher all have different extra actions
			if (getRole() == "Operations Expert") {//We are going to execute a special move from a city with a researc station to any city
				cout << "Please indicate a city card you wish to discard to make this move. Note, it does not have to match the city you are moving to!" << endl;
				displayCardsInHand();
				cin >> cardIndex;
				//We are statically casting the role to an OperationsExpert type because we know it is an Operations Expert
				success = static_cast<OperationsExpert&>(*ref).specialOperationsMove(getMyPawn(), getHand(), cardIndex);
			}
			else if (getRole() == "Contingency Planner") { //We are going to pick up a discarded Event card
														   //Since we do not have a discard pile at the moment, we will pass any arbitrary card to the function
				cout << "Passing an arbitrary PlayerCard to the function " << endl;
				PlayerCard* arbitrary = new PlayerCard("Event", 0, "Random Special Event");
				success = static_cast<ContingencyPlanner&>(*ref).pickUpSpecialEvent(arbitrary);
			}
			else { //We will be moving ourselves to any other city with a player in it
				   //Poll the player for a city
				cout << "Please choose a city with another player in it to travel to." << endl;
				cin >> newCityID;
				success = static_cast<Dispatcher&>(*ref).specialMoveAnotherPlayer(getMyPawn(), newCityID);
			}

			if (success == 0) { //If the action didn't work
				cout << "Oops! Looks like your action didn't work. Press 0 to retry the action, or 1 to pick another action." << endl;
				cin >> redo;
			}
			else { //it worked, we don't want to retry
				redo = 1;
			}
		} while (redo == 0);

		if (success != 0 && getRole() == "Contingency Planner") {
			//We need to delete the special event
			static_cast<ContingencyPlanner&>(*ref).discardSpecialEvent();
		}
		break;
	}

	if (success != 0) {
		useAction();
		return 1;
	}
	else
		return 0;
}