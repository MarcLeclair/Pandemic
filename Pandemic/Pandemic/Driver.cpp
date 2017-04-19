#include "Driver.h"

int main() {


	Game* checkIfgameSave = new Game();
	//checkIfgameSave->dropTables();
	bool startedOrNot = checkIfgameSave->isGameSaved();
	bool newgame = true;
	int numberOfPlayers = 0;
	string choice;

	if (!startedOrNot) {
		do {
			if (cin.fail()) {
				std::cin.clear();
				std::cin.ignore(256, '\n');
			}
			cout << "Starting a new game" << endl;
			cout << "How many players with to play? (2 to 4)" << endl;
			cin >> numberOfPlayers;
		} while (cin.fail() || numberOfPlayers < 2 || numberOfPlayers > 4);

	}
	else {
		do {
			if (cin.fail()) {
				std::cin.clear();
				std::cin.ignore(256, '\n');
			}
			cout << "Start a new game or load saved game?(N/L)" << endl;
			cin >> choice;
			
		} while (cin.fail() || (choice != "L" && choice != "N"));
		
		if (choice == "L") {
			newgame = false;
		}
		else {
			cout << "Starting a new game" << endl;
			cout << "How many players with to play? (2 to 4)" << endl;
			cin >> numberOfPlayers;


		}

	}


	if (newgame) {

		director director;
		builder* startGame = new loadstartgame();

		director.setbuilder(startGame);
		director.buildInitialGame(numberOfPlayers);

		checkIfgameSave->dropTables();
		Game * game = director.getgame();
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
		delete startGame;
	}
	else if (!newgame) {

		string userInput;


		director dir;
		
		builder* loadGame = new loadSavedGame();


		dir.setbuilder(loadGame);
		loadGame->createnewstatement();
		
		dir.buildLoadedGame();


		Game* loadedGame = dir.getgame();
		


		Observer *g = new GameStatistics();
		g = new PlayersStatistics(g, checkIfgameSave);
		g = new DiseaseStatistics(g, checkIfgameSave);
		g = new CitiesStatistics(g, checkIfgameSave);
		g = new ResourcesStatistics(g, checkIfgameSave);
		loadedGame->attach(g);
		loadedGame->StartGame();
		delete loadedGame;
	}
	system("PAUSE");
	
	delete checkIfgameSave;
	return 0;
}