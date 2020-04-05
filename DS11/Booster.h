#pragma once
#ifndef _BOOSTER_H
#define _BOOSTER_H

#include <iostream>

struct Booster {
	int degradeToLeaf,
		degradeFromParent;
	bool boosterHere;

	Booster() :degradeToLeaf(0), degradeFromParent(0), boosterHere(false){}
	Booster(const Booster& b):degradeToLeaf(b.degradeToLeaf), degradeFromParent(b.degradeFromParent), boosterHere(b.boosterHere) {}

	void output(std::ostream& out) const { out << boosterHere << ' ' << degradeToLeaf << ' ' << degradeFromParent << ' '; }
	void input(std::istream& in) { in >> degradeFromParent; }

};

std::ostream& operator<<(std::ostream& out, const Booster& x);
std::istream& operator>>(std::istream& in, Booster& x);
#endif