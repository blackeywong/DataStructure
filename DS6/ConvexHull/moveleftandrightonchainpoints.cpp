#include "moveleftandrightonchainpoints.h"
using namespace std;
//数据结构算法与应用-C++语言描述 第六章
//Exercise 68
bool pointsInSameLine(MoveLeftAndRightOnChain<Point>& points, MoveLeftAndRightOnChain<Point>& endpoints, Point& pole) {
	if (points.size() <= 2) {
		endpoints = points;
		return true;
	}

	bool result = true;

	points.reset();
	Point p1, p2, p3;
	for (int i=0; i<points.size() -2; i++) {
		p1 = points.current();
		points.moveToNext();
		p2 = points.current();
		points.moveToNext();
		p3 = points.current();
		result = result && pointsInSameLine(p1, p2, p3);
		if (result == false) break;
		points.moveToPrevious();
	}

	if (result) {//in the same line, calculate the endpoints
		//the two points has max/min x are the endpoints
		points.reset();
		Point minPoint = points.current() , maxPoint = points.current();
		points.moveToNext();
		for (int i=1; i < points.size(); i++) {
			Point p = points.current();
			if (p.x < minPoint.x)
				minPoint = p;
			if (p.x > maxPoint.x)
				maxPoint = p;
			points.moveToNext();
		}
		endpoints.insert(0, minPoint);
		endpoints.insert(1, maxPoint);
	}
	else {//find a point in the middle of 3 points that not in a line		
		//since it just jumps out the loop, the current three points are not in a line
		pole = getPointInTriangle(p1, p2, p3);
	}

	return result;
}

void SortPoints(MoveLeftAndRightOnChain<Point>& points) {
	MoveLeftAndRightOnChain<Point> endpoints;
	Point pole(0, 0);
	if (pointsInSameLine(points, endpoints, pole)) {
		bubbleSortPointsInLine(points);
	}
	else {
		bubbleSortPointsWithPoler(points, pole);
	}
}

void bubbleSortPointsInLine(MoveLeftAndRightOnChain<Point>& points) {
	for (int i = 0; i < points.size() - 1; i++) {
		points.reset();
		bool sorted = false;
		for (int j = 0; j < points.size() - i - 1; j++) {
			Point& p1 = points.current();
			points.moveToNext();
			Point& p2 = points.current();
			if (p1.x > p2.x) {
				swap(p1, p2);
				sorted = true;
			}
		}
		if (!sorted) return;
	}
}

void bubbleSortPointsWithPoler(MoveLeftAndRightOnChain<Point>& points, Point& pole) {
	for (int i = 0; i < points.size() - 1; i++) {
		points.reset();
		bool sorted = false;
		for (int j = 0; j < points.size() - i - 1; j++) {
			Point& p1 = points.current();
			points.moveToNext();
			Point& p2 = points.current();
			double poler1 = calPoler(pole, p1, calTangent(pole, p1));
			double poler2 = calPoler(pole, p2, calTangent(pole, p2));
			double len1 = lengthOfTwoPoints(pole, p1);
			double len2 = lengthOfTwoPoints(pole, p2);
			if (poler1 > poler2 || poler1 == poler2 && len1 > len2) {
				swap(p1, p2);
				sorted = true;
			}
		}
		if (!sorted) return;
	}
}

int moveToSmallestX(MoveLeftAndRightOnChain<Point>& points) {
	points.reset();
	Point p1 = points.current();
	int smallest = 0;
	points.moveToNext();
	for (int i = 1; i < points.size();i++) {
		Point p2 = points.current();
		if (p2.x < p1.x) {
			p1 = p2;
			smallest = i;
		}
		points.moveToNext();
	}

	points.reset();
	int j = 0;
	for (; j < smallest; j++) {
		points.moveToNext();
	}
	return j;
}

void getConvexHull(MoveLeftAndRightOnChain<Point>& points, MoveLeftAndRightOnChain<Point>& convexHull) {
	if (points.size() < 3) {
		convexHull = points;
		return;
	}

	Point pole(0, 0);
	if (pointsInSameLine(points, convexHull, pole)) {//convexHull saves max and min endpoints in the line
		return;
	}

	if (points.size() == 3) {//triangle
		convexHull = points;
		return;
	}

	convexHull = points;//don't erase point from original MoveLeftAndRightOnChain. It may be unrecoverable
	SortPoints(convexHull);
	int index = moveToSmallestX(convexHull);//index for rx
	Point p = convexHull.current();
	Point x = p;
	if (!convexHull.atEnd()) {
		convexHull.moveToNext();
		index++;
	}
	else {
		convexHull.reset();
		index = 0;
	}
	Point rx = convexHull.current();
	if (!convexHull.atEnd())
		convexHull.moveToNext();
	else
		convexHull.reset();
	Point rrx = convexHull.current();
	while (true) {
		double angle = angleOfThreePointsCounterClockwise(x, rx, rrx);
		if (angle <= M_PI) {//remove second point
			convexHull.erase(index);
			rx = x;
			if (index > 1) {
				index--;
				convexHull.moveToPrevious();
				x = convexHull.previous();
				convexHull.moveToNext();
			}
			else if (index == 1) {
				index = 0;
				x = convexHull.last();
			}
			else if (index == 0)
			{
				index = convexHull.size() - 1;
				x = convexHull.lastSecond();
			}
		}
		else {//move to next
			x = rx;
			rx = rrx;
			index++;
			if (index == convexHull.size()) index = 0;
			if (rx == p)
				break;
			if (!convexHull.atEnd())
				convexHull.moveToNext();
			else
				convexHull.reset();
			rrx = convexHull.current();
		}
	}
}