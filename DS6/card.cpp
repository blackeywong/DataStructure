#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include<ctime>
#include<random>
#include "card.h"
#include "extendedchain.h"

ostream& operator<<(ostream& out, const Card& x)
{
	out << x.deck << ' ' << x.suit << ' ' << x.face << endl; return out;
}

int getDeck(ChainNode<Card>* node) {
	return node->element.deck;
}

int getSuit(ChainNode<Card>* node) {
	return node->element.suit;
}

int getFace(ChainNode<Card>* node) {
	return node->element.face - 2;
}


ExtendedChain<Card>& constructCards() {
	constexpr int deckNum = 10;
	constexpr int suitNum = 4;
	constexpr int faceNum = 13;
	constexpr int cardNum = suitNum * faceNum;
	const int total = deckNum * cardNum;
	ExtendedChain<Card>* chain = new ExtendedChain<Card>();

	//create a sorted chain
	for (int i = 0; i < deckNum; i++) {
		for (int j = 0; j < cardNum; j++) {
			int deck = i;
			Card::Suit suit = (Card::Suit)(j / faceNum);
			Card::Face face = (Card::Face)(j % faceNum + 2);
			Card card(deck,suit,face);
			chain->push_back(card);
		}
	}

	//randomize it
	srand(time(0));


	for (int i = 0; i < total; i++) {
		unsigned int from = rand() % total;
		unsigned int to = rand() % total;
		Card card = chain->get(from);
		chain->erase(from);
		chain->insert(to, card);
	}

	//random drop 10%
	for (int i = 0; i < total / 10; i++) {
		unsigned int drop = rand() % (total - i);
		chain->erase(drop);
	}
	
	return *chain;
}

void destructCards(Chain<Card>* chain) {
}