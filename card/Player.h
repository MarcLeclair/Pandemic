#pragma once
#include "DeckOfCard.h"
#include "PlayerCard.h"
#include "ReferenceCards.h"
#include "Pawn.h"
class Player {

	std::vector<PlayerCard> currentPlayerCards;
	Pawn pawn;
	ReferenceCards referenceCard;

public:
	
	Player();
	Player(std::vector<PlayerCard> deck);
	bool checkIfPlayerHasCard(std::string type, std::string nameOfCity);

};