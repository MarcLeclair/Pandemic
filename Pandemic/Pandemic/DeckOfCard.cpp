#include "DeckOfCard.h"

DeckOfCard<class T>::DeckOfCard() {

}
DeckOfCard<class T>::DeckOfCard(std::vector<T> arrayOfCard, int numberOfEpidemic) {

	shuffleInInfection(arrayOfCard, numberOfEpidemic);
	storeInQue(arrayOfCard);

}

DeckOfCard<class T>::DeckOfCard(std::vector<T> arrayOfCard) {

	shuffleDeck(arrayOfCard);
	storeInQue(arrayOfCard);
}

//top card retrieval;
template <class T> T DeckOfCard<class T>::getTopCard() {
	T returnValue = deck.front();
	deck.pop_front();
	return returnValue;
}

//Shuffle deck Algorithm fisher -yates shuffle based
template <class T> void DeckOfCard::shuffleDeck(std::vector<T> &cardDeck) {
	int N = cardDeck.size();
	for (int i = N - 1; i>0; --i) {
		int r = rand() % (i + 1);
		std::swap(cardDeck[i], cardDeck[r]);
	}

	/*for (PlayerCard card : cardDeck) {
		std::cout << card.getValue() << std::endl;
	} Used for testing*/
}

//go through the arraylist and store it in a queue for easy top and bottom access
template <class T> void DeckOfCard::storeInQue(std::vector<PlayerCard> initialDeck) {
	for (PlayerCard card : initialDeck) {
		deck.emplace_back(card);
	}
}

template <class T> void DeckOfCard::shuffleInInfection(std::vector<T> &cardDeck, int numberOfEpidemic) {
	
	std::vector<int>::iterator it; // create random access iterator
	
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
			shuffleDeck(cardDeck, posInVector, counter);
		}
	}

template <class T> void DeckOfCard::shufflePlayerCard(std::vector<T> &cardDeck, int epidemicRate, int position) {
	
	PlayerCard* epidemic = New PlayerCard("epidemic", 0, "test")

	std::vector<int>::iterator it;
	it = (epidemicRate+1) * position;

	cardDeck.insert(it, epidemic);

	for (int i = (currentPosToShuffle + 1) * position; i > ((position * epidemicRate) - epidemicRate); --i) {asfaxzv
		int r = rand() % (i + 1);
		std::swap(cardDeck[i], cardDeck[r]);
	}
}