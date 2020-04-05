#include "vectorpoints.h"
using namespace std;

bool pointsInSameLine(vector<Point>& points, vector<Point>& endpoints, Point& pole) {
	if (points.size() <= 2) {
		endpoints = points;
		return true;
	}

	bool result = true;

	vector<Point>::iterator b = points.begin();
	for (; b < points.end() - 2; b++) {
		result = result && pointsInSameLine(*b, *(b + 1), *(b + 2));
		if (result == false) break;
	}

	if (result) {//in the same line, calculate the endpoints
		//the two points has max/min x are the endpoints
		vector<Point>::iterator b2 = points.begin();
		Point minPoint = *b2, maxPoint = *b2;
		b2++;
		for (; b2 < points.end(); b2++) {
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

void SortPoints(vector<Point>& points) {
	vector<Point> endpoints;
	Point pole(0, 0);
	if (pointsInSameLine(points, endpoints, pole)) {
		bubbleSortPointsInLine(points);
	}
	else {
		bubbleSortPointsWithPoler(points, pole);
	}
}

void bubbleSortPointsInLine(vector<Point>& points) {
	for (int i = 0; i < points.size() - 2; i++) {
		for (int j = 0; j < points.size() - i - 1; j++) {
			if (points[j].x > points[j + 1].x)
				swap(points[j], points[j + 1]);
		}
	}
}

void bubbleSortPointsWithPoler(vector<Point>& points, Point& pole) {
	for (int i = 0; i < points.size() - 2; i++) {
		for (int j = 0; j < points.size() - i - 1; j++) {
			double poler1 = calPoler(pole, points[j], calTangent(pole, points[j]));
			double poler2 = calPoler(pole, points[j + 1], calTangent(pole, points[j + 1]));
			double len1 = lengthOfTwoPoints(pole, points[j]);
			double len2 = lengthOfTwoPoints(pole, points[j + 1]);
			if (poler1 > poler2 || poler1 == poler2 && len1 > len2)
				swap(points[j], points[j + 1]);
		}
	}
}

void getConvexHull(vector<Point>& points, vector<Point>& convexHull) {
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

	convexHull = points;//don't erase point from original vector. It may be unrecoverable
	SortPoints(convexHull);
	vector<Point>::iterator b = convexHull.begin();
	while ((b + 2) != convexHull.end()) {
		double angle = angleOfThreePointsCounterClockwise(*b, *(b + 1), *(b + 2));
		if (angle <= M_PI) {//remove second point
			convexHull.erase(b + 1);
		}
		else {//move to next
			b++;
		}
	}
	//calculate last two points plus first point 
	do {
		vector<Point>::iterator b = convexHull.begin();
		vector<Point>::iterator e = convexHull.end();
		double angle = angleOfThreePointsCounterClockwise(*(e - 2), *(e - 1), *b);
		if (angle <= M_PI) {//remove second point
			convexHull.erase(e - 1);
		}
		else {//the three points are convex'd
			break;
		}
	} while (true);
	//calculate last pne point plus first two points
	do {
		vector<Point>::iterator b = convexHull.begin();
		vector<Point>::iterator e = convexHull.end();
		double angle = angleOfThreePointsCounterClockwise(*(e - 1), *b, *(b + 1));
		if (angle <= M_PI) {//remove second point
			convexHull.erase(b);
		}
		else {//the three points are convex'd
			break;
		}
	} while (true);

}