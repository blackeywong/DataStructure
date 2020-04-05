#include "applications.h"
#include <memory>


/************************Train Track Rearrangement********************************/
extendedQueue<int>* track;
int numberOfCars;
int numberOfTracks;
int smallestCar;
int itsTrack;
//Exercise 22
int directTrack;

bool railroad(int inputOrder[], int theNumberOfCars, int theNumberOfTracks/*Exercise 22*/, int* trackSize) {
	numberOfCars = theNumberOfCars;
	numberOfTracks = theNumberOfTracks;
	if (trackSize) {
		directTrack = 1;
		for (int i = 1; i <= numberOfTracks - 1; ++i) {
			if (trackSize[i] > trackSize[i+1])
				directTrack = i+1;
		}
	}
	else {
		directTrack = numberOfTracks;
	}

	track = new extendedQueue<int>[numberOfTracks+1];

	int nextCarToOutput = 1;
	smallestCar = numberOfCars + 1;

	for (int i = 1; i <= numberOfCars; ++i) {
		if (inputOrder[i] == nextCarToOutput) {
			std::cout << "Move car " << inputOrder[i] << " from input track to output track" << std::endl;

			++nextCarToOutput;
			while (smallestCar == nextCarToOutput) {
				outputFromHoldingTrack();
				++nextCarToOutput;
			}
		}
		else {
			if (!putInHoldingTrack(inputOrder[i], trackSize))
				return false;
		}
	}
	return true;
}

void outputFromHoldingTrack() {
	track[itsTrack].pop();

	std::cout << "Move car " << smallestCar << " from holding track " << itsTrack << " to output track" << std::endl;
	smallestCar = numberOfCars + 2;
	for (int i = 1; i <= numberOfTracks; ++i) {
		if (!track[i].empty() && (track[i].front() < smallestCar)) {
			smallestCar = track[i].front();
			itsTrack = i;
		}
	}
}

bool putInHoldingTrack(int c/*Exercise 22*/, int* trackSize) {
	int bestTrack = 0;
	int bestBack = 0;

	for (int i = 1; i <= numberOfTracks; ++i) {
		if (i == directTrack)
			continue;

		if (!track[i].empty()) {
			int backCar = track[i].back();
			if (c > backCar && backCar > bestBack && (trackSize == nullptr || trackSize[i] > track[i].size())) {
				bestBack = backCar;
				bestTrack = i;
			}
		}
		else {
			if (bestTrack == 0) {
				bestTrack = i;
			}
		}
	}
	if (bestTrack == 0) return false;

	track[bestTrack].push(c);

	if (c < smallestCar) {
		smallestCar = c;
		itsTrack = bestTrack;
	}

	std::cout << "Move car " << c << " from input track to holding track " << bestTrack << std::endl;

	return true;
}

//Exercise 23
int numberOfCarsWithNoQueues;
int numberOfTracksWithNoQueues;
int smallestCarWithNoQueues;
int itsTrackWithNoQueues;
std::shared_ptr<int[]> lastCar;
std::shared_ptr<int[]> whichTrack;


bool railroadWithNoQueues(int inputOrder[], int theNumberOfCars, int theNumberOfTracks) {
	numberOfCarsWithNoQueues = theNumberOfCars;
	numberOfTracksWithNoQueues = theNumberOfTracks;

	int nextCarToOutput = 1;
	smallestCarWithNoQueues = numberOfCarsWithNoQueues + 1;

	lastCar = std::shared_ptr<int[]>(new int[numberOfTracksWithNoQueues]);
	for (int i = 1; i <= numberOfTracksWithNoQueues - 1; ++i)
		lastCar[i] = 0;

	whichTrack = std::shared_ptr<int[]>(new int[numberOfCarsWithNoQueues +1]);
	for (int i = 1; i <= numberOfCarsWithNoQueues; ++i)
		whichTrack[i] = 0;

	for (int i = 1; i <= numberOfCarsWithNoQueues; ++i) {
		if (inputOrder[i] == nextCarToOutput) {
			std::cout << "Move car " << inputOrder[i] << " from input track to output track" << std::endl;

			++nextCarToOutput;
			while (smallestCarWithNoQueues == nextCarToOutput) {
				outputFromHoldingTrackWithNoQueues();
				++nextCarToOutput;
			}
		}
		else {
			if (!putInHoldingTrackWithNoQueues (inputOrder[i]))
				return false;
		}
	}
	return true;
}

void outputFromHoldingTrackWithNoQueues() {
	whichTrack[smallestCarWithNoQueues] = numberOfTracksWithNoQueues + 1;
	std::cout << "Move car " << smallestCarWithNoQueues << " from holding track " << itsTrackWithNoQueues << " to output track" << std::endl;
	int i = smallestCarWithNoQueues;
	smallestCarWithNoQueues = numberOfCarsWithNoQueues + 2;
	for (; i <= numberOfCarsWithNoQueues; ++i) {
		if (whichTrack[i] != 0 && whichTrack[i] != numberOfTracksWithNoQueues + 1) {
			smallestCarWithNoQueues = i;
			itsTrackWithNoQueues = whichTrack[i];
			break;
		}
	}
}

bool putInHoldingTrackWithNoQueues(int c) {
	int bestTrack = 0;
	int bestBack = 0;

	for (int i = 1; i <= numberOfTracksWithNoQueues-1; ++i) {
		if (lastCar[i] != 0) {
			if (c > lastCar[i]&& lastCar[i] > bestBack) {
				bestBack = lastCar[i];
				bestTrack = i;
			}
		}
		else {
			if (bestTrack == 0) {
				bestTrack = i;
			}
		}
	}
	if (bestTrack == 0) return false;

	whichTrack[c] = bestTrack;
	lastCar[bestTrack] = c;

	if (c < smallestCarWithNoQueues) {
		smallestCarWithNoQueues = c;
		itsTrackWithNoQueues = bestTrack;
	}

	std::cout << "Move car " << c << " from input track to holding track " << bestTrack << std::endl;

	return true;
}

//Exercise 24
int numberOfCarsWithNoStacks;
int numberOfTracksWithNoStacks;
int smallestCarWithNoStacks;
int itsTrackWithNoStacks;
std::shared_ptr<int[]> topCar;
std::shared_ptr<int[]> whichTrackWithNoStacks;


bool railroadWithNoStacks(int inputOrder[], int theNumberOfCars, int theNumberOfTracks) {
	numberOfCarsWithNoStacks = theNumberOfCars;
	numberOfTracksWithNoStacks = theNumberOfTracks;

	int nextCarToOutput = 1;
	smallestCarWithNoStacks = numberOfCarsWithNoStacks + 1;

	topCar = std::shared_ptr<int[]>(new int[numberOfTracksWithNoStacks+1]);
	for (int i = 1; i <= numberOfTracksWithNoStacks; ++i)
		topCar[i] = 0;

	whichTrackWithNoStacks = std::shared_ptr<int[]>(new int[numberOfCarsWithNoStacks + 1]);
	for (int i = 1; i <= numberOfCarsWithNoStacks; ++i)
		whichTrackWithNoStacks[i] = 0;

	for (int i = 1; i <= numberOfCarsWithNoStacks; ++i) {
		if (inputOrder[i] == nextCarToOutput) {
			std::cout << "Move car " << inputOrder[i] << " from input track to output track" << std::endl;

			++nextCarToOutput;
			while (smallestCarWithNoStacks == nextCarToOutput) {
				outputFromHoldingTrackWithNoStacks();
				++nextCarToOutput;
			}
		}
		else {
			if (!putInHoldingTrackWithNoStacks(inputOrder[i]))
				return false;
		}
	}
	return true;
}

void outputFromHoldingTrackWithNoStacks() {
	int temp = whichTrackWithNoStacks[smallestCarWithNoStacks];
	whichTrackWithNoStacks[smallestCarWithNoStacks] = numberOfTracksWithNoStacks + 1;
	std::cout << "Move car " << smallestCarWithNoStacks << " from holding track " << itsTrackWithNoStacks << " to output track" << std::endl;
	int i = smallestCarWithNoStacks;
	smallestCarWithNoStacks = numberOfCarsWithNoStacks + 2;
	for (; i <= numberOfCarsWithNoStacks; ++i) {
		if (whichTrackWithNoStacks[i] != 0 && whichTrackWithNoStacks[i] != numberOfTracksWithNoStacks + 1) {
			smallestCarWithNoStacks = i;
			itsTrackWithNoStacks = whichTrackWithNoStacks[i];
			break;
		}
	}

	for (; i <= numberOfCarsWithNoStacks; ++i) {
		if (whichTrackWithNoStacks[i] == temp ) {
			topCar[temp] = i;
			break;
		}
	}
	if (i == numberOfCarsWithNoStacks + 1)
		topCar[temp] = 0;
}

bool putInHoldingTrackWithNoStacks(int c) {
	int bestTrack = 0;
	int bestFront = numberOfCarsWithNoStacks + 2;

	for (int i = 1; i <= numberOfTracksWithNoStacks; ++i) {
		if (topCar[i] != 0) {
			if (c < topCar[i] && topCar[i] < bestFront) {
				bestFront = topCar[i];
				bestTrack = i;
			}
		}
		else {
			if (bestTrack == 0) {
				bestTrack = i;
			}
		}
	}
	if (bestTrack == 0) return false;

	whichTrackWithNoStacks[c] = bestTrack;
	topCar[bestTrack] = c;

	if (c < smallestCarWithNoStacks) {
		smallestCarWithNoStacks = c;
		itsTrackWithNoStacks = bestTrack;
	}

	std::cout << "Move car " << c << " from input track to holding track " << bestTrack << std::endl;

	return true;
}