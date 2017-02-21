#pragma once
#include <vector>
#include <card.h>
#include <stack>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>


class DeckOfCard {
	std::deque<Card> deck;
	Card card;
	bool isDeckShuffled = false;
	typedef enum DeckType { infection, player, role}; // need a card type just to make sure all the cards within certain decks do belong there
public:
	DeckOfCard();// default constructor
	DeckOfCard(std::vector<Card> arrayOfCard); // pass initial array of cards at beginning of game.  
	//Remove this comment after checking out for your assignment
	//marc: im using a db to store my info, if you guys want to use it to I can put it online for us to use all the same db.
	//I.e: I'll make calls to a certain table containt type cards x and just put it all in an array. You can use a txt file or hard code them here . 
	//Though we should maybe think to do a single thing when we put it all together
	//I'm going to push what im doing for my side of things, yo uchange it to your liking :)
	//P.s for this upload Im not doing the db connection, im just putting a dummy string just so the compiler accepts it	
	Card getTopCard();

private:
	//void shuffleDeck(std::vector<Card> deck);
	void storeInQue(std::vector<Card> deck);

};