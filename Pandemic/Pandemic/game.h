#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "SqlBuilder.h"
#include "ODBC.h"
#include "possession.h"
#include "DeckOfCard.h"
#include "Infection.h"
#include "map.h"
#include "player.h"
#include "PlayerView.h"
#include "ReferenceCard.h"
#include "SqlConnection.h"
#include "Subject.h"
#include "RoleFactory.h"
#include "togglePlayerStats.h"

using namespace std;
class Game : public Subject{

	
	int playerTurnOnLoad;
	bool hasGameStarted;
	ODBC_Class Example;
	Map map;
	vector<Player*> playerlist;
	vector<RoleCard*> rolelist;
	DeckOfCard<PlayerCard>* deck;
	vector<PlayerCard> discardPile;
	DeckOfCard<Infection>* InfectionDeck;
	vector<Infection> infectionDiscard;
	bool infectCities = true;
	int infectionRate = 1;
	
public:
	Game();
	Game(int);
	Map* getMap() {
		return &map;
	}

	vector<Player*> getPlayerlist() {
		return playerlist;
	}
	DeckOfCard<PlayerCard>* getDeck() {
		return deck;
	}

	void dropTables();
	void save_gameState(int playerIdTurns);
	bool isGameSaved();

	bool shouldCitiesBeInfected() {
		return infectCities;
	}

	void resetInfectCities() {
		infectCities = true;
	}

	void displayDisplayOptions();
	void displayPlayers();
	void drawPlayerCards(int);


	void StartGame();
	void SaveGame(int playerIdTurn);
	void LoadGame();
	bool isGameOver();

	void performPlayersTurn(int);

	vector<PlayerCard> returnEventCards(vector<PlayerCard>);
	bool playerHasSpecialEvent(int);
	void playEvent(int, int);
	void playEvent(PlayerCard*, int);
	int governmentGrantEvent(int);
	int resilientPopulationEvent();
	int forecastEvent();
	int airliftEvent(Pawn* playerPawn, int cityID);
	int oneQuietNightEvent();

	int pollForCity();
	int pollForCards(int);
	int pollForEvents(int);
	int pollForRetry();
	int pollDispatcherPawn();
	int pollPlayers();


	void save_infectionCards();
	void save_playerCards();
	void save_players();
	void load_players();
	void load_deck();
	void load_infectionCards();

	void endTurnInfection();
	void startInfect();
	void infectEpidemic();

	DeckOfCard<PlayerCard>* instantiatePlayerCards(Map map, int numOfEpidemic);
	DeckOfCard<Infection>* instantiateInfectionDeck(Map map);
};

