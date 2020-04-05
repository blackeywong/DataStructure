#pragma once
#ifndef _DS8_APPLICATIONS_H
#define _DS8_APPLICATIONS_H
#include <string>
#include <Windows.h>
#include "drawing.h"
#include "extendedArrayStack.h"

bool unmatchedParen(std::string& expr);
void printMatchedParensNoStack(const std::string& expr);//Exercise 15
void printMatchedPairs(const std::string& expr);
void printMatchedPairs2(const std::string& expr);//Exercise 16
void printMatchedPairs3(const std::string& expr);//Exercise 17

void towersOfHanoi(int n, int x, int y, int z);
void towersOfHanoi(int n);

bool railroad(int inputOrder[], int theNumberOfCars, int theNumberOfTracks,/*Exercise 27*/int* theTrackSize = nullptr);
void outputFromHoldingTrack();
bool putInHoldingTrack(int c);

bool checkBox(int net[], int n);

void offlineEquivClass(const std::string& relations, int n);
void offlineEquivClass2(const std::string& relations, int n);//Exercise 32

//Exercise 21
template<unsigned DISKS, unsigned TOWERS>
class HanoiTower {
public:
	HanoiTower();
	virtual ~HanoiTower();
	void move();
protected:
	void drawBase();
	void drawInitialDisks();
	MyRectangle getTopDiskRect(int disk, int tower, bool from);
	void moveDisk(int tower1, int tower2);
	virtual void moveAndShow(int n, int x, int y, int z);
	virtual COLORREF getColor(int disk);

	HWND myconsole;
	HDC mydc;
	extendedArrayStack<int> towerStack[TOWERS+1];

	int top;
	int left;
	int topDiskWidth;
	int diskHeight;
	int diskDiff;
	int diskGap;
	int baseLeft;
	int baseTop;
	int baseWidth;
	int baseHeight;
	int baseSpacing;

	COLORREF COLORS[10] = {
	RGB(255, 255, 255),//white
	RGB(255, 0, 0),//red
	RGB(0, 255, 0),//green
	RGB(0, 0, 255),//blue
	RGB(255, 255, 0),//yellow
	RGB(255, 0, 255),//purple
	RGB(0, 255, 255)//indigo
	};

};


template<unsigned DISKS, unsigned TOWERS>
HanoiTower<DISKS, TOWERS>::HanoiTower() {
	top = 20;
	left = 20;
	topDiskWidth = 30;
	diskHeight = 10;
	diskDiff = 20;
	diskGap = 5;
	baseLeft = 20;
	baseTop = (diskHeight + diskGap) * DISKS + left;
	baseWidth = diskDiff * DISKS + topDiskWidth;
	baseHeight = 5;
	baseSpacing = 50;
	myconsole = GetConsoleWindow();
	mydc = GetDC(myconsole);
	drawBase();
}

template<unsigned DISKS, unsigned TOWERS>
HanoiTower<DISKS, TOWERS>::~HanoiTower() {
	ReleaseDC(this->myconsole, this->mydc);
}

template<unsigned DISKS, unsigned TOWERS>
void HanoiTower<DISKS, TOWERS>::drawBase() {

	for (int i = 0; i < TOWERS; ++i) {
		MyRectangle base(Point(baseLeft + i * (baseSpacing + baseWidth), baseTop), Point(baseLeft + i * (baseSpacing + baseWidth) + baseWidth, baseTop + baseHeight), COLORS[0]);
		fillRectangle(mydc, base);
	}
}

template<unsigned DISKS, unsigned TOWERS>
void HanoiTower<DISKS, TOWERS>::drawInitialDisks() {
	for (int i = 1; i <= DISKS; ++i) {
		int diskWidth = topDiskWidth + (i - 1) * diskDiff;
		int x1 = baseLeft + diskDiff / 2 * (DISKS - i + 1);
		int x2 = x1 + diskWidth;
		int y1 = top + (i-1) * (diskHeight + diskGap);
		int y2 = y1 + diskHeight;
		fillRectangle(mydc, MyRectangle(Point(x1, y1), Point(x2, y2), getColor(i)));
	}
}

template<unsigned DISKS, unsigned TOWERS>
MyRectangle HanoiTower<DISKS, TOWERS>::getTopDiskRect(int disk, int tower, bool from) {
	int diskWidth = topDiskWidth + (disk - 1) * diskDiff;
	int x1 = baseLeft + diskDiff / 2 * (DISKS - disk + 1) + (tower - 1) * (baseWidth + baseSpacing);
	int x2 = x1 + diskWidth;
	int y1 = top + (DISKS - towerStack[tower].size()) * (diskHeight + diskGap);
	if (!from)
		y1 -= diskHeight + diskGap;
	int y2 = y1 + diskHeight;

	return MyRectangle(Point(x1, y1), Point(x2, y2), getColor(disk));
}

template<unsigned DISKS, unsigned TOWERS>
void HanoiTower<DISKS, TOWERS>::moveDisk(int tower1, int tower2) {
	int disk = towerStack[tower1].top();
	if (disk == 3 && tower1 == 1 && tower2 == 2) {
		int m = 1;
	}
	MyRectangle rectFrom = getTopDiskRect(disk, tower1, true);
	MyRectangle rectTo = getTopDiskRect(disk, tower2, false);
	moveRectangle(mydc, rectFrom, rectTo.topLeft);
	towerStack[tower2].push(disk);
	towerStack[tower1].pop();

}

template<unsigned DISKS, unsigned TOWERS>
void HanoiTower<DISKS, TOWERS>::moveAndShow(int n, int x, int y, int z) {
	if (n > TOWERS - 2) {
		moveAndShow(n - (TOWERS - 2), x, z, y);
		//std::cout << "Move top disk from tower " << x << " to top of tower " << y << std::endl;
		for (int i = TOWERS; i >= 4; --i) {
			moveDisk(x, i);
		}
		moveDisk(x, y);
		for (int i = 4; i <= TOWERS; ++i) {
			moveDisk(i, y);
		}
		moveAndShow(n - (TOWERS - 2), z, y, x);
	}
	else {
		for (int i = TOWERS; i >= TOWERS - n + 2; --i) {
			moveDisk(x, i);
		}
		moveDisk(x, y);
		for (int i = TOWERS - n + 2; i <= TOWERS; ++i) {
			moveDisk(i, y);
		}
	}
}

template<unsigned DISKS, unsigned TOWERS>
void HanoiTower<DISKS, TOWERS>::move() {
	for (int d = DISKS; d > 0; --d) {
		towerStack[1].push(d);
	}
	drawInitialDisks();

	moveAndShow(DISKS, 1, 2, 3);
}

template<unsigned DISKS, unsigned TOWERS>
COLORREF HanoiTower<DISKS, TOWERS>::getColor(int disk) {
	return COLORS[disk % 7];
}

/*******************HaHa Tower******************/

template<unsigned DISKS, unsigned TOWERS>
class HaHaTower : public HanoiTower<DISKS, TOWERS> {
protected:
	COLORREF getColor(int disk);
	//void moveAndShow(int n, int x, int y, int z);

};

template<unsigned DISKS, unsigned TOWERS>
COLORREF HaHaTower<DISKS, TOWERS>::getColor(int disk) {
	if (disk % 2 == 0)
		return RGB(255, 255, 0);
	return RGB(255, 0, 0);
}

//template<unsigned DISKS, unsigned TOWERS>
//void HaHaTower<DISKS, TOWERS>::moveAndShow(int n, int x, int y, int z) {
//	if (n == 1) {
//		int d = this->towerStack[x].top();
//		this->moveDisk(d, x, y);
//	}
//	else if (n > 1) {
//		moveAndShow(n - 2, x, z, y);
//		int d = this->towerStack[x].top();
//		//std::cout << "Move top disk from tower " << x << " to top of tower " << y << std::endl;
//		if (d % 2 == 1 && !this->towerStack[y].empty() && this->towerStack[y].top() % 2 == 1)
//			swap(y, z);
//		this->moveDisk(d, x, y);
//		d = this->towerStack[x].top();
//		this->moveDisk(d, x, z);
//		d = this->towerStack[y].top();
//		this->moveDisk(d, y, x);
//		d = this->towerStack[z].top();
//		this->moveDisk(d, z, y);
//		d = this->towerStack[x].top();
//		this->moveDisk(d, x, y);
//		moveAndShow(n - 2, z, y, x);
//	}
//}

//template<unsigned DISKS, unsigned TOWERS>
//void HaHaTower<DISKS, TOWERS>::moveAndShow(int n, int x, int y, int z) {
//	if (n == 1) {
//		int d = this->towerStack[x].top();
//		this->moveDisk(d, x, y);
//	}
//	else if (n == 2) {
//		moveTwoDisks(x, y, z);
//	}
//	else if (n > 2) {
//		moveAndShow(n - 2, x, z, y);
//		moveTwoDisks(x, y, z);
//		moveAndShow(n - 2, z, y, x);
//	}
//}
//
//template<unsigned DISKS, unsigned TOWERS>
//void HaHaTower<DISKS, TOWERS>::moveTwoDisks(int x, int y, int z) {
//	int d = this->towerStack[x].top();
//	this->moveDisk(d, x, y);
//	d = this->towerStack[x].top();
//	this->moveDisk(d, x, z);
//	d = this->towerStack[y].top();
//	this->moveDisk(d, y, x);
//	d = this->towerStack[z].top();
//	this->moveDisk(d, z, y);
//	d = this->towerStack[x].top();
//	this->moveDisk(d, x, y);
//}

#endif