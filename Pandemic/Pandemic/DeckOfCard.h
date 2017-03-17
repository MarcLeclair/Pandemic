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
	
	std::vector<int> some;
	std::deque<T> deck;
	std::vector<T> vectorDeck;
	T *card;
	int numberOfInfection;
	bool isDeckShuffled = false;

public:
	 DeckOfCard();
	 DeckOfCard(std::vector<T> arrayOfCard);
	 T getTopCard();
	 void storeInQue(std::vector<T> initialDeck);
	 std::vector<T> returnVector();
	 std::vector<int> indices();

private:

	void shufflePlayerCard(std::vector<T> &cardDeck, int epidemicRate, int position, T epidemic);
	 void shuffleInInfection(std::vector<T> &cardDeck, int numberOfEpidemic);
	void shuffleDeck(std::vector<T> &cardDeck);

};

template <class T> DeckOfCard<T>::DeckOfCard() {

};

template<class T> DeckOfCard<T>::DeckOfCard(std::vector<T> arrayOfCard) { // regular deck constructor

	shuffleDeck(arrayOfCard);
	storeInQue(arrayOfCard);
};

//top card retrieval. Have to first check the front then pop it so the card is out of the deck;
template <class T> T DeckOfCard<T>::getTopCard() {
	T returnValue = deck.front();
	deck.pop_front();
	return returnValue;
};


//go through the arraylist and store it in a queue for easy top and bottom access. A deck wouldn't work as a vector 
// because we don't have access to ALL of its copmonent, only to top and bottom ,  at occasions.
template <class T> void DeckOfCard<T>::storeInQue(std::vector<T> initialDeck) {
	for (PlayerCard card : initialDeck) {
		deck.emplace_back(card);
	}
};
template <class T> void DeckOfCard<T>::shufflePlayerCard(std::vector<T> &cardDeck, int epidemicRate, int position, T epidemic) {

	

																  // iterator is used to have a pointer to certain place in vector to insert epidemic card 
	std::vector<int>::iterator it;
	it = v.begin()+ ((epidemicRate + 1) * position);

	cardDeck.insert(it, epidemic);
	// same algo as above, but this one will iterate only between two points. I.e if we have 4 epidemic it is suppose to do this assuming we have 48 city + 7 event
	//53 cards wand 4 epidemic will be ~ like this: i = 
	for (int i = (currentPosToShuffle + 1) * position; i > ((position * epidemicRate) - epidemicRate); --i) {
			int r = rand() % (i + 1);
			std::swap(cardDeck[i], cardDeck[r]);
		}
};

template <class T> void DeckOfCard<T>::shuffleInInfection(std::vector<T> &cardDeck, int numberOfEpidemic) {

	std::vector<int>::iterator it; // create random access iterator

								   // check the position at which we will introduce an epidemic card
	int posInVector;

	if (numberOfEpidemic == 4) {
		posInVector = (cardDeck.size() - 1) / 4; //53 - 1  = 52 ; 52/ 4 = 13 --> will insert an epidemic every 13 card
	}
	else if (numberOfEpidemic == 5) {
		posInVector = (cardDeck.size() - 3) / 5; //53 - 3  = 50 ; 50/ 5 = 10  --> will insert an epidemic every 10 card
	}
	else if (numberOfEpidemic == 6) {
		posInVector = (cardDeck.size() - 5) / 6;//53 -  5  = 48 ; 48/ 6 = 8 --> will insert an epidemic every 8 card
	}

	for (int counter = 1; counter <= numberOfEpidemic; counter++) {
		shuffleDeck(cardDeck, posInVector, counter); //this shuffle deck  algorithm is used for epidemic cards
	}
};

//Shuffle deck Algorithm fisher -yates shuffle based -- Takes in 2 cards at random place in the array and swap them together
// Although rand() isn't truly random ( as in it will favor a side at some point), it does serve its purpose right in this case
template <class T> void DeckOfCard<T>::shuffleDeck(std::vector<T> &cardDeck) {

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(1, 48); // define the range

	int N = cardDeck.size();
	for (int i = N - 1; i>0; --i) {
		int r = distr(eng) % (i + 1);
		std::swap(cardDeck[i], cardDeck[r]);
		some.push_back(r);
	}
/*
	for (T typ : cardDeck) {
		vectorDeck.push_back(typ);
	} testing */

};

//template <class T> std::vector<int> DeckOfCard<T>::indices() {
//	return some;
//};
//template <class T> std::vector<T> DeckOfCard<T>::returnVector() {
//	return vectorDeck;
// TESTING FUNCTIONS}





