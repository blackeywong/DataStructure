#include "applications.h"
#include <iostream>
#include <sstream>
#include "extendedArrayStack.h"
#include <thread>
#include <chrono>
#include "drawing.h"
#include <regex>
#include "../DS5/arraylist.h"

/************************Parenthesis Matching********************************/
//Exercise 15
bool unmatchedParen(std::string& expr) {
	int count = 0;
	for (int i = 0; i < expr.size(); ++i) {
		if (expr[i] == '(')
			++count;
		else if (expr[i] == ')')
			--count;

		if (count < 0)//unmatched ')'
			return false;
	}

	if (count > 0)//unmatched '('
		return false;

	return true;
}

void printMatchedParensNoStack(const std::string& expr) {
	std::string s(expr);
	//std::string result;
	std::ostringstream oss;
	for (int i = 0; i < s.size(); ++i) {
		bool leftFound = false;
		for (int j = 0; j < s.size(); ++j) {
			if (s[j] == '(') {
				leftFound = true;
				bool rightFound = false;
				int k = j + 1;
				for (; k < s.size(); ++k) {
					if (s[k] == '(') {
						j = k;
					}
					else if (s[k] == ')') {
						rightFound = true;
						break;
					}
				}
				if (rightFound) {
					oss << '(' << j << ',' << k << ") ";
					s[j] = ' ';
					s[k] = ' ';
					std::cout << s << std::endl;
					break;
				}
				else {
					std::cout << "unmatched '(' found at " << j << std::endl;
					s[j] = ' ';
				}
			}
			else if (s[j] == ')' && !leftFound) {
				std::cout << "unmatched ')' found at " << j << std::endl;
				s[j] = ' ';
			}

		}

		if (!leftFound) break;
	}

	std::cout << "matched '(' and ')' found at " << oss.str() << std::endl;
}

//Program 8.6
void printMatchedPairs(const std::string& expr) {
	arrayStack<int> st;
	int length = expr.size();
	std::ostringstream oss;

	for (int i = 0; i < length; ++i) {
		if (expr[i] == '(')
			st.push(i);
		else if (expr[i] == ')') {
			if (!st.empty()) {
				oss << '(' << st.top() << ',' << i << ") ";
				st.pop();
			}
			else {
				std::cout << "unmatched ')' found at " << i << std::endl;
			}
		}
	}

	while (!st.empty()) {
		std::cout << "unmatched '(' found at " << st.top() << std::endl;
		st.pop();
	}

	std::cout << "matched '(' and ')' found at " << oss.str() << std::endl;
}
//Exercise 16
void printMatchedPairs2(const std::string& expr) {
	arrayStack<int> st;
	arrayStack<char> st2;

	int length = expr.size();
	std::ostringstream oss;

	for (int i = 0; i < length; ++i) {
		switch (expr[i]) {
		case '(':
		case '[':
			st.push(i);
			st2.push(expr[i]);
			break;
		case ')':
			if (!st.empty() && st2.top() == '(') {
				oss << '(' << st.top() << ',' << i << ") ";
				st.pop();
				st2.pop();
			}
			else if (!st.empty() && st2.top() == '[') {
				std::cout << "unmatched '[' and ')' found at " << '[' << st.top() << ',' << i << "), both of them will be dropped." << std::endl;
				st.pop();
				st2.pop();
			}
			else {
				std::cout << "unmatched " << expr[i] << " found at " << i << std::endl;
			}
			break;
		case ']':
			if (!st.empty() && st2.top() == '[') {
				oss << '[' << st.top() << ',' << i << "] ";
				st.pop();
				st2.pop();
			}
			else if (!st.empty() && st2.top() == '(') {
				std::cout << "unmatched '(' and ']' found at " << '(' << st.top() << ',' << i << "], both of them will be dropped." << std::endl;
				st.pop();
				st2.pop();
			}
			else {
				std::cout << "unmatched " << expr[i] << " found at " << i << std::endl;
			}
		}
	}

	while (!st.empty()) {
		std::cout << "unmatched " << st2.top() << " found at " << st.top() << std::endl;
		st.pop();
		st2.pop();
	}

	std::cout << "matched '(/[' and ')/]' found at " << oss.str() << std::endl;
}

//Exercise 17
void printMatchedPairs3(const std::string& expr) {
	arrayStack<int> st;
	arrayStack<char> st2;

	int length = expr.size();
	std::ostringstream oss;
	auto matched = [](char left, char right) {
		if (left == '(' && right == ')'
			|| left == '[' && right == ']'
			|| left == '{' && right == '}')
			return true;
		return false;
	};

	auto matchedPair = [&oss, &st, &st2](char left, char right, int i) {
		oss << left << st.top() << ',' << i << right << ' ';
		st.pop();
		st2.pop();
	};

	auto unmatchedPair = [&st, &st2](char left, char right, int i) {
		std::cout << "unmatched " << left << " and " << right << " found at " << left << st.top() << ',' << i << right << ", both of them will be dropped." << std::endl;
		st.pop();
		st2.pop();
	};

	auto unmatchedRight = [](char right, int i) {
		std::cout << "unmatched " << right << " found at " << i << std::endl;
	};

	for (int i = 0; i < length; ++i) {
		switch (expr[i]) {
		case '(':
		case '[':
		case '{':
			st.push(i);
			st2.push(expr[i]);
			break;
		case ')':
		case ']':
		case '}':
			if (!st.empty() && matched(st2.top(), expr[i])) {
				matchedPair(st2.top(), expr[i], i);
			}
			else if (!st.empty() && !matched(st2.top(), expr[i])) {
				unmatchedPair(st2.top(), expr[i], i);
			}
			else {
				unmatchedRight(expr[i], i);
			}
			break;
		}
	}

	while (!st.empty()) {
		std::cout << "unmatched " << st2.top() << " found at " << st.top() << std::endl;
		st.pop();
		st2.pop();
	}

	std::cout << "matched pairs found at " << oss.str() << std::endl;
}

/************************Tower of Hanoi********************************/

void towersOfHanoi(int n, int x, int y, int z) {
	if (n > 0) {
		towersOfHanoi(n - 1, x, z, y);
		std::cout << "Move top disk from tower " << x << " to top of tower " << y << std::endl;
		towersOfHanoi(n - 1, z, y, x);
	}
}

extendedArrayStack<int> tower[4];
void showState() {
	//std::this_thread::sleep_for(std::chrono::seconds(1));
	//system("cls");
	for(int i=1;i<4;++i)
		std::cout << "Tower " << i << ": " << tower[i] << std::endl;
}

void moveAndShow(int n, int x, int y, int z) {
	if (n > 0) {
		moveAndShow(n - 1, x, z, y);
		int d = tower[x].top();
		tower[y].push(d);
		tower[x].pop();
		//Exercise 20
		//std::cout << "Move top disk from tower " << x << " to top of tower " << y << std::endl;
		std::cout << "Move top disk: " << d << " from tower " << x << " to top of tower " << y << std::endl;
		showState();
		moveAndShow(n - 1, z, y, x);
	}
}

void towersOfHanoi(int n) {
	for (int d = n; d > 0; --d) {
		tower[1].push(d);
	}

	moveAndShow(n, 1, 2, 3);
}

/************************Train Track Rearrangement********************************/
extendedArrayStack<int>* track;
int numberOfCars;
int numberOfTracks;
int smallestCar;
int itsTrack;
//Exercise 27
int* trackSize;

bool railroad(int inputOrder[], int theNumberOfCars, int theNumberOfTracks, /*Exercise 27*/int* theTrackSize) {
	numberOfCars = theNumberOfCars;
	numberOfTracks = theNumberOfTracks;
	trackSize = theTrackSize;/*Exercise 27*/

	track = new extendedArrayStack<int>[numberOfTracks +1];

	int nextCarToOutput = 1;
	smallestCar = numberOfCars + 1;

	for (int i = 1; i <= numberOfCars; ++i) {
		if (inputOrder[i] == nextCarToOutput) {
			std::cout << "Move car " << inputOrder[i] << " from input track to output track" << endl;

			++nextCarToOutput;
			while (smallestCar == nextCarToOutput) {
				outputFromHoldingTrack();
				++nextCarToOutput;
			}
		}
		else {
			if (!putInHoldingTrack(inputOrder[i]))
				return false;
		}
	}
	return true;
}

void outputFromHoldingTrack() {
	track[itsTrack].pop();

	std::cout << "Move car " << smallestCar << " from holding track " << itsTrack << " to output track" << endl;
	smallestCar = numberOfCars + 2;
	for (int i = 1; i <= numberOfTracks; ++i) {
		if (!track[i].empty() && (track[i].top() < smallestCar)) {
			smallestCar = track[i].top();
			itsTrack = i;
		}
	}
}

bool putInHoldingTrack(int c) {
	int bestTrack = 0;
	int bestTop = numberOfCars + 1;

	for (int i = 1; i <= numberOfTracks; ++i) {
		if (!track[i].empty()) {
			int topCar = track[i].top();
			if (c < topCar && topCar < bestTop /*Exercise 27*/ && (trackSize == nullptr || track[i].size() < trackSize[i])) {
				bestTop = topCar;
				bestTrack = i;
			}
		}
		else {
			if (bestTrack == 0) bestTrack = i;
		}
	}
	if (bestTrack == 0) return false;

	track[bestTrack].push(c);

	std::cout << "Move car " << c << " from input track to holding track " << bestTrack << std::endl;

	if (c < smallestCar) {
		smallestCar = c;
		itsTrack = bestTrack;
	}
	return true;
}

/************************Switch Box Routing********************************/
bool checkBox(int net[], int n) {
	extendedArrayStack<int> stack;

	for (int i = 0; i < n; ++i) {
		if (!stack.empty()) {
			if (net[i] == net[stack.top()])
				stack.pop();
			else
				stack.push(i);
		}
		else
			stack.push(i);

		//Exercise 29, check if top() and relevant pin on the same net are all in the stack
		if (stack.size() <= 1)
			continue;
		else {
			int temp = stack.top();
			stack.pop();
			stringstream ss;
			ss << stack;
			std::string s;
			while (ss >> s) {
				int t = stoi(s);
				if (net[t] == net[temp]) {
					std::cout << "Switch box is not routable" << std::endl;
					return false;
				}
			}
			stack.push(temp);
		}
	}

	if (stack.empty()) {
		std::cout << "Switch box is routable" << std::endl;
		return true;
	}

	std::cout << "Switch box is not routable" << std::endl;
	return false;
}


/************************Offline Equivalence Class********************************/
void offlineEquivClass(const std::string& relations, int n) {

	extendedArrayStack<int>* list = new extendedArrayStack<int>[n + 1];

	string pattern = "\\( *(\\d+) *, *(\\d+) *\\)";
	try {
		regex r(pattern);

		int i = 1;
		for (sregex_iterator it(relations.begin(), relations.end(), r), end_it; it != end_it; ++it) {
			int r1 = stoi(it->str(1));
			int r2 = stoi(it->str(2));
			//Exercise 31
			if (r1 < 1 || r1 > n || r2 < 1 || r2 > n) {
				std::cout << "bad relation: " << it->str() << std::endl;
				return;
			}

			list[r1].push(r2);
			list[r2].push(r1);
			++i;
		}
	}
	catch (regex_error e) {
		std::cout << e.what() << "\ncode: " << e.code() << std::endl;
	}

	extendedArrayStack<int> unprocessedList;

	bool* out = new bool[n + 1];
	for (int i = 1; i <= n; ++i)
		out[i] = false;

	for (int i = 1; i <= n; ++i) {
		if (!out[i]) {
			std::cout << "Next class is: " << i << " ";
			out[i] = true;
			unprocessedList.push(i);
			while (!unprocessedList.empty()) {
				int j = unprocessedList.top();
				unprocessedList.pop();

				while (!list[j].empty()) {
					int q = list[j].top();
					list[j].pop();
					if (!out[q]) {
						std::cout << q << " ";
						out[q] = true;
						unprocessedList.push(q);
					}
				}
			}
		}
		std::cout << std::endl;
	}
	std::cout << "End of list of quievalence classes" << std::endl;

	delete[] list;
}

//Exercise 32
void offlineEquivClass2(const std::string& relations, int n) {

	ArrayList<int>* list = new ArrayList<int>[n + 1];

	string pattern = "\\( *(\\d+) *, *(\\d+) *\\)";
	try {
		regex r(pattern);

		int i = 1;
		for (sregex_iterator it(relations.begin(), relations.end(), r), end_it; it != end_it; ++it) {
			int r1 = stoi(it->str(1));
			int r2 = stoi(it->str(2));
			if (r1 < 1 || r1 > n || r2 < 1 || r2 > n) {
				std::cout << "bad relation: " << it->str() << std::endl;
				return;
			}
			list[r1].insert(list[r1].size(),r2);
			list[r2].insert(list[r2].size(), r1);
			++i;
		}
	}
	catch (regex_error e) {
		std::cout << e.what() << "\ncode: " << e.code() << std::endl;
	}

	extendedArrayStack<int> unprocessedList;

	bool* out = new bool[n + 1];
	for (int i = 1; i <= n; ++i)
		out[i] = false;

	for (int i = 1; i <= n; ++i) {
		if (!out[i]) {
			std::cout << "Next class is: " << i << " ";
			out[i] = true;
			unprocessedList.push(i);
			while (!unprocessedList.empty()) {
				int j = unprocessedList.top();
				unprocessedList.pop();

				while (!list[j].empty()) {
					int q = list[j].get(list[j].size()-1);
					list[j].erase(list[j].size() - 1);
					if (!out[q]) {
						std::cout << q << " ";
						out[q] = true;
						unprocessedList.push(q);
					}
				}
			}
		}
		std::cout << std::endl;
	}
	std::cout << "End of list of quievalence classes" << std::endl;

	delete[] list;
}
/************************Rat in a Maze********************************/
