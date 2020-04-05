#pragma once
#ifndef _DS9_APPLICATIONS_H
#define _DS9_APPLICATIONS_H
#include "extendedQueue.h"

bool railroad(int inputOrder[], int theNumberOfCars, int theNumberOfTracks/*Exercise 22*/, int* trackSize=nullptr);
void outputFromHoldingTrack();
bool putInHoldingTrack(int c/*Exercise 22*/, int* trackSize = nullptr);
//Exercise 23
bool railroadWithNoQueues(int inputOrder[], int theNumberOfCars, int theNumberOfTracks);
void outputFromHoldingTrackWithNoQueues();
bool putInHoldingTrackWithNoQueues(int c);
//Exercise 24
bool railroadWithNoStacks(int inputOrder[], int theNumberOfCars, int theNumberOfTracks);
void outputFromHoldingTrackWithNoStacks();
bool putInHoldingTrackWithNoStacks(int c);
#endif