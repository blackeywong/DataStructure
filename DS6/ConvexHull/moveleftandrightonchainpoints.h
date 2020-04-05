#pragma once
#ifndef _MOVELEFTANDRIGHTONCHAINPOINTS_H
#define _MOVELEFTANDRIGHTONCHAINPOINTS_H
#include "../moveleftandrightonchain.h"
#include "point.h"
using namespace std;

bool pointsInSameLine(MoveLeftAndRightOnChain<Point>& points, MoveLeftAndRightOnChain<Point>& endpoints, Point& p);

void SortPoints(MoveLeftAndRightOnChain<Point>& points);
void bubbleSortPointsInLine(MoveLeftAndRightOnChain<Point>& points);
void bubbleSortPointsWithPoler(MoveLeftAndRightOnChain<Point>& points, Point& pole);
int moveToSmallestX(MoveLeftAndRightOnChain<Point>& points);

void getConvexHull(MoveLeftAndRightOnChain<Point>& points, MoveLeftAndRightOnChain<Point>& convexHull);

#endif