
#pragma once

#include <string>
#include<vector>
#include <iostream>
#include "ReferenceCard.h"
#include "RoleCard.h"
#include "possession.h"
#include "PlayerCard.h"
#include "map.h"
#include "Subject.h"

using namespace std;
/********************************************************************************************************
/ Class that encapsulates all the functionality for a single player
/ Holds a pawn, a reference card, and a hand of player cards.
/ Also holds a reference to a generic RoleCard, which can be a role card of any type
/ This allows the role card to execute subclass-specific virtual functions inherited from ReferenceCard
********************************************************************************************************/
class Player : public Subject
{
public:
	Player();
	Player(const Player& plr);
	Player(int pid, RoleCard* rolec);
	~Player();

	int getPlayerID() {
		return playerID;
	}


	//Setters

	void setCardsInHnad(vector<PlayerCard> vec) { cardsInHand = vec; }

	void setPlayerID(int pid) { playerID = pid; }
	void setMyPawn(Pawn* mp) { playerPawn = mp; }
	void setReferenceCard(ReferenceCard* refc) { refcard = refc; }
	void setRoleCard(RoleCard* rc) { role = rc; }
	void setNumOfCards() { numOfCards = cardsInHand.size(); }
	void setActions(int ac) { actions = ac; }

	//Getters
	Pawn* getMyPawn() { return playerPawn; }
	ReferenceCard* getRefCard() { return refcard; }
	RoleCard* getRoleCard() { return role; }
	int getNumOfCards() { return numOfCards; }
	int getCurrentLocation() { return playerPawn->get_location();}
	string getPawnColor() { return playerPawn->get_color(); }
	string getRole() { return role->getRoleName(); }
	string getRoleDescription() { return role->getRoleDescription(); }
	int getAction() { return actions; }
	std::vector<PlayerCard> getHand() { return cardsInHand; }


	void useAction() { --actions; }

	//Functions to operate on the player's hand of PlayerCards
	void drawCard(PlayerCard plc, vector<PlayerCard> &discardPile);
	void displayCardsInHand();
	void discardCard(int disc, vector<PlayerCard> &discardPile);
	void balanceHand(vector<PlayerCard> &discardPile);
	void display_player_info();

	//Functions to execute actions during a player's turn
	int requestAction();
	void outputPossibleActions();

	//Action Functions, being called on the role card
	int drive(int newCityID);
	int direct_flight(int cardIndex);
	int charter_flight(int cardIndex, int newCityID);
	int shuttle_flight(int newCityID);


	int build_research_station(int cardIndex);
	int treat_disease();
	int share_knowledge(vector<PlayerCard> receivingHand, int exchangeCard);
	int discover_cure(vector<int> cure);
	const Player& operator=(const Player& pl);
private:
	Pawn* playerPawn;
	ReferenceCard* refcard;
	//Holds a reference to a role card for polymorphism purposes, as role cards have multiple subtypes
	RoleCard* role;
	std::vector<PlayerCard> cardsInHand;
	int numOfCards;
	int playerID;
	int actions;
};

//Constant variable defining the max amount of cards allowed in hand
const static int maxCardsInHand = 7;