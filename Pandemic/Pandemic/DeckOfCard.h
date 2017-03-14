#pragma once
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <queue>

/***************************************************************
/This template class allows the game to create multiple deck of different kind.
/This would mean that the shuffling algorithm can be use for different decks, also depending on which constructor is used
****************************************************************/
template <class T> class DeckOfCard {
	std::deque<T> deck;
	std::vector<T> deck;
	T *card;
	int numberOfInfection;
	bool isDeckShuffled = false;

public:
	DeckOfCard(); 
	DeckOfCard(std::vector<T> arrayOfCard, int numberOfInfections); 
	DeckOfCard(std::vector<T> arrayOfCard);
	T getTopCard();
	void shuffleDeck(std::vector<T> &cardDeck); 
	void shuffleInInfection(std::vector<T> &cardDeck, int numOfInfection);
private:
	void storeInQue(std::vector<T> deck); 
	void shufflePlayerCard(std::vector<T> &cardDeck, int epidemicRate, int position);

};