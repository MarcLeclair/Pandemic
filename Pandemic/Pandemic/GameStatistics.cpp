/********************************************************************
/ This class is a concrete implementation of an observer on a Game
/ GameStatistics objects will be updated whenever the Game object that
/ they observe notifies them of an update.
/ They hold a single Game object to which they observe
/ Thus, each Game should have its own observer attached.
*********************************************************************/


#include "GameStatistics.h"

/**********************************
/ Default constructor
/ instatiates nothing in particular
************************************/
GameStatistics::GameStatistics() {

};

/******************************************************************
/ Constructor to instantiate an observer with a connected game
/ Upon instantiation, it'll take in a Game and attach itself
*******************************************************************/
GameStatistics::GameStatistics(Game* pl) {
	game = pl;
	pl->attach(this);
}

/****************************************************
/ Copy Constructor
/ Will make a deep copy of the Game attached
*****************************************************/
GameStatistics::GameStatistics(const GameStatistics& pv) {
	game = new Game(*pv.game);
	game->attach(this);
}

/**********************************
/ Overloaded assignment operator
***********************************/
const GameStatistics& GameStatistics::operator=(const GameStatistics& pv) {
	if (&pv != this) {
		delete game;

		game = new Game(*pv.game);
		game->attach(this);
	}
	return *this;
}

/***************************************************************
/ Destructor for the Observer
/ Upon going out of scope, it'll detach itself from its game
/ This still leaves the game responsible for deleting itself
****************************************************************/
GameStatistics::~GameStatistics() {
	game->detach(this);
}

/*******************************************************************
/ This function is called by the attached game when it changes
/ The GameStatistics will then get all the updated info from Game
/ and display it to the user using its display function
********************************************************************/
void GameStatistics::update() {
	displayGame();
}

/***************************************************************************************************
/ Functio to display the Game's information when something about their state is changed
/ Includes information about their pawn, location, role, how many actions are left in their turn
/ Also outputs their hand of cards
****************************************************************************************************/
void GameStatistics::displayGame() {
	/*cout << "\nDisplaying Game " << game->getGameID() << "'s status: " << endl;


	//1) Pawn information
	cout << "    Game is a " << game->getRole() << " with a " << game->getPawnColor() << " pawn in Location " << game->getCurrentLocation() << endl;
	cout << "    Game has " << game->getAction() << " moves left.";
	//3 GameCards information
	cout << "    Game's current hand: " << endl;
	game->displayCardsInHand();
	cout << endl;*/
}

Game* GameStatistics::getGame() {
	return this->game;
}