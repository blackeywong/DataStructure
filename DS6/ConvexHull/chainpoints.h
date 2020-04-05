#pragma once
#ifndef _CHAINPOINTS_H
#define _CHAINPOINTS_H
#include "../extendedchain.h"
#include "point.h"
using namespace std;

bool pointsInSameLine(ExtendedChain<Point>& points, ExtendedChain<Point>& endpoints, Point& p);//Exercise 67-2

void SortPoints(ExtendedChain<Point>& points);
void bubbleSortPointsInLine(ExtendedChain<Point>& points);
void bubbleSortPointsWithPoler(ExtendedChain<Point>& points, Point& pole);
ExtendedChain<Point>::iterator findSmallestX(ExtendedChain<Point>& points);

void getConvexHull(ExtendedChain<Point>& points, ExtendedChain<Point>& convexHull);

#endif