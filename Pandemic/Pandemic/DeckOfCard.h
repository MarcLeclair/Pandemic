#pragma once
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <queue>
#include "PlayerCards.h"

template <class T> class DeckOfCard {
	std::deque<T> deck;
	std::vector<T> deck;
	T *card;
	int numberOfInfection;
	bool isDeckShuffled = false;

public:
	DeckOfCard();// default constructor
	DeckOfCard(std::vector<T> arrayOfCard, int numberOfInfections); // constructor for PlayerCard
	DeckOfCard(std::vector<T> arrayOfCard);
	T getTopCard(); // get top card of the queue
	void shuffleDeck(std::vector<T> &cardDeck); // shuffle the deck
	void shuffleInInfection(std::vector<T> &cardDeck, int numOfInfection);
private:
	void storeInQue(std::vector<T> deck); // put the vector into a queue so players only have access to bottom or top;
	void shufflePlayerCard(std::vector<T> &cardDeck, int epidemicRate, int position);

};