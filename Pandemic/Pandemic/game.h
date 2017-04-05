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
#include "SqlConnection.h"
using namespace std;
class Game {
	bool hasGameStarted;
	ODBC_Class Example;
	Map map;
	vector<Player*> playerlist;
	vector<RoleCard*> rolelist;
	vector<string> toSave;
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
	void save_playerCards();
	void save_players();
	void load_players();
	int pollDispatcherPawn();
	DeckOfCard<PlayerCard>* instantiatePlayerCards(Map map, int numOfEpidemic);
	DeckOfCard<Infection>* instantiateInfectionCards(Map map);
	void displayPlayers();
};

