#pragma once
#ifndef _VECTORPOINTS_H
#define _VECTORPOINTS_H
#include <vector>
#include "point.h"
using namespace std;

bool pointsInSameLine(vector<Point>& points, vector<Point>& endpoints, Point& p);//Exercise 67-2

void SortPoints(vector<Point>& points);
void bubbleSortPointsInLine(vector<Point>& points);
void bubbleSortPointsWithPoler(vector<Point>& points, Point& pole);

void getConvexHull(vector<Point>& points, vector<Point>& convexHull);

#endif