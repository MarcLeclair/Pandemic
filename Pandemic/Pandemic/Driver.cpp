#include "Driver.h"

int main() {


	Game* checkIfgameSave = new Game();
	checkIfgameSave->dropTables();
	bool startedOrNot = checkIfgameSave->isGameSaved();

	if (startedOrNot == false) {
		Game * game = new Game(2);
		DeckOfCard<PlayerCard>* deck = game->getDeck();
		Observer *g = new GameStatistics();
		g = new PlayersStatistics(g, game);
		g = new DiseaseStatistics(g, game);
		g = new CitiesStatistics(g, game);
		g = new ResourcesStatistics(g, game);
		game->attach(g);
		game->displayPlayers();
		game->StartGame();
		vector<Player*> players = game->getPlayerlist();
		cout << players[0]->getCurrentLocation() << endl;
		delete game;
	}
	else if (startedOrNot == true) {

		string userInput;
		cout << "would you like to load the game found?" << endl;
		cin >> userInput;
		if (userInput == "yes") {
			checkIfgameSave->LoadGame();
			Observer *g = new GameStatistics();
			g = new PlayersStatistics(g, checkIfgameSave);
			g = new DiseaseStatistics(g, checkIfgameSave);
			g = new CitiesStatistics(g, checkIfgameSave);
			g = new ResourcesStatistics(g, checkIfgameSave);
			checkIfgameSave->attach(g);
			checkIfgameSave->StartGame();
		}
		else
			checkIfgameSave->dropTables();
	}
	system("PAUSE");
	delete checkIfgameSave;
	return 0;
}