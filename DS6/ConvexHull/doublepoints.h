#pragma once
#ifndef _DOUBLEPOINTS_H
#define _DOUBLEPOINTS_H
#include "../extendedouble.h"
#include "point.h"
using namespace std;

bool pointsInSameLine(ExtendedDouble<Point>& points, ExtendedDouble<Point>& endpoints, Point& p);//Exercise 67-2

void SortPoints(ExtendedDouble<Point>& points);
void bubbleSortPointsInLine(ExtendedDouble<Point>& points);
void bubbleSortPointsWithPoler(ExtendedDouble<Point>& points, Point& pole);

ExtendedDouble<Point>::iterator findSmallestX(ExtendedDouble<Point>& points);
void getConvexHull(ExtendedDouble<Point>& points, ExtendedDouble<Point>& convexHull);

#endif