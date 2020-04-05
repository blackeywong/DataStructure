#pragma once
#ifndef _POSITION_H
#define _POSITION_H
#include <iostream>

struct position {
	int row;
	int col;

	position() = default;
	position(int r, int c) :row(r), col(c) {}
	bool operator==(const position& pos) { return row == pos.row && col == pos.col; }
	bool operator!=(const position& pos) { return !operator==(pos); }
	position(const position& pos) :row(pos.row), col(pos.col) {}
	position& operator=(const position& pos) { row = pos.row; col = pos.col; return *this; }
};

position operator+(const position& pos1, const position& pos2) {
	return position(pos1.row + pos2.row, pos1.col + pos2.col);
}

position operator-(const position& pos1, const position& pos2) {
	//get index in offset comparing pos1 with pos2
	return position(pos1.row - pos2.row, pos1.col - pos2.col);
}

std::ostream& operator<<(std::ostream& out, const position& pos) {
	out << "(" << pos.row << "," << pos.col << ")";
	return out;
}

#endif
