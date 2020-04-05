#pragma once
#ifndef _CARD_H
#define _CARD_H
#include <iostream>
#include <string>
#include "extendedchain.h"
using namespace std;

//���ݽṹ�㷨��Ӧ��-C++�������� ������
//Exercise 66

struct Card {
	enum Suit { Spade, Heart };// , Diamond, Club };

	enum Face { Two = 2, Three, Four };// , Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace};

	int deck;
	Suit suit;
	Face face;

	Card() {}
	Card(const int deck, const int suit, const int face) { this->deck = deck; this->suit = Suit(suit); this->face = Face(face);}
	Card(const Card& rec) { deck = rec.deck; suit = rec.suit; face = rec.face;}

	Card& operator=(const Card& rec) { deck = rec.deck; suit = rec.suit; face = rec.face; return *this; }
	bool operator!=(const Card& x) const
	{
		return deck != x.deck || suit != x.suit || face != x.face;
	}
	operator int() const { return face; }

};
ostream& operator<<(ostream& out, const Card& x);

int getDeck(ChainNode<Card>* node);
int getSuit(ChainNode<Card>* node);
int getFace(ChainNode<Card>* node);

ExtendedChain<Card>& constructCards();
void destructCards(ExtendedChain<Card>* chain);

#endif