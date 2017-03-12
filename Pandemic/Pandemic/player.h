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
#include "PlayerCards.h"


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
	Player(int pid, RoleCard* rolec);
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

	//Functions to operate on the player's hand of PlayerCards
	void drawCard(PlayerCard plc);
	void displayCardsInHand();
	void discardCard(int disc);
	void balanceHand();

	//Function to infect a city. This takes a string, but should take an integer corresponding to a city ID
	void infectCity(std::string cityID);

	//Functions to execute actions during a player's turn
	int requestAction();
	int performAction();
	void outputPossibleActions();

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