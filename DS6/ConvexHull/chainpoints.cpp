#include "chainpoints.h"
using namespace std;

bool pointsInSameLine(ExtendedChain<Point>& points, ExtendedChain<Point>& endpoints, Point& pole) {
	if (points.size() <= 2) {
		endpoints = points;
		return true;
	}

	bool result = true;

	ExtendedChain<Point>::iterator b = points.begin();
	for (; b +2 != points.end(); b++) {
		result = result && pointsInSameLine(*b, *(b + 1), *(b + 2));
		if (result == false) break;
	}

	if (result) {//in the same line, calculate the endpoints
		//the two points has max/min x are the endpoints
		ExtendedChain<Point>::iterator b2 = points.begin();
		Point minPoint = *b2, maxPoint = *b2;
		b2++;
		for (; b2 != points.end(); b2++) {
			if ((*b2).x < minPoint.x)
				minPoint = *b2;
			if ((*b2).x > maxPoint.x)
				maxPoint = *b2;
		}
		endpoints.clear();
		endpoints.push_back(minPoint);
		endpoints.push_back(maxPoint);
	}
	else {//find a point in the middle of 3 points that not in a line		
		//since it just jumps out the loop, the current three points are not in a line
		pole = getPointInTriangle(*b, *(b + 1), *(b + 2));
	}

	return result;
}

void SortPoints(ExtendedChain<Point>& points) {
	ExtendedChain<Point> endpoints;
	Point pole(0, 0);
	if (pointsInSameLine(points, endpoints, pole)) {
		bubbleSortPointsInLine(points);
	}
	else {
		bubbleSortPointsWithPoler(points, pole);
	}
}

void bubbleSortPointsInLine(ExtendedChain<Point>& points) {
	for (int i = 0; i < points.size() - 1; i++) {
		bool sorted = false;
		for (auto j = points.begin(); j + i + 1 != points.end(); j++) {
			if ((*j).x > (*(j + 1)).x) {
				swap(*j, *(j + 1));
				sorted = true;
			}
		}
		if (!sorted) return;
	}
}

void bubbleSortPointsWithPoler(ExtendedChain<Point>& points, Point& pole) {
	for (int i = 0; i < points.size() - 1; i++) {
		bool sorted = false;
		for (auto j = points.begin(); j + i + 1 != points.end(); j++) {
			double poler1 = calPoler(pole, *j, calTangent(pole, *j));
			double poler2 = calPoler(pole, *(j + 1), calTangent(pole, *(j + 1)));
			double len1 = lengthOfTwoPoints(pole, *j);
			double len2 = lengthOfTwoPoints(pole, *(j + 1));
			if (poler1 > poler2 || poler1 == poler2 && len1 > len2) {
				swap(*j, *(j + 1));
				sorted = true;
			}
		}
		if (!sorted) return;
	}
}

ExtendedChain<Point>::iterator findSmallestX(ExtendedChain<Point>& points) {
	auto b = points.begin();
	auto smallest = b;
	b++;
	while (b != points.end()) {
		if ((*b).x < (*smallest).x)
			smallest = b;
		b++;
	}
	return smallest;
}

void getConvexHull(ExtendedChain<Point>& points, ExtendedChain<Point>& convexHull) {
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

	convexHull = points;//don't erase point from original ExtendedChain. It may be unrecoverable
	SortPoints(convexHull);
	auto p = findSmallestX(convexHull);
	auto x = p;
	auto rx = x + 1;
	if (rx == convexHull.end()) rx = convexHull.begin();
	auto rrx = rx + 1;
	if (rrx == convexHull.end()) rrx = convexHull.begin();
	while (true) {

		double angle = angleOfThreePointsCounterClockwise(*x, *rx, *rrx);
		if (angle <= M_PI) {//remove second point
			convexHull.erase(convexHull.iteratorToIndex(rx));
			rx = x;
			x = convexHull.previous(x);
			if (x == convexHull.end()) x = convexHull.last();
		}
		else {//move to next
			x = rx;
			rx = rrx;
			if (rx == p)
				break;
			rrx = rx + 1;
			if (rrx == convexHull.end()) rrx = convexHull.begin();
		}
	}
}