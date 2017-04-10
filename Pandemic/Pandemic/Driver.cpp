#include "Driver.h"

int main() {
	Game* game = new Game(2);
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
	//game->getMap().display_information();
	//players[1]->drive(26);

	system("PAUSE");
	delete game;
	return 0;
}