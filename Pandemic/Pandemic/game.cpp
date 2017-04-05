#include "stdafx.h"

#include "..\glew\glew.h"	// include GL Extension Wrangler
#include "..\glfw\glfw3.h"	// include GLFW helper library
#include <stdio.h>

#include "game.h"
using namespace std;

Game::Game() {

}
Game::Game(int numberPlayers) {
	this->hasGameStarted = true;
	map = Map();
	map.load_starting_map();
	deck = instantiatePlayerCards(map, 4);

	rolelist.push_back(new Medic(&map));
	rolelist.push_back(new Researcher(&map));
	rolelist.push_back(new OperationsExpert(&map));
	rolelist.push_back(new Scientist(&map));
	rolelist.push_back(new ContingencyPlanner(&map));
	rolelist.push_back(new QuarantineSpecialist(&map));
	rolelist.push_back(new Dispatcher(&map));

	cout << "Creating role deck" << endl;
	DeckOfCard<RoleCard*>* roledeck = new DeckOfCard<RoleCard*>(rolelist);
	

	for (int i = 0; i < numberPlayers; i++) {
		Player* player = new Player(i, roledeck->getTopCard(), &map);
		PlayerView* playerview = new PlayerView(player);
		for (int j = 0; j < (6 - numberPlayers); j++) {
			PlayerCard card = deck->getTopCard();
			if (card.getType() != "epidemic") {
				player->drawCard(card);
			}
			else {
				j--;
			}
		}
		this->playerlist.push_back(player);
		map.addPawn(player->getMyPawn());
	}
	//load_players();
	//initialize both decks of cards??
	cout << endl;
	InfectionDeck = new Infection(0);
	InfectionDeck->makeDeck();
	InfectionDeck->shuffleInfection();
	InfectionDeck->startInfect(&map);
	cout << endl;
}

void Game::StartGame() {
	int currentPlayersId = 0;
	while (!(this->isGameOver())) {
		SaveGame();
		cout << "\nPlayer " << currentPlayersId%playerlist.size() << "' turn starts." << endl;
		performPlayersTurn(currentPlayersId%playerlist.size());
		cout << "\nPlayer " << currentPlayersId%playerlist.size() << " actions over. Drawing player cards." << endl;
		drawPlayerCards(currentPlayersId%playerlist.size());

		cout << "\nFinished drawn cards. Player " << currentPlayersId%playerlist.size() << "'s hand is now: " << endl;
		playerlist[currentPlayersId%playerlist.size()]->displayCardsInHand();

		cout << "\nDrawing cards finished. Infecting Cities." << endl;
		InfectionDeck->endTurnInfection(&map);
	
		if (currentPlayersId%playerlist.size() == playerlist.size() - 1) {
			cout << "Saving the game" << endl;
			SaveGame();
		}
		currentPlayersId++;
	}

}
void Game::SaveGame() {
	if (hasGameStarted == true) {
		map.save_map();
		save_players();
		save_playerCards();
	}
	else
		cout << "Game has not started" << endl;

}

void Game::LoadGame() {
	map.load_map();
	load_players();

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
	int redo = -1;
	do {
		cout << "\nOops! Looks like your action didn't work. Press 0 to retry the action, or 1 to pick another action." << endl;
		cin >> redo;
	} while (redo != 0 && redo != 1);
	return redo;
}


void Game::performPlayersTurn(int pId) {
	playerlist[pId]->setActions(4);
	int success = 0;
	int redo = 1;
	while (playerlist[pId]->getAction() > 0 && redo == 1) {

		//Preliminary initializations
		City current = map.getCityByID(playerlist[pId]->getCurrentLocation());
		int newCityID;
		int count = 0;
		int cardIndex = -1;
		vector<int> cure;
		int otherPlayerID;

		//These initializations are important for the share knowledge function
		int currentCityID = playerlist[pId]->getCurrentLocation();
		City currentCity = map.getCityByID(currentCityID);
		vector<int> pawnsInCity = currentCity.pawnList;
		int giver = 0;
		int receiver = 0;
		int giverstatus = 0;
		vector<PlayerCard> receivingHand;
		vector<PlayerCard> givingHand;

		int displayaction = -1;
		vector<City> allCities = map.getCities();
		bool redoDisplay = true;
		do {
			cout << endl;
			displayDisplayOptions();
			cin >> displayaction;
			switch (displayaction) {
			case 0:
				redoDisplay = false;
				break;
			case 1:
				currentCity.display_information();
				break;
			case 2:
				for (int i = 0; i < currentCity.connectionsRef.size(); i++) {
					currentCity.connectionsRef[i]->display_information();
				}
				break;
			case 3:
				for (int i = 0; i < allCities.size(); i++) {
					allCities[i].display_information();
				}
				break;
			case 4:
				map.display_status();
				break;
			case 5:
				playerlist[pId]->displayCardsInHand();
				break;
			case 6:
				playerlist[pId]->display_player_info();
				break;
			case 7:
				for (int i = 0; i < playerlist.size(); i++) {
					playerlist[i]->display_player_info();
				}

			}

		} while (redoDisplay);


		int action = playerlist[pId]->requestAction();
		do {
			switch (action) {
			case 1: //drive
				cout << "\nYou chose to drive." << endl;

				do {
					cout << "Please choose a city id corresponding to the city you want to drive to." << endl;
					for (int i = 0; i < current.connections.size(); i++) {
						cout << "\t" << map.getCityByID(current.connections[i]).name << " (" << current.connections[i] << ")" << endl;
					}
					newCityID = pollForCity();
				} while (newCityID < 1 || newCityID > 48);
				success = playerlist[pId]->drive(newCityID);
				break;

			case 2: //direct flight
				cout << "\nYou chose to take a direct flight." << endl;
				do {
					cout << "\nPlease choose a city card in your hand corresponding to the city you want to fly to." << endl;
					cardIndex = pollForCards(pId);
				} while (cardIndex > playerlist[pId]->getNumOfCards() || cardIndex < 1);

				success = playerlist[pId]->direct_flight(cardIndex-1);
				break;
			case 3: //charter flight
				cout << "\nYou chose to take a charter flight." << endl;

				do { //Poll the user for the city they'd like to go to, and the city card they'd like to discard
					cout << "\nPlease choose the city you would like to fly to" << endl;
					newCityID = pollForCity();
					cout << "\Please choose the city card you'd like to discard to make this flight." << endl;
					cardIndex = pollForCards(pId);
				} while (cardIndex > playerlist[pId]->getNumOfCards() || cardIndex < 1 || newCityID >48 || newCityID < 1);

				success = playerlist[pId]->charter_flight(cardIndex-1, newCityID);
				break;
			case 4: //shuttle flight
				cout << "\nYou chose to take a shuttle flight." << endl;
				do {
					cout << "\nPlease choose the city you'd like to fly to." << endl;
					newCityID = pollForCity();
				} while (newCityID > 48 || newCityID < 1);

				success = playerlist[pId]->shuttle_flight(newCityID);
				break;
			case 5: //build research station
				do {
					cout << "\nPlease choose the city card corresponding to the city that you are in" << endl;
					cardIndex = pollForCards(pId);
				} while (cardIndex > playerlist[pId]->getNumOfCards() || cardIndex < 1);

				success = playerlist[pId]->build_research_station(cardIndex-1);
				break;
			case 6: //treat disease
				cout << "\nYou chose to treat a disease!\nTreating disease in current city." << endl;
				success = playerlist[pId]->treat_disease();
				break;
			case 7: //share knowledge
				/*
				/ This method is actually executed in this class, as references to each player's hands are required, and such references are not accessible through reference or role card classes
				/ However, the reference and role cards still perform the proper checks to ensure sharing knowledge is valid
				*/
				cout << "\nYou chose to share knowledge!" << endl;

				do {
					cout << "Which player would you like to share knowledge with?" << endl;
					for (int i = 0; i < playerlist.size(); i++) {
						cout << "\tPlayer " << playerlist[i]->getPlayerID() << endl;
					}
					cin >> otherPlayerID;
				} while (otherPlayerID > playerlist.size() || otherPlayerID < 0);

				do {
					//Decide whether you want to give or receive a card
					cout << "Choose 1 to give a card to another player, or 2 to receive a card from another player." << endl;
					cin >> giverstatus;
				} while (giverstatus < 1 || giverstatus>2);

				//Set who will be the giver and receiver
				if (giverstatus == 1) {
					giver = pId;
					receiver = otherPlayerID;
				}
				else {
					giver = otherPlayerID;
					receiver = pId;
				}

				if (find(pawnsInCity.begin(), pawnsInCity.end(), otherPlayerID) == pawnsInCity.end()) {
					cout << "\nCannot share knowledge, player " << otherPlayerID << " is not in the current location with you." << endl;
					redo = pollForRetry();
					break;
				}
			
				do {
					cout << "Which card would you like to give to the player?" << endl;
					cardIndex = pollForCards(giver);

					receivingHand = playerlist[receiver]->getHand();
					givingHand = playerlist[giver]->getHand();

					//For semantics, the reference/role card performs the proper checks for exchange validity
					success = playerlist[pId]->share_knowledge(givingHand, cardIndex-1);
				} while (cardIndex < 1 || cardIndex > playerlist[giver]->getNumOfCards());
				

				if (success > 0) {
					//If you get here, it means the sharing knowledge is valid and the card will pass hands here
					PlayerCard givingCard =givingHand[cardIndex - 1];
					playerlist[receiver]->drawCard(givingCard);
					std::cout << "Player " << playerlist[giver]->getPlayerID() << " has given a card to another player in " << map.getCityByID(playerlist[giver]->getCurrentLocation()).name << "(" << playerlist[pId]->getCurrentLocation() << "). " << std::endl;
				}
				break;
			case 8: //cure a disease
				cout << "\nYou chose to cure a diease." << endl;
				if (playerlist[pId]->getNumOfCards() < 5) {
					cout << "You do not have enough cards in your hand to cure a disease!" << endl;
					success = 0;
					break;
				}
				while (count < 5) {
					cout << "\nIndicate card " << count + 1 << " of cure cards." << endl;
					do {
						cardIndex = pollForCards(pId);
						count++;
					} while (cardIndex > playerlist[pId]->getNumOfCards() || cardIndex < 1);
					cure.push_back(cardIndex-1);
				}
				success = playerlist[pId]->discover_cure(cure);
				if (success != 0) { //If it worked, we need to discard the cards used
					for (int i = 0; i < cure.size(); i++) {
						int relativeIndex = (cure[i]-i)% playerlist[pId]->getNumOfCards();
						playerlist[pId]->discardCard(relativeIndex);
					}
					cardIndex = -1;
				}
				break;
			case 9:
				//This case can constitute a different action, as Contingency Planner, Operations Expert, and Dispatcher all have different extra actions
				if (playerlist[pId]->getRole() == "Operations Expert") {//We are going to execute a special move from a city with a researc station to any city
					cout << "\nYou chose the Operations Expert's special move!" << endl;
					do {
						cout << "\nPlease indicate a city card you wish to discard to make this move. Note, it does not have to match the city you are moving to!" << endl;
						cardIndex = pollForCards(pId);
					} while (cardIndex > playerlist[pId]->getNumOfCards() || cardIndex < 1);

					RoleCard* rc = playerlist[pId]->getRoleCard();
					PlayerCard moveCard = playerlist[pId]->getHand().at(cardIndex-1);
					//We are casting the role to an OperationsExpert type because we know it is an Operations Expert
					success = dynamic_cast<OperationsExpert&>(*rc).specialOperationsMove(playerlist[pId]->getMyPawn(), moveCard);
				}

				else if (playerlist[pId]->getRole() == "Contingency Planner") { //We are going to pick up a discarded Event card
					cout << "\nYou chose the Contingency Planner's special move!" << endl;
					//Since we do not have a discard pile at the moment, we will pass any arbitrary card to the function
					cout << "Passing an arbitrary PlayerCard to the function " << endl;
					/*PlayerCard* arbitrary = new PlayerCard("Event", 0, "Random Special Event");*/
					RoleCard* rc = playerlist[pId]->getRoleCard();
					/*success = dynamic_cast<ContingencyPlanner&>(*rc).pickUpSpecialEvent(arbitrary);*/
				}

				else if (playerlist[pId]->getRole() == "Dispatcher") { //We will be moving any other pawn as if it is our own
					cout << "\nYou chose the Dispatcher's special move!" << endl;
					do {
						cout << "Which player's pawn would you like to move? " << endl;
						for (int i = 0; i < playerlist.size(); i++) {
							cout << "Player " << playerlist[i]->getPlayerID() << " in " << playerlist[i]->getCurrentLocation() << endl;
						}
						cin >> otherPlayerID;
					} while (otherPlayerID > playerlist.size() || otherPlayerID < 0);

					do {
						cout << "\nPlease choose a city with another player in it to travel to." << endl;
						newCityID = pollForCity();
					} while (newCityID > 48 || newCityID < 1);

					RoleCard* rc = playerlist[pId]->getRoleCard();
					success = dynamic_cast<Dispatcher&>(*rc).specialMoveAnotherPlayer(playerlist[otherPlayerID]->getMyPawn(), newCityID);
				}
				else {
					cout << "\nYour role does not have any special moves." << endl;
					redo = 1;
					break;
				}
				if (success != 0 && playerlist[pId]->getRole() == "Contingency Planner") {
					//We need to delete the special event
					RoleCard* rc = playerlist[pId]->getRoleCard();
					dynamic_cast<ContingencyPlanner&>(*rc).discardSpecialEvent();
				}
				break;
			default:
				cout << "Invalid ID, please retry." << endl;
				redo = 0;
			}

			if (success != 1) { //If the action didn't work
				redo = pollForRetry();
			}
			else {
				redo = 1;
			}
		} while (redo == 0);

		if (success != 0) {
			playerlist[pId]->useAction();
			cout << "\nPlayer " << pId << " has " << playerlist[pId]->getAction() << " actions left." << endl;
			if (cardIndex != -1) playerlist[pId]->discardCard(cardIndex - 1);
		}
	}
}

void Game::drawPlayerCards(int pId) {
	PlayerCard card1 = deck->getTopCard();
	PlayerCard card2 = deck->getTopCard();
	if (card1.getType() != "epidemic") {
		playerlist[pId]->drawCard(card1);
	}
	else {
		InfectionDeck->infectEpidemic(&map);
	}
	if (card2.getType() != "epidemic") {
		playerlist[pId]->drawCard(card2);
	}
	else {
		InfectionDeck->infectEpidemic(&map);
	}



}

void Game::save_players() {
	vector<string> playersToSave;
	vector<string> playersCardToSave;


	SqlConnection savePlayer;
	
	
	
	for (int i = 0; i < playerlist.size(); i++) {

		string id = to_string(playerlist[i]->getPlayerID());
		string location = to_string(playerlist[i]->getCurrentLocation());
		string numOfCards = to_string(playerlist[i]->getNumOfCards());

		//SavePlayers table --> pcID, pcValue, pcColor , eventName, type, deckOrPlayerId
		string player = id + " , " + " ' " + playerlist[i]->getRole() + " ' " + " , " + location + " , " + numOfCards;
		playersToSave.push_back(player);


		for (int j = 0; j < playerlist[i]->getNumOfCards(); j++) {
			string cardType = playerlist[i]->getHand().at(j).getType();
			
			if (cardType == "city") {

				string cityId = to_string(playerlist[i]->getHand().at(j).getCityId());
				

				string card = cityId + " ,  ' " + playerlist[i]->getHand().at(j).getValue() + " ' ,  ' " + playerlist[i]->getHand().at(j).getColour() + " ' ,  null , ' " + cardType + "' ," + id;
				toSave.push_back(card);
			}
			if (cardType == "event") {

				string card = "null, ' " + playerlist[i]->getHand().at(j).getValue() + " '   , null , ' " + playerlist[i]->getHand().at(j).getName() + " '  ,  ' " +
																	playerlist[i]->getHand().at(j).getType() + " '  , "+ id ;
				toSave.push_back(card);
			}
		}
	}
	string* select = new string("INSERT INTO SavePlayerInfo(playerId,playerRole, playerLoc, numOfCards) VALUES  ");

	for (string str : playersToSave) {
		if ((str) != playersToSave.back()) {
			select->append("( " + str + " ),");
		}
		else
			select->append("( " + str + " )");
	}
	cout << *select << endl;
	savePlayer.sqlExecuteSelect(select);
	cout << "Players saved successfully!" << endl;
	
}
void Game::save_playerCards() {

	


	SqlConnection saveCard;
	deque<PlayerCard>::iterator playerCardIt;
	int counter = 0;
	for (playerCardIt = deck->deck.begin(); playerCardIt != deck->deck.end(); playerCardIt++) {
			string cardType = playerCardIt->getType();
			string deckId = to_string(-1);
			if (cardType == "city") {

				string cityId = to_string(playerCardIt->getCityId());
				string deckId = to_string(-1);
				string card = cityId + " ,  ' " + playerCardIt->getValue() + " ' ,  ' " + playerCardIt->getColour() + " ' ,  null , ' " + cardType + "' ," + deckId;
				toSave.push_back(card);
			}
			if (cardType == "event") {
				string card = "null, ' " + playerCardIt->getValue() + " '   , null , ' " + playerCardIt->getName() + " '  ,  ' " +
					playerCardIt->getType() + " '  , " + deckId;
				toSave.push_back(card);
			}
			if (cardType == "epidemic") {
				//TODO
			}
		}
	string* select = new string("INSERT INTO SavePlayerCards(pcID,pcValue, pcColor, eventName,type,deckOrPlayerId) VALUES ");

	for (string str : toSave) {
		if ((str) != toSave.back()) {
			select->append("( " + str + " ),");
		}
		else
			select->append("( " + str + " )");
	}

	saveCard.sqlExecuteSelect(select);

	cout << "Players saved successfully!" << endl;

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
					PlayerCard* card = new PlayerCard(PlayerCard::CITY, stoi(cardVals[i + 1]), cardVals[i + 2], cardVals[i + 3]);
					i += 3;
					hand.push_back(*card);
				}
				else {
					//if it's a player card, load it with other values
					PlayerCard* card = new PlayerCard(PlayerCard::EPIDEMIC, cardVals[i + 1], cardVals[i+2]);
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
void Game::displayDisplayOptions() {
	cout << "\nSelect option"<< endl;
	cout << "0) Choose action" << endl;
	cout << "1) Display information of the city you are on" << endl;
	cout << "2) Display information of adjacent cites" << endl;
	cout << "3) Display information of all cites" << endl;
	cout << "4) Display game status"<< endl;
	cout << "5) Display cards in hand"<< endl;
	cout << "6) Display current player status" << endl;
	cout << "7) Display all players status" << endl;
}

bool Game::isGameOver() {
	//add checks here
	if (map.checkGameOver()) {
		cout << "Game Over!!!"<< endl;
		return true;
	}
	if (map.checkWin()) {
		cout << "Win!!!" << endl;
		return true;
	}
	return false;
}


DeckOfCard<PlayerCard>* Game::instantiatePlayerCards(Map map, int numOfEpidemic) {

	/*  char *select = "select * from PlayerCards WHERE pcID = 0";
	sqlConnection(select);*/
	PlayerCard epidemic = PlayerCard(PlayerCard::EPIDEMIC, -1, "1-INCREASE \n move the infection rate marker forward 1 space \n"
													 "\t 2-INFECT \n draw the bottom card from the infection deck  and put 3 cubes  on that city. Discard that card \n"
													 "\t 3-INTESIFY \n shuffle the cards in the infection discard pile and put them on top of the infection deck", "no colour");
	

	//stringstream colourConversion;
	//string colour;

	vector<PlayerCard> playerCards;
	SqlConnection PlayerCardsConnect,EventCardsConnect;

	/*******************Back-Up *****************************/
	//vector<City> temp = map.getCities();
	//for (City city : temp) {
	//	int id = city.id;
	//	string name = city.name;
	//	colourConversion << (city.zone);
	//	colourConversion >> colour;

	//	PlayerCard cardToPush = PlayerCard(PlayerCard::CITY, id, name, colour);
	//	playerCards.push_back(cardToPush);
	//}

	//for (int i = 0; i < 4; i++) {
	//	playerCards.push_back(epidemic);
	//}
	/**/
	
	

	string* select =new string("select * from PlayerCards");
	PlayerCardsConnect.sqlExecuteSelect(select);

	vector<vector<string>> results = PlayerCardsConnect.Connection.colData;
	
	for (vector<string> rows : results) {

		int id;
		string value, colour;

		id = atoi(rows.at(0).c_str());
		value = rows.at(1);
		colour = rows.at(2);

		PlayerCard cardToPush = PlayerCard(PlayerCard::CITY, id, value, colour);
		playerCards.push_back(cardToPush);
	}


	
	*select = "select * from EventCards";
	EventCardsConnect.sqlExecuteSelect(select);

	vector<vector<string>> resultsEvent = EventCardsConnect.Connection.colData;

	for (vector<string> rows : resultsEvent) {

		int id;

		string eventName, eventValue;

		id = atoi(rows.at(0).c_str());
		eventName = rows.at(1);
		eventValue = rows.at(2);

		PlayerCard cardToPush = PlayerCard(PlayerCard::EVENT, eventName, eventValue);
		playerCards.push_back(cardToPush);
	}
	
	for (int i = 0; i < 4; i++) {
		playerCards.push_back(epidemic);
	}
	DeckOfCard<PlayerCard>* playerDeck = new DeckOfCard<PlayerCard>(playerCards);
	


	vector<PlayerCard> t = playerDeck->returnVector();
	for (PlayerCard player : t) {
		cout << player.getValue() << endl;
	}

	return playerDeck;
}

int main() {
	Game* game = new Game(2);
	DeckOfCard<PlayerCard>* deck = game->getDeck();
	game->displayPlayers();
	game->StartGame();
	vector<Player*> players = game->getPlayerlist();
	cout << players[0]->getCurrentLocation() << endl;
	//game->getMap().display_information();
	players[1]->drive(26);

	system("PAUSE");
	delete game;
	return 0;
}