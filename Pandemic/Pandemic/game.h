#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "possession.h"
#include "DeckOfCard.h"
#include "Infection.h"
#include "map.h"
#include "player.h"
//#include "PlayerCards.h"
#include "ReferenceCard.h"
using namespace std;
class Game {
	Map map;
	vector<Player*> playerlist;
	vector<RoleCard*> rolelist;
public:
	Game();
	Game(int);
	Map getMap() {
		return map;
	}

	vector<Player*> getPlayerlist() {
		return playerlist;
	}
	void displayDisplayOptions();
	void StartGame();
	bool isGameOver();
	void performPlayersTurn(int);
	int pollForCity();
	int pollForCards(int);
	int pollForRetry();
	void save_players();
	void load_players();
	DeckOfCard<PlayerCard>* instantiatePlayerCards(Map map, int numOfEpidemic);
	void displayPlayers();
};

