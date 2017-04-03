/********************************************************************
/ This class is a concrete implementation of an observer on a Player
/ PlayerView objects will be updated whenever the Player object that
/ they observe notifies them of an update.
/ They hold a single Player object to which they observe
/ Thus, each player should have its own observer attached.
*********************************************************************/


#include "PlayerView.h"

/**********************************
/ Default constructor
/ instatiates nothing in particular
************************************/
PlayerView::PlayerView() {

};

/******************************************************************
/ Constructor to instantiate an observer with a connected subject
/ Upon instantiation, it'll take in a player and attach itself
*******************************************************************/
PlayerView::PlayerView(Player* pl) {
	subject = pl;
	pl->attach(this);
}

/***************************************************************
/ Destructor for the Observer
/ Upon going out of scope, it'll detach itself from its subject
/ This still leaves the subject responsible for deleting itself
****************************************************************/
PlayerView::~PlayerView() {
	subject->detach(this);
}

/*******************************************************************
/ This function is called by the attached subject when it changes
/ The playerview will then get all the updated info from Player
/ and display it to the user using its display function
********************************************************************/
void PlayerView::update() {
	displayPlayer();
}

/***************************************************************************************************
/ Functio to display the player's information when something about their state is changed
/ Includes information about their pawn, location, role, how many actions are left in their turn
/ Also outputs their hand of cards
****************************************************************************************************/
void PlayerView::displayPlayer() {
	cout << "\nDisplaying Player " << subject->getPlayerID() << "'s status: " << endl;
	
	
	//1) Pawn information
	cout << "    Player is a " << subject->getRole() << " with a " << subject->getPawnColor() << " pawn in Location " << subject->getCurrentLocation() << endl;
	cout << "    Player has " << subject->getAction() << " moves left.";
	//3 PlayerCards information
	cout << "    Player's current hand: " << endl;
	subject->displayCardsInHand();
	cout << endl;
}