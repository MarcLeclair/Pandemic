#include "DeckOfCard.h"
#include <iterator>

DeckOfCard::DeckOfCard(std::vector<Card> arrayOfCard) {
	shuffleDeck(arrayOfCard);
	storeInQue(arrayOfCard);

};

DeckOfCard::DeckOfCard() {
	
};
Card DeckOfCard::getTopCard() {
	deck.pop_front();
};

void shuffleDeck(std::vector<Card> deck) {
	// seed the RNG
	std::random_device random;
	std::mt19937 randomNumber(random());

	std::copy(deck.cbegin(), deck.cend(),std::ostream_iterator<int>(std::cout, " "));

	auto counterCurrentIndex = deck.size();

	for (auto iterationCount = 0; deck.at(iterationCount).isEqual(deck.rend()); deck.at(++iterationCount), --counterCurrentIndex) // need to create my own iterator here
	{
		// get int distribution with new range
		std::uniform_int_distribution<> dis(0, counterCurrentIndex);
		const int randomIndex = dis(randomNumber);
		
		
		if (deck.at(iterationCount).isEqual(deck.at(randomIndex)))
		{
			std::swap(deck.at(randomIndex), deck.at(iterationCount));
		}
	}

};

void DeckOfCard::storeInQue(std::vector<Card> initialDeck) {
	for (Card card : initialDeck) {
		deck.insert(card); 
	}
};