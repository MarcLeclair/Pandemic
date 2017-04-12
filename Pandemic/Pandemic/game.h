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
	vector<PlayerCard> discardPile;
	Infection* InfectionDeck;
	bool infectCities = true;
	
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
	void SaveGame();
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


	void save_playerCards();
	void save_players();
	void load_players();

	void load_deck();

	DeckOfCard<PlayerCard>* instantiatePlayerCards(Map map, int numOfEpidemic);
	DeckOfCard<Infection>* instantiateInfectionDeck(Map map);
};

