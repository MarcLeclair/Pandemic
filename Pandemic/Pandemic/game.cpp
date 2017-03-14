#include "game.h"
using namespace std;

Game::Game() {

}
Game::Game(int numberPlayers) {
	map = Map();
	map.load_starting_map();
	rolelist.push_back(Medic());
	rolelist.push_back(Researcher());
	rolelist.push_back(OperationsExpert());
	rolelist.push_back(Scientist());
	rolelist.push_back(ContingencyPlanner());
	rolelist.push_back(QuarantineSpecialist());
	rolelist.push_back(Dispatcher());
	for (int i = 0; i < numberPlayers; i++) {
		Player player = Player(i, &rolelist[i]);
		this->playerlist.push_back(player);
		map.addPawn(player.getMyPawn());
	}
	//initialize both decks of cards??
}

void Game::StartGame() {
	int currentPlayersId = 0;
	while (!(this->isGameOver())) {
		performPlayersTurn(currentPlayersId%playerlist.size());
		currentPlayersId++;
	}

}

int Game::pollForCity() {
	int newCityID = 0;
	cin >> newCityID;
	return newCityID;
}

int Game::pollForCards(int pId) {
	int cardIndex = 0;
	playerlist[pId].displayCardsInHand();
	cin >> cardIndex;
	return cardIndex;
}

int Game::pollForRetry() {
	int redo = 1;
	cout << "Oops! Looks like your action didn't work. Press 0 to retry the action, or 1 to pick another action." << endl;
	cin >> redo;
	return redo;
}


void Game::performPlayersTurn(int pId) {
	playerlist[pId].setActions(4);
	int success = 0;
	int redo = 1;
	while (playerlist[pId].getAction() > 0 && redo == 1) {
		//Preliminary initializations
		int action = playerlist[pId].requestAction();
		int newCityID;
		int cardIndex;
		vector<int> cure;
		int playerID;
		vector<PlayerCard> receivingHand;


		//These initializations are important for the share knowledge function
		int currentCityID = playerlist[pId].getCurrentLocation();
		City currentCity = map.getCityByID(currentCityID);
		vector<int> pawnsInCity = currentCity.pawnList;

		do {
			switch (action) {
			case 1: //drive
				cout << "You chose to drive." << endl;

				do {
					cout << "Please choose a city corresponding to the city you want to drive to." << endl;
					newCityID = pollForCity();
				} while (newCityID < 1 || newCityID > 48);
				success = playerlist[pId].drive(newCityID);
				break;

			case 2: //direct flight
				cout << "You chose to take a direct flight." << endl;
				do {
					cout << "Please choose a city card in your hand corresponding to the city you want to fly to." << endl;
					cardIndex = pollForCards(pId);
				} while (cardIndex > playerlist[pId].getNumOfCards() || cardIndex < 1);

				success = playerlist[pId].direct_flight(cardIndex);
				break;
			case 3: //charter flight
				cout << "You chose to take a charter flight." << endl;

				do { //Poll the user for the city they'd like to go to, and the city card they'd like to discard
					cout << "Please choose the city you would like to fly to" << endl;
					newCityID = pollForCity();
					cout << "Please choose the city card you'd like to discard to make this flight." << endl;
					cardIndex = pollForCards(pId);
				} while (cardIndex > playerlist[pId].getNumOfCards() || cardIndex < 1 || newCityID >48 || newCityID < 1);

				success = playerlist[pId].charter_flight(cardIndex, newCityID);
				break;
			case 4: //shuttle flight
				cout << "You chose to take a shuttle flight." << endl;
				do {
					cout << "Please choose the city you'd like to fly to." << endl;
					newCityID = pollForCity();
				} while (newCityID > 48 || newCityID < 1);

				success = playerlist[pId].shuttle_flight(newCityID);
				break;
			case 5: //build research station
				do {
					cout << "Please choose the city card corresponding to the city that you are in" << endl;
					cardIndex = pollForCards(pId);
				} while (cardIndex > playerlist[pId].getNumOfCards() || cardIndex < 1);

				success = playerlist[pId].build_research_station(cardIndex);
				break;
			case 6: //treat disease
				cout << "You chose to treat a disease!\nTreating disease in current city." << endl;
				success = playerlist[pId].treat_disease();
				break;
			case 7: //share knowledge
				cout << "You chose to share knowledge!" << endl;
				do {
					cout << "Which player would you like to share knowledge with?" << endl;
					cin >> playerID;
				} while (playerID > playerlist.size() || playerID < 1);

				if (find(pawnsInCity.begin(), pawnsInCity.end(), playerID) == pawnsInCity.end()) {
					cout << "Cannot share knowledge, player " << playerID << " is not in the current location with you." << endl;
					redo = pollForRetry();
					break;
				}
				else {
					receivingHand = playerlist[playerID].getHand();
				}

				do {
					cout << "Which card would you like to give to the player?" << endl;
					cardIndex = pollForCards(pId);
				} while (cardIndex < 1 || cardIndex > playerlist[pId].getNumOfCards());
				success = playerlist[pId].share_knowledge(receivingHand, cardIndex);

				//Balance the receiving player's hand, in case they've acquired too many cards
				playerlist[playerID].balanceHand();

				break;
			case 8: //cure a disease
				cout << "You chose to cure a diease." << endl;
				int count = 0;
				while (count < 5) {
					cout << "Indicate card " << count + 1 << " of cure cards." << endl;
					do {
						cardIndex = pollForCards(pId);
					} while (cardIndex > playerlist[pId].getNumOfCards() || cardIndex < 1);
					cure.push_back(cardIndex);
				}
				success = playerlist[pId].discover_cure(cure);
				if (success != 0) { //If it worked, we need to discard the cards used
					for (int i = 0; i < cure.size(); i++) {
						playerlist[pId].discardCard(cure[i]);
					}
					cardIndex = -1;
				}
				break;
			case 9:
				//This case can constitute a different action, as Contingency Planner, Operations Expert, and Dispatcher all have different extra actions
				if (playerlist[pId].getRole() == "Operations Expert") {//We are going to execute a special move from a city with a researc station to any city
					cout << "You chose the Operations Expert's special move!" << endl;
					do {
						cout << "Please indicate a city card you wish to discard to make this move. Note, it does not have to match the city you are moving to!" << endl;
						cardIndex = pollForCards(pId);
					} while (cardIndex > playerlist[pId].getNumOfCards() || cardIndex < 1);

					RoleCard* rc = playerlist[pId].getRoleCard();
					PlayerCard moveCard = playerlist[pId].getHand().at(cardIndex);
					//We are casting the role to an OperationsExpert type because we know it is an Operations Expert
					success = dynamic_cast<OperationsExpert&>(*rc).specialOperationsMove(playerlist[pId].getMyPawn(), moveCard);
				}

				else if (playerlist[pId].getRole() == "Contingency Planner") { //We are going to pick up a discarded Event card
					cout << "You chose the Contingency Planner's special move!" << endl;
					//Since we do not have a discard pile at the moment, we will pass any arbitrary card to the function
					cout << "Passing an arbitrary PlayerCard to the function " << endl;
					PlayerCard* arbitrary = new PlayerCard("Event", 0, "Random Special Event");
					RoleCard* rc = playerlist[pId].getRoleCard();
					success = dynamic_cast<ContingencyPlanner&>(*rc).pickUpSpecialEvent(arbitrary);
				}

				else if (playerlist[pId].getRole() == "Dispatcher") { //We will be moving any other pawn as if it is our own
					cout << "You chose the Dispatcher's special move!" << endl;
					do {
						cout << "Which player's pawn would you like to move? " << endl;
						cin >> playerID;
					} while (playerID > playerlist.size() || playerID < 0);

					do {
						cout << "Please choose a city with another player in it to travel to." << endl;
						newCityID = pollForCity();
					} while (newCityID > 48 || newCityID < 1);

					RoleCard* rc = playerlist[pId].getRoleCard();
					success = dynamic_cast<Dispatcher&>(*rc).specialMoveAnotherPlayer(playerlist[playerID].getMyPawn(), newCityID);
				}
				else {
					cout << "Your role does not have any special moves." << endl;
					redo = pollForRetry();
					break;
				}
				if (success != 0 && playerlist[pId].getRole() == "Contingency Planner") {
					//We need to delete the special event
					RoleCard* rc = playerlist[pId].getRoleCard();
					dynamic_cast<ContingencyPlanner&>(*rc).discardSpecialEvent();
				}
				break;
			}

			if (success == 0) { //If the action didn't work
				redo = pollForRetry();
			}
		} while (redo == 0);

		if (success != 0) {
			playerlist[pId].useAction();
			if (cardIndex) playerlist[pId].discardCard(cardIndex);
		}
	}

	for (int i = 0; i < 2; i++)
		playerlist[pId].drawCard;

	//Draw epidemic cards		
}


bool Game::isGameOver() {
	//add checks here
	return false;
}


