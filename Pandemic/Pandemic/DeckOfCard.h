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



DeckOfCard<class T>::DeckOfCard() {

};
template<class T>  DeckOfCard(std::vector<T> arrayOfCard, int numberOfEpidemic) { // use this constructor to construc Player Card only because it takes in the number of epidemic card chosen by user

	shuffleInInfection(arrayOfCard, numberOfEpidemic); // call a shuffle algorithm that will introduce epidemic cards
	storeInQue(arrayOfCard);

};

template<class T> DeckOfCard(std::vector<T> arrayOfCard) { // regular deck constructor

	shuffleDeck(arrayOfCard);
	storeInQue(arrayOfCard);
};

//top card retrieval. Have to first check the front then pop it so the card is out of the deck;
template <class T> T DeckOfCard<class T>::getTopCard() {
	T returnValue = deck.front();
	deck.pop_front();
	return returnValue;
};

//Shuffle deck Algorithm fisher -yates shuffle based -- Takes in 2 cards at random place in the array and swap them together
// Although rand() isn't truly random ( as in it will favor a side at some point), it does serve its purpose right in this case
template <class T> void shuffleDeck(std::vector<T> &cardDeck) {
	int N = cardDeck.size();
	for (int i = N - 1; i>0; --i) {
		int r = rand() % (i + 1);
		std::swap(cardDeck[i], cardDeck[r]);
	}

	/*for (PlayerCard card : cardDeck) {
	std::cout << card.getValue() << std::endl;
	} Used for testing*/
};

//go through the arraylist and store it in a queue for easy top and bottom access. A deck wouldn't work as a vector 
// because we don't have access to ALL of its copmonent, only to top and bottom ,  at occasions.
template <class T> void storeInQue(std::vector<PlayerCard> initialDeck) {
	for (PlayerCard card : initialDeck) {
		deck.emplace_back(card);
	}
};

template <class T> void shuffleInInfection(std::vector<T> &cardDeck, int numberOfEpidemic) {

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

template <class T> void shufflePlayerCard(std::vector<T> &cardDeck, int epidemicRate, int position) {

	PlayerCard* epidemic = New PlayerCard("epidemic", 0, "test"); // create epidemic 

																  // iterator is used to have a pointer to certain place in vector to insert epidemic card 
	std::vector<int>::iterator it;
	it = (epidemicRate + 1) * position;

	cardDeck.insert(it, epidemic);
	// same algo as above, but this one will iterate only between two points. I.e if we have 4 epidemic it is suppose to do this assuming we have 48 city + 7 event
	//53 cards wand 4 epidemic will be ~ like this: i = 
	for (int i = (currentPosToShuffle + 1) * position; i > ((position * epidemicRate) - epidemicRate); --i) {
		int r = rand() % (i + 1);
		std::swap(cardDeck[i], cardDeck[r]);
	}
};