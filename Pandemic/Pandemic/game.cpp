#include "game.h"
using namespace std;

Game::Game() {

}
Game::Game(int numberPlayers) {
	map = Map();
	map.load_starting_map();
	rolelist.push_back(new Medic(&map));
	rolelist.push_back(new Researcher(&map));
	rolelist.push_back(new OperationsExpert(&map));
	rolelist.push_back(new Scientist(&map));
	rolelist.push_back(new ContingencyPlanner(&map));
	rolelist.push_back(new QuarantineSpecialist(&map));
	rolelist.push_back(new Dispatcher(&map));
	for (int i = 0; i < numberPlayers; i++) {
		Player* player = new Player(i, rolelist[i], &map);
		this->playerlist.push_back(player);
		map.addPawn(player->getMyPawn());
	}
	//load_players();
	//initialize both decks of cards??

	DeckOfCard<PlayerCard>* deck = instantiatePlayerCards(map, 4);
	Infection InfectionDeck = Infection(0);
	InfectionDeck.makeDeck();
	InfectionDeck.startInfect(map);
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
	playerlist[pId]->displayCardsInHand();
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
	playerlist[pId]->setActions(4);
	int success = 0;
	int redo = 1;
	while (playerlist[pId]->getAction() > 0 && redo == 1) {
		//Preliminary initializations
		int action = playerlist[pId]->requestAction();
		int newCityID;
		int count = 0;
		int cardIndex;
		vector<int> cure;
		int playerID;
		vector<PlayerCard> receivingHand;


		//These initializations are important for the share knowledge function
		int currentCityID = playerlist[pId]->getCurrentLocation();
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
				success = playerlist[pId]->drive(newCityID);
				break;

			case 2: //direct flight
				cout << "You chose to take a direct flight." << endl;
				do {
					cout << "Please choose a city card in your hand corresponding to the city you want to fly to." << endl;
					cardIndex = pollForCards(pId);
				} while (cardIndex > playerlist[pId]->getNumOfCards() || cardIndex < 1);

				success = playerlist[pId]->direct_flight(cardIndex);
				break;
			case 3: //charter flight
				cout << "You chose to take a charter flight." << endl;

				do { //Poll the user for the city they'd like to go to, and the city card they'd like to discard
					cout << "Please choose the city you would like to fly to" << endl;
					newCityID = pollForCity();
					cout << "Please choose the city card you'd like to discard to make this flight." << endl;
					cardIndex = pollForCards(pId);
				} while (cardIndex > playerlist[pId]->getNumOfCards() || cardIndex < 1 || newCityID >48 || newCityID < 1);

				success = playerlist[pId]->charter_flight(cardIndex, newCityID);
				break;
			case 4: //shuttle flight
				cout << "You chose to take a shuttle flight." << endl;
				do {
					cout << "Please choose the city you'd like to fly to." << endl;
					newCityID = pollForCity();
				} while (newCityID > 48 || newCityID < 1);

				success = playerlist[pId]->shuttle_flight(newCityID);
				break;
			case 5: //build research station
				do {
					cout << "Please choose the city card corresponding to the city that you are in" << endl;
					cardIndex = pollForCards(pId);
				} while (cardIndex > playerlist[pId]->getNumOfCards() || cardIndex < 1);

				success = playerlist[pId]->build_research_station(cardIndex);
				break;
			case 6: //treat disease
				cout << "You chose to treat a disease!\nTreating disease in current city." << endl;
				success = playerlist[pId]->treat_disease();
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
					receivingHand = playerlist[playerID]->getHand();
				}

				do {
					cout << "Which card would you like to give to the player?" << endl;
					cardIndex = pollForCards(pId);
				} while (cardIndex < 1 || cardIndex > playerlist[pId]->getNumOfCards());
				success = playerlist[pId]->share_knowledge(receivingHand, cardIndex);

				//Balance the receiving player's hand, in case they've acquired too many cards
				playerlist[playerID]->balanceHand();

				break;
			case 8: //cure a disease
				cout << "You chose to cure a diease." << endl;
				while (count < 5) {
					cout << "Indicate card " << count + 1 << " of cure cards." << endl;
					do {
						cardIndex = pollForCards(pId);
					} while (cardIndex > playerlist[pId]->getNumOfCards() || cardIndex < 1);
					cure.push_back(cardIndex);
				}
				success = playerlist[pId]->discover_cure(cure);
				if (success != 0) { //If it worked, we need to discard the cards used
					for (int i = 0; i < cure.size(); i++) {
						playerlist[pId]->discardCard(cure[i]);
					}
					cardIndex = -1;
				}
				break;
			case 9:
				//This case can constitute a different action, as Contingency Planner, Operations Expert, and Dispatcher all have different extra actions
				if (playerlist[pId]->getRole() == "Operations Expert") {//We are going to execute a special move from a city with a researc station to any city
					cout << "You chose the Operations Expert's special move!" << endl;
					do {
						cout << "Please indicate a city card you wish to discard to make this move. Note, it does not have to match the city you are moving to!" << endl;
						cardIndex = pollForCards(pId);
					} while (cardIndex > playerlist[pId]->getNumOfCards() || cardIndex < 1);

					RoleCard* rc = playerlist[pId]->getRoleCard();
					PlayerCard moveCard = playerlist[pId]->getHand().at(cardIndex);
					//We are casting the role to an OperationsExpert type because we know it is an Operations Expert
					success = dynamic_cast<OperationsExpert&>(*rc).specialOperationsMove(playerlist[pId]->getMyPawn(), moveCard);
				}

				else if (playerlist[pId]->getRole() == "Contingency Planner") { //We are going to pick up a discarded Event card
					cout << "You chose the Contingency Planner's special move!" << endl;
					//Since we do not have a discard pile at the moment, we will pass any arbitrary card to the function
					cout << "Passing an arbitrary PlayerCard to the function " << endl;
					PlayerCard* arbitrary = new PlayerCard("Event", 0, "Random Special Event");
					RoleCard* rc = playerlist[pId]->getRoleCard();
					success = dynamic_cast<ContingencyPlanner&>(*rc).pickUpSpecialEvent(arbitrary);
				}

				else if (playerlist[pId]->getRole() == "Dispatcher") { //We will be moving any other pawn as if it is our own
					cout << "You chose the Dispatcher's special move!" << endl;
					do {
						cout << "Which player's pawn would you like to move? " << endl;
						cin >> playerID;
					} while (playerID > playerlist.size() || playerID < 0);

					do {
						cout << "Please choose a city with another player in it to travel to." << endl;
						newCityID = pollForCity();
					} while (newCityID > 48 || newCityID < 1);

					RoleCard* rc = playerlist[pId]->getRoleCard();
					success = dynamic_cast<Dispatcher&>(*rc).specialMoveAnotherPlayer(playerlist[playerID]->getMyPawn(), newCityID);
				}
				else {
					cout << "Your role does not have any special moves." << endl;
					redo = pollForRetry();
					break;
				}
				if (success != 0 && playerlist[pId]->getRole() == "Contingency Planner") {
					//We need to delete the special event
					RoleCard* rc = playerlist[pId]->getRoleCard();
					dynamic_cast<ContingencyPlanner&>(*rc).discardSpecialEvent();
				}
				break;
			}

			if (success == 0) { //If the action didn't work
				redo = pollForRetry();
			}
		} while (redo == 0);

		if (success != 0) {
			playerlist[pId]->useAction();
			if (cardIndex) playerlist[pId]->discardCard(cardIndex);
		}
	}

	/*for (int i = 0; i < 2; i++)
		playerlist[pId].drawCard;*/

	//Draw epidemic cards		
}

void Game::save_players() {
	ofstream playerFile;
	playerFile.open("players.csv", ofstream::out | ofstream::trunc);
	for (int i = 0; i < playerlist.size(); i++) {
		playerFile << playerlist[i]->getPlayerID() << ",";
		playerFile << playerlist[i]->getRole() << ",";
		playerFile << playerlist[i]->getCurrentLocation() << ",";
		playerFile << playerlist[i]->getNumOfCards() << endl;


		for (int j = 0; j < playerlist[i]->getNumOfCards(); j++) {
			string cardType = playerlist[i]->getHand().at(i).getType();
			playerFile << cardType << ",";
			if (cardType == "City") {
				playerFile << playerlist[i]->getHand().at(i).getCityId() << ",";
				playerFile << playerlist[i]->getHand().at(i).getValue() << ",";
				playerFile << playerlist[i]->getHand().at(i).getColour()  << endl;
			}
			if (cardType == "Event") {
				playerFile << playerlist[i]->getHand().at(i).getCityId() << ",";
				playerFile << playerlist[i]->getHand().at(i).getValue() << endl;
			}
		}
	}
	cout << "Players saved successfully!" << endl;
	playerFile.close();
}

void Game::load_players() {
	string line;
	ifstream playerFile("players.csv");
	if (playerFile.is_open())
	{
		while (getline(playerFile, line))
		{
			vector<string> vals;
			string s = line;
			int position = 0;
			while ((position = s.find(",")) != string::npos) {
				vals.push_back(s.substr(0, position));
				s.erase(0, position + 1);
			}
			vals.push_back(s.substr(0, position));

			//Read in the player's ID
			int pId = stoi(vals[0]);
			cout << pId << endl;

			//Load the player's role
			string role = vals[1];
			cout << role << endl;
			
			//Load the player's last location
			int currentLocation = stoi(vals[2]);
			cout << currentLocation << endl;

			//Load the amount of cards the player was holding
			int numOfCards = stoi(vals[3]);
			cout << numOfCards << endl;

			vector<string> cardVals;
			vector<PlayerCard> hand;
			for (int i = 0; i < numOfCards; i++) {
				position = 0;
				//Read in one line, for a card
				while ((position = s.find(",")) != string::npos) {
					cardVals.push_back(s.substr(0, position));
					s.erase(0, position + 1);
				}
				cardVals.push_back(s.substr(0, position));

				string cardType = cardVals[i];
				if (cardType == "City") {
					//If it's a city card, load it one way (by including the color)
					PlayerCard* card = new PlayerCard(cardType, stoi(cardVals[i + 1]), cardVals[i + 2], cardVals[i + 3]);
					i += 3;
					hand.push_back(*card);
				}
				else {
					//if it's a player card, load it with other values
					PlayerCard* card = new PlayerCard(cardType, stoi(cardVals[i + 1]), cardVals[i+2]);
					i+= 2;
					hand.push_back(*card);
				}
			}

			RoleCard* rc;
			if (role == "Medic") rc = new Medic(&map);
			else if (role == "Contingency Planner") rc = new ContingencyPlanner(&map);
			else if (role == "Researcher") rc = new Researcher(&map);
			else if (role == "Dispatcher") rc = new Dispatcher(&map);
			else if (role == "Operations Expert") rc = new OperationsExpert(&map);
			else if (role == "Quarantine Specialist") rc = new QuarantineSpecialist(&map);
			else rc = new Scientist(&map);

			Player* player1 = new Player(pId, rc, &map);

			for (int i = 0; i < numOfCards; i++) {
				player1->drawCard(hand[i]);
			}
			//set the player's location to their previous location, as the constructor sets them back at the start by default
			player1->getMyPawn()->set_location(currentLocation);

			playerlist.push_back(player1);
		}
		playerFile.close();
	}
}

void Game::displayPlayers() {
	for (int i = 0; i < playerlist.size(); i++) {
		cout << "Player " << playerlist[i]->getPlayerID() << " is a ";
		cout << playerlist[i]->getRole() << " with a ";
		cout << playerlist[i]->getPawnColor() << " pawn." << endl;
	}
}

bool Game::isGameOver() {
	//add checks here
	return false;
}

DeckOfCard<PlayerCard>* Game::instantiatePlayerCards(Map map, int numOfEpidemic) {

	vector<PlayerCard> playerCards;
	vector<City> temp = map.getCities();
	for (City city : temp) {
		int id = city.id;
		string name = city.name;
		string colour = "none";

		PlayerCard cardToPush = PlayerCard("city", id, name, colour);
		playerCards.push_back(cardToPush);
	}
	DeckOfCard<PlayerCard>* playerDeck = new DeckOfCard<PlayerCard>(playerCards);
	
	return playerDeck;
}
int main() {
	Game* game = new Game(2);
	game->displayPlayers();
	vector<Player*> players = game->getPlayerlist();
	cout << players[0]->getCurrentLocation() << endl;
	//game->getMap().display_information();
	players[1]->drive(26);

	system("PAUSE");
	delete game;
	return 0;
}