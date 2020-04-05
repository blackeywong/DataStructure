#pragma once
#ifndef _POINT_H
#define _POINT_H
#include <iostream>
using namespace std;
struct Point {
	double x;
	double y;
	Point() {}
	Point(double x, double y) { this->x = x; this->y = y; }
	Point(const Point& p) { x = p.x; y = p.y; }

	Point operator=(const Point& p) { x = p.x; y = p.y; return *this; }

	Point& operator+=(const Point& p) { x += p.x; y += p.y; return *this; }
	Point& operator-=(const Point& p) { x -= p.x; y -= p.y; return *this; }

	bool operator==(const Point& p) const { return x == p.x && y == p.y; }
	bool operator!=(const Point& p) const { return x != p.x || y != p.y; }
};

Point operator+(const Point& p1, const Point& p2);
Point operator-(const Point& p1, const Point& p2);
ostream& operator<<(ostream& out, const Point& p);
//Exercise 67-68
Point getPointInTriangle(Point& u, Point& v, Point& w);//Exercise 67-1
bool pointsInSameLine(Point& u, Point& v, Point& w);//Exercise 67-2

double calTangent(Point& pole, Point& p);
double calPoler(Point& pole, Point& p, double tangent);

double lengthOfTwoPoints(Point& p1, Point& p2);
double angleOfThreePoints(Point& u, Point& v, Point& w);
double slope(Point& p1, Point& p2);
double angleOfThreePointsCounterClockwise(Point& u, Point& v, Point& w);

#endif