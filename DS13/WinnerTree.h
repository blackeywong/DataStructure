#ifndef _WINNERTREE_H
#define _WINNERTREE_H

template<class T>
class WinnerTree {
public:
	virtual ~WinnerTree() {}
	virtual void initialize(T* thePlayer, int theNumberOfPlayers) = 0;
	virtual T winner() const = 0;
	virtual void rePlay(int thePlayer) = 0;
};

#endif
