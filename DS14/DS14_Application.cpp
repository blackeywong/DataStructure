#include<utility>
#include<cmath>
#include<numeric>
#include<fstream>

#include "DS14_Application.h"
#include "DupBinarySearchTreeWithGE.h"
#include "../DS5/arraylist.h"
#include "IndexedBinarySearchTree.h"

void averageHeight(int n)
{
	int times = 100;
	int totalHeight = 0;
	int lowBound = 1;
	int highBound = n;

	for (int k = 0; k < times; ++k) {
		int* numbers = new int[n];
		for (int i = 0; i < n; ++i) {
			numbers[i] = i + 1;
		}

		std::default_random_engine e(static_cast<unsigned int>(time(nullptr)));
		std::uniform_int_distribution<int> u(lowBound, highBound);
		for (int i = 0; i < n; ++i) {
			int pos1 = u(e);
			int pos2 = u(e);
			using std::swap;
			swap(numbers[pos1 - 1], numbers[pos2 - 1]);
		}

		BinarySearchTree<int, int> bst;
		for (int i = 0; i < n; ++i) {
			bst.insert({ numbers[i], numbers[i] });
		}

		totalHeight += bst.Height();

		delete[] numbers;
	}
	double averageHeight = (double)totalHeight / (double)times;

	int goal = (int)(log(n + 1) / log(2) + 1) * 2;
	std::cout << "n is: " << n << "; average height: " << averageHeight << "; goal: " << goal << std::endl;
}


void bestFitPack(int* objectSize, int numberOfObjects, int binCapacity) {
	int n = numberOfObjects;
	int binsUsed = 0;
	DupBinarySearchTreeWithGE<int, int> theTree;
	std::pair<int, int> theBin;

	for (int i = 1; i <= n; ++i) {
		std::pair<int, int>* bestBin = theTree.findGE(objectSize[i]);
		if (bestBin == nullptr) {
			theBin.first = binCapacity;
			theBin.second = ++binsUsed;
		}
		else {
			theBin = *bestBin;
			theTree.erase(bestBin->first);
		}
		std::cout << "Pack object " << i << " in bin " << theBin.second << endl;

		theBin.first -= objectSize[i];
		if (theBin.first > 0) {
			theTree.insert(theBin);
		}
	}
}

void bestFitPack2(int* objectSize, int numberOfObjects, int binCapacity) {
	int n = numberOfObjects;
	int binsUsed = 0;
	DupBinarySearchTreeWithGE<int, int> theTree;
	std::pair<int, int> theBin;

	for (int i = 1; i <= n; ++i) {
		std::pair<int, int> bestBin = theTree.eraseGE(objectSize[i]);
		if (bestBin.first == -1) {
			theBin.first = binCapacity;
			theBin.second = ++binsUsed;
		}
		else {
			theBin = bestBin;
		}
		std::cout << "Pack object " << i << " in bin " << theBin.second << endl;

		theBin.first -= objectSize[i];
		if (theBin.first > 0) {
			theTree.insert(theBin);
		}
	}
}

void crossingDistribution(int theC[], int n) {
	int* k = new int[n + 1L];

	setK(theC, k, n);
	std::cout << "k is ";
	for (int i = 1; i <= n; ++i) {
		std::cout << k[i] << " ";
	}
	std::cout << std::endl;

	int theK = accumulate(k + 1, k + 1 + n, 0);

	ArrayList<int> theList(n);
	int* theA = new int[n + 1L],
		* theB = new int[n + 1L],
		* theX = new int[n + 1L];

	int crossingNeeded = theK / 2;

	int currentWire = n;
	while (crossingNeeded > 0) {
		if (k[currentWire] < crossingNeeded) {
			theList.insert(k[currentWire], currentWire);
			crossingNeeded -= k[currentWire];
		}
		else {
			theList.insert(crossingNeeded, currentWire);
			crossingNeeded = 0;
		}
		--currentWire;
	}

	for (int i = 1; i <= currentWire; ++i) {
		theX[i] = i;
	}

	for (int i = currentWire + 1; i <= n; ++i) {
		theX[i] = theList.get(i - currentWire - 1);
	}

	for (int i = 1; i <= n; ++i) {
		theA[theX[i]] = i;
	}

	for (int i = 1; i <= n; ++i) {
		theB[i] = theC[theX[i]];
	}

	std::cout << "A is ";
	for (int i = 1; i <= n; ++i) {
		std::cout << theA[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "B is ";
	for (int i = 1; i <= n; ++i) {
		std::cout << theB[i] << " ";
	}
	std::cout << std::endl;

	delete[] theA;
	delete[] theB;
	delete[] theX;
	delete[] k;
}

void setK(int theC[], int k[], int n) {
	for (int i = 1; i < n; ++i) {
		k[i] = 0;
		for (int j = i + 1; j <= n; ++j) {
			if (theC[j] < theC[i]) {
				++k[i];
			}
		}
	}
	k[n] = 0;
}

void crossingDistribution2(int theC[], int n) {
	int* k = new int[n + 1L];

	setK2(theC, k, n);
	std::cout << "k is ";
	for (int i = 1; i <= n; ++i) {
		std::cout << k[i] << " ";
	}
	std::cout << std::endl;

	int theK = accumulate(k + 1, k + 1 + n, 0);

	ArrayList<int> theList(n);
	int* theA = new int[n + 1L],
		* theB = new int[n + 1L],
		* theX = new int[n + 1L];

	int crossingNeeded = theK / 2;

	int currentWire = n;
	while (crossingNeeded > 0) {
		if (k[currentWire] < crossingNeeded) {
			theList.insert(k[currentWire], currentWire);
			crossingNeeded -= k[currentWire];
		}
		else {
			theList.insert(crossingNeeded, currentWire);
			crossingNeeded = 0;
		}
		--currentWire;
	}

	for (int i = 1; i <= currentWire; ++i) {
		theX[i] = i;
	}

	for (int i = currentWire + 1; i <= n; ++i) {
		theX[i] = theList.get(i - currentWire - 1);
	}

	for (int i = 1; i <= n; ++i) {
		theA[theX[i]] = i;
	}

	for (int i = 1; i <= n; ++i) {
		theB[i] = theC[theX[i]];
	}

	std::cout << "A is ";
	for (int i = 1; i <= n; ++i) {
		std::cout << theA[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "B is ";
	for (int i = 1; i <= n; ++i) {
		std::cout << theB[i] << " ";
	}
	std::cout << std::endl;

	delete[] theA;
	delete[] theB;
	delete[] theX;
	delete[] k;
}

void setK2(int theC[], int k[], int n) {
	IndexedBinarySearchTree<int, int> ibst;
	for (int i = n; i >= 1; --i) {
		ibst.insert({ theC[i], theC[i] });
		k[i] = ibst.getIndex(theC[i]);
	}
}

void indexText(const std::string& inFile, const std::string& outFile) {
	std::ifstream ifs(inFile);
	std::vector<std::string> text;
	std::string s;
	while (std::getline(ifs, s)) {
		text.push_back(s);
	}
	ifs.close();

	BinarySearchTree<std::string, std::set<int>> bst;
	for (int i = 0; i < text.size(); ++i) {
		std::istringstream iss(text[i]);
		std::string word;
		while (iss >> word) {
			auto p = bst.find(word);
			if (p) {
				p->second.insert(i+1);
			}
			else {
				bst.insert({ word, {i+1} });
			}
		}
	}

	std::ofstream ofs(outFile);
	auto f = [&ofs](BinaryTreeNode<std::pair<std::string, std::set<int>>>* t) {
		ofs << t->element.first << ": ";
		std::for_each(t->element.second.begin(), t->element.second.end(), [&ofs](int n) {ofs << n << " "; });
		ofs << std::endl;
	};
	bst.inOrder(f);
	//bst.output(std::cout);
	ofs.close();
}

std::ostream& operator<<(std::ostream& out, std::set<int>& v) {
	std::for_each(v.begin(), v.end(), [&out](int n) {out << n << " "; });
	return out;
}

std::ostream& operator<<(std::ostream& out, std::pair<std::string, std::set<int>>& p) {
	out << p.first << ": ";
	std::for_each(p.second.begin(), p.second.end(), [&out](int n) {out << n << " "; });
	out << std::endl;
	return out;
}