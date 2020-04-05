#pragma once
#ifndef _DOUBLECIRCULARPOINTS_H
#define _DOUBLECIRCULARPOINTS_H
#include "../extendeddoublecircular.h"
#include "point.h"
using namespace std;

bool pointsInSameLine(ExtendedDoubleCircular<Point>& points, ExtendedDoubleCircular<Point>& endpoints, Point& p);//Exercise 67-2

void SortPoints(ExtendedDoubleCircular<Point>& points);
void bubbleSortPointsInLine(ExtendedDoubleCircular<Point>& points);
void bubbleSortPointsWithPoler(ExtendedDoubleCircular<Point>& points, Point& pole);

ExtendedDoubleCircular<Point>::iterator findSmallestX(ExtendedDoubleCircular<Point>& points);
void getConvexHull(ExtendedDoubleCircular<Point>& points, ExtendedDoubleCircular<Point>& convexHull);

#endif