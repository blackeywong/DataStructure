#pragma once
#ifndef _MAZE_H
#define _MAZE_H
#include "../DS5/arraylist.h"
#include <string>
#include <sstream>
#include <iostream>
#include "position.h"

const int OPTIONS = 8;

template<unsigned SIZE>
class Maze {
public:
	Maze();
	Maze(const std::string& maze_str);
	virtual ~Maze();
	bool findPath();
	bool findPath2(position here, int option);
	void showPath();

protected:
	unsigned getOffset(const position& pos1, const position& pos2);

	position offset[OPTIONS];
	ArrayList<position> path;
	int** maze;
};


template<unsigned SIZE>
Maze<SIZE>::Maze() {
	//Exercise 34
	//offset[0].row = 0; offset[0].col = 1;
	//offset[1].row = 1; offset[1].col = 0;
	//offset[2].row = 0; offset[2].col = -1;
	//offset[3].row = -1; offset[3].col = 0;
	offset[0].row = 0; offset[0].col = 1;
	offset[1].row = 1; offset[1].col = 1;
	offset[2].row = 1; offset[2].col = 0;
	offset[3].row = 1; offset[3].col = -1;
	offset[4].row = 0; offset[4].col = -1;
	offset[5].row = -1; offset[5].col = -1;
	offset[6].row = -1; offset[6].col = 0;
	offset[7].row = -1; offset[7].col = 1;

	maze = new int * [SIZE + 2];
	for (int i = 0; i < SIZE + 2; i++) {
		maze[i] = new int[SIZE + 2];
	}

	for (int i = 0; i < SIZE + 2; i++) {
		maze[0][i] = maze[SIZE + 1][i] = 1;
		maze[i][0] = maze[i][SIZE + 1] = 1;
	}
}

template<unsigned SIZE>
Maze<SIZE>::Maze(const std::string& maze_str):Maze() {
	std::istringstream iss(maze_str);
	std::string s;
	for (int i = 1; i <= SIZE; ++i) {
		for (int j = 1; j <= SIZE; ++j) {
			if (iss >> s) {
				maze[i][j] = stoi(s);
			}
			else
				maze[i][j] = 0;
		}
	}
}

template<unsigned SIZE>
Maze<SIZE>::~Maze() {
	for (int i = 0; i < SIZE + 2; i++) {
		delete[] maze[i];
	}
	delete[] maze;
	maze = nullptr;
}

template<unsigned SIZE>
bool Maze<SIZE>::findPath() {

	position here(1,1), next(1,2), goal(SIZE, SIZE);
	int option = 0;

	maze[1][1] = 1;
	
	while (here != goal) {
		if (option < OPTIONS) {
			next = here + offset[option];
			if (maze[next.row][next.col] == 0) {
				path.push_back(here);
				maze[next.row][next.col] = 1;
				here = next;
				option = 0;
			}
			else {
				++option;
			}
		}
		else {
			if (path.empty()) {
				return false;
			}
			position temp;
			path.pop_back(temp);
			//Exercise 34
			//if (here.row == temp.row)
			//	option = temp.col - here.col + 2;
			//else
			//	option = temp.row - here.row + 3;
			option = getOffset(here, temp) + 1;
			here = temp;
		}
	}

	return true;
}

//Exercise 36
template<unsigned SIZE>
bool Maze<SIZE>::findPath2(position here, int option) {
	if (here.row == SIZE && here.col == SIZE)
		return true;
	
	position next;
	if (option < OPTIONS) {
		next = here + offset[option];
		if (maze[next.row][next.col] == 0) {
			path.push_back(here);
			maze[next.row][next.col] = 1;
			here = next;
			option = 0;
		}
		else {
			++option;
		}
	}
	else {
		if (path.empty()) {
			return false;
		}
		position temp;
		path.pop_back(temp);
		option = getOffset(here, temp) + 1;
		here = temp;
	}
	return findPath2(here, option);
}

template<unsigned SIZE>
void Maze<SIZE>::showPath() {
	std::cout << "Path: ";
	for (int i = 0; i < path.size(); ++i) {
		std::cout << "(" << path[i].row << "," << path[i].col << ") ";
	}
	std::cout << std::endl;
}

template<unsigned SIZE>
unsigned Maze<SIZE>::getOffset(const position& pos1, const position& pos2) {
	position off = pos1 - pos2;

	if (off == offset[0]) return 0;
	if (off == offset[1]) return 1;
	if (off == offset[2]) return 2;
	if (off == offset[3]) return 3;
	if (off == offset[4]) return 4;
	if (off == offset[5]) return 5;
	if (off == offset[6]) return 6;
	if (off == offset[7]) return 7;
}


#endif