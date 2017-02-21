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

//void shuffleDeck(std::vector<Card> deck) {
//	// seed the RNG
//	std::random_device random;
//	std::mt19937 randomNumber(random());
//
//	std::copy(deck.cbegin(), deck.cend(),std::ostream_iterator<int>(std::cout, " "));
//
//	auto counterCurrentIndex = deck.size();
//
//	for (auto iterationCount = 0; deck.at(iterationCount).isEqual(deck.rend()); deck.at(++iterationCount), --counterCurrentIndex) // need to create my own iterator here
//	{
//		// get int distribution with new range
//		std::uniform_int_distribution<> dis(0, counterCurrentIndex);
//		const int randomIndex = dis(randomNumber);
//		
//		
//		if (deck.at(iterationCount).isEqual(deck.at(randomIndex)))
//		{
//			std::swap(deck.at(randomIndex), deck.at(iterationCount));
//		}
//	}
//
//}; Will fix algorithm later, implemented an easier version but not "as good"

	void shuffleDeck(std::vector<Card> &cardDeck) {
		int N = cardDeck.size();
		for (int i = N - 1; i>0; --i) {  // gist, note, i>0 not i>=0
			int r = rand() % (i + 1); // gist, note, i+1 not i. "rand() % (i+1)" means 
									  // generate rand numbers from 0 to i
			std::swap(cardDeck[i], cardDeck[r]);
		}
	};
void DeckOfCard::storeInQue(std::vector<Card> initialDeck) {
	for (Card card : initialDeck) {
		deck.emplace_back(card);
	}
};