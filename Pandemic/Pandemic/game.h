#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "ODBC.h"
#include "possession.h"
#include "DeckOfCard.h"
#include "Infection.h"
#include "map.h"
#include "player.h"
#include "PlayerView.h"
#include "ReferenceCard.h"
using namespace std;
class Game {
	ODBC_Class Example;
	Map map;
	vector<Player*> playerlist;
	vector<RoleCard*> rolelist;
	DeckOfCard<PlayerCard>* deck;
	Infection* InfectionDeck;
	
public:
	Game();
	Game(int);
	Map getMap() {
		return map;
	}

	vector<Player*> getPlayerlist() {
		return playerlist;
	}
	DeckOfCard<PlayerCard>* getDeck() {
		return deck;
	}
	void sqlConnection(const char* select);
	void displayDisplayOptions();
	void drawPlayerCards(int);
	void StartGame();
	void SaveGame();
	void LoadGame();
	bool isGameOver();
	void performPlayersTurn(int);
	int pollForCity();
	int pollForCards(int);
	int pollForRetry();
	void save_players();
	void load_players();
	int pollDispatcherPawn();
	DeckOfCard<PlayerCard>* instantiatePlayerCards(Map map, int numOfEpidemic);
	void displayPlayers();
};

