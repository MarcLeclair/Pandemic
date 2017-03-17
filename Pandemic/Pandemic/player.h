/*
/ Claudia Della Serra, 26766048
/ COMP 345, Advanced Programming with C++
/
/ Assignment 1 Player Class
*/

#pragma once

#include <string>
#include<vector>
#include <iostream>
#include "ReferenceCard.h"
#include "RoleCard.h"
#include "possession.h"
#include "PlayerCard.h"
#include "map.h"

/********************************************************************************************************
/ Class that encapsulates all the functionality for a single player
/ Holds a pawn, a reference card, and a hand of player cards.
/ Also holds a reference to a generic RoleCard, which can be a role card of any type
/ This allows the role card to execute subclass-specific virtual functions inherited from ReferenceCard
********************************************************************************************************/
class Player
{
public:
	Player();
	Player(const Player& plr);
	Player(int pid, RoleCard* rolec, Map* mp);
	~Player();

	int getPlayerID() {
		return playerID;
	}

	void setPlayerID(int pid) { playerID = pid; }

	Pawn* getMyPawn() { return &playerPawn; }

	void setMyPawn(Pawn mp) { playerPawn = mp; }

	ReferenceCard* getRefCard() { return &refcard; }

	void setReferenceCard(ReferenceCard refc) { refcard = refc; }

	RoleCard* getRoleCard() { return role; }

	void setRoleCard(RoleCard* rc) { role = rc; }

	int getNumOfCards() { return numOfCards; }

	void setNumOfCards() { numOfCards = cardsInHand.size(); }

	int getCurrentLocation() { return playerPawn.get_location();}

	std::string getPawnColor() { return playerPawn.get_color(); }

	std::string getRole() { return (*role).getRoleName(); }

	int getAction() { return actions; }

	void setActions(int ac) { actions = ac; }

	void useAction() { --actions; }

	std::vector<PlayerCard> getHand() { return cardsInHand; }


	int performAction();
	//Functions to operate on the player's hand of PlayerCards
	void drawCard(PlayerCard plc);
	void displayCardsInHand();
	void discardCard(int disc);
	void balanceHand();
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
private:
	Pawn playerPawn;
	ReferenceCard refcard;

	//Holds a reference to a role card for polymorphism purposes, as role cards have multiple subtypes
	RoleCard* role;
	std::vector<PlayerCard> cardsInHand;
	int numOfCards;
	int playerID;
	int actions;
};

const static int maxCardsInHand = 7;