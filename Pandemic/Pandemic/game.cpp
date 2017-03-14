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
void Game::performPlayersTurn(int pId) {
	playerlist[pId].setActions(4);
	while (playerlist[pId].getAction() > 0) {
		playerlist[pId].performAction();
		
	}
	//Draw player cards
	//Draw epidemic cards

}
bool Game::isGameOver() {
	//add checks here
	return false;
}

