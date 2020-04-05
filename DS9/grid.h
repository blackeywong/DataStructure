#pragma once
#ifndef _GRID_H
#define _GRID_H
#include "ArrayDeque.h"
#include <string>
#include <sstream>
#include <iostream>
#include "../DS8/position.h"

const int OPTIONS = 4;

template<unsigned SIZE>
class Grid {
public:
	Grid();
	Grid(const std::string& grid_str);
	virtual ~Grid();
	bool findPath(position here, position goal);
	void showPath();
	//Exercise 27
	void clearPath(position here, position goal);

protected:
	position offset[OPTIONS];
	arrayDeque<position> path;
	int** grid;
	int pathLength;
};


template<unsigned SIZE>
Grid<SIZE>::Grid() {
	offset[0].row = 0; offset[0].col = 1;
	offset[1].row = 1; offset[1].col = 0;
	offset[2].row = 0; offset[2].col = -1;
	offset[3].row = -1; offset[3].col = 0;

	grid = new int* [SIZE + 2];
	for (int i = 0; i < SIZE + 2; i++) {
		grid[i] = new int[SIZE + 2];
	}

	for (int i = 0; i < SIZE + 2; i++) {
		grid[0][i] = grid[SIZE + 1][i] = 1;
		grid[i][0] = grid[i][SIZE + 1] = 1;
	}
	
	pathLength = 0;
}

template<unsigned SIZE>
Grid<SIZE>::Grid(const std::string& grid_str) :Grid() {
	std::istringstream iss(grid_str);
	std::string s;
	for (int i = 1; i <= SIZE; ++i) {
		for (int j = 1; j <= SIZE; ++j) {
			if (iss >> s) {
				grid[i][j] = stoi(s);
			}
			else
				grid[i][j] = 0;
		}
	}
}

template<unsigned SIZE>
Grid<SIZE>::~Grid() {
	for (int i = 0; i < SIZE + 2; i++) {
		delete[] grid[i];
	}
	delete[] grid;
	grid = nullptr;
}

template<unsigned SIZE>
void Grid<SIZE>::showPath() {
	std::cout << "Path: ";
		std::cout << path;
	std::cout << std::endl;
}

template<unsigned SIZE>
bool Grid<SIZE>::findPath(position here, position goal) {
	if (here == goal)
		return true;

	int option = 0;

	grid[here.row][here.col] = 2;
	arrayQueue<position> q;
	position nbr;

	do {
		for (int i = 0; i < OPTIONS;++i) {
			nbr = here + offset[i];
			if (grid[nbr.row][nbr.col] == 0) {
				grid[nbr.row][nbr.col] = grid[here.row][here.col] + 1;
				if (nbr == goal)
					break;
				q.push(nbr);
			}
		}

		if (nbr == goal)
			break;

		if (q.empty())
			return false;

		here = q.front();
		q.pop();
	} while (true);

	pathLength = grid[goal.row][goal.col] - 2;

	here = goal;
	for (int j = pathLength - 1; j >= 0; --j) {
		path.push_front(here);

		for (int i = 0; i < OPTIONS; ++i) {
			nbr = here + offset[i];
			if (grid[nbr.row][nbr.col] == j + 2)
				break;
		}
		here = nbr;
	}

	return true;
}

template<unsigned SIZE>
void Grid<SIZE>::clearPath(position here, position goal) {
	grid[here.row][here.col] = 1;
	if (here == goal)
	{
		return;
	}

	int option = 0;

	arrayQueue<position> q;
	position nbr;

	do {
		for (int i = 0; i < OPTIONS; ++i) {
			nbr = here + offset[i];
			if (grid[nbr.row][nbr.col] != 0 && grid[nbr.row][nbr.col] != 1) {
				grid[nbr.row][nbr.col] = 0;
				if (nbr == goal)
					break;
				q.push(nbr);
			}
		}

		if (q.empty())
			break;

		here = q.front();
		q.pop();
	} while (true);

	for (int j = pathLength - 1; j >= 0; --j) {
		here = path.front();
		path.pop_front();
		grid[here.row][here.col] = 1;
	}
}


#endif