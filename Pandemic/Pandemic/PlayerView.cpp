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

void PlayerView::displayPlayer() {
	cout << "\nDisplaying Player " << subject->getPlayerID() << "'s status: " << endl;
	
	
	cout << "    Player has a " << subject->getPawnColor() << " pawn at location "<< subject->getCurrentLocation() << endl;
	cout << "    Player is a " << subject->getRole() << "." << endl;
	cout << "    Player has " << subject->getAction()-1 << " actions remaining." << endl;

	cout << "    Player's hand : " << endl;
	subject->displayCardsInHand();
	cout << endl;
}