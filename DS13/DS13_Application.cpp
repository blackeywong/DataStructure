#include<algorithm>

#include "DS13_Application.h"
#include "CompleteWinnerTree.h"

void firstFitPack(int* objectSize, int numberOfObjects, int binCapacity) {
	int n = numberOfObjects;

	BinType* bin = new BinType[n + 1];
	for (int i = 1; i <= n; ++i) {
		bin[i].unusedCapacity = binCapacity;
	}
	CompleteWinnerTree<BinType> winTree(bin, n, false);

	for (int i = 1; i <= n; ++i) {
		int child = 2;
		while (child < n) {
			int winner = winTree.winner(child);
			if (bin[winner].unusedCapacity < objectSize[i]) {
				++child;
			}
			child *= 2;
		}

		int binToUse;
		child /= 2;
		if (child < n) {
			binToUse = winTree.winner(child);
			if (binToUse > 1 && bin[binToUse - 1].unusedCapacity >= objectSize[i]) {
				--binToUse;
			}
		}
		else {
			binToUse = winTree.winner(child / 2);
		}

		//std::cout << "Pack object " << i << " in bin " << binToUse << std::endl;
		bin[binToUse].unusedCapacity -= objectSize[i];
		winTree.rePlay(binToUse);
	}
}

//Exercise 25
void firstFitPack2(int* objectSize, int numberOfObjects, int binCapacity) {
	int n = numberOfObjects;

	BinType* bin = new BinType[n + 1];
	for (int i = 1; i <= n; ++i) {
		bin[i].unusedCapacity = binCapacity;
	}
	CompleteWinnerTree<BinType> winTree(bin, n, false);

	int rightMost = 1;
	int binToUse = 1;
	for (int i = 1; i <= n; ++i) {
		int child;
		if (rightMost == 1) {
			child = winTree.getParentForExt(1);
		}
		else {
			child = winTree.getCommonAncestor(1, rightMost, true);
		}
		if (bin[winTree.winner(child)].unusedCapacity < objectSize[i]) {
			++rightMost;
			binToUse = rightMost;
		}
		else {
			while (child < n) {
				int winner = winTree.winner(child);
				if (bin[winner].unusedCapacity < objectSize[i]) {
					++child;
				}
				child *= 2;
			}
			child /= 2;
			if (child < n) {
				binToUse = winTree.winner(child);
				if (binToUse > 1 && bin[binToUse - 1].unusedCapacity >= objectSize[i]) {
					--binToUse;
				}
			}
			else {
				binToUse = winTree.winner(child / 2);
			}
		}
		if (rightMost < binToUse) {
			rightMost = binToUse;
		}

		//std::cout << "Pack object " << i << " in bin " << binToUse << std::endl;
		bin[binToUse].unusedCapacity -= objectSize[i];
		winTree.rePlay(binToUse);

	}
}

//Exercise 26
void firstFitPack3(int* objectSize, int numberOfObjects, int binCapacity) {
	int n = numberOfObjects;

	BinType* bin = new BinType[n + 1];
	for (int i = 1; i <= n; ++i) {
		bin[i].unusedCapacity = binCapacity;
	}
	CompleteWinnerTree<BinType> winTree(bin, n, false);

	for (int i = 1; i <= n; ++i) {
		int parent = winTree.root();
		int child = winTree.leftChild(parent);
		while (child != 0) {
			int winner = winTree.winner(child);
			if (bin[winner].unusedCapacity < objectSize[i]) {
				child = winTree.rightChild(parent);
				if (child == 0)
					break;
			}
			parent = child;
			child = winTree.leftChild(parent);
		}

		int binToUse;
		if (parent < n) {
			binToUse = winTree.winner(parent);
			if (binToUse > 1 && bin[binToUse - 1].unusedCapacity >= objectSize[i]) {
				--binToUse;
			}
		}
		else {
			binToUse = winTree.winner(parent / 2);
		}

		std::cout << "Pack object " << i << " in bin " << binToUse << std::endl;
		bin[binToUse].unusedCapacity -= objectSize[i];
		winTree.rePlay(binToUse);
	}
}

//Exercise 28
void firstFitDecreasingPack(int* objectSize, int numberOfObjects, int binCapacity) {
	//std::sort(objectSize + 1, objectSize + numberOfObjects + 1, [](const int i, const int j) {return i >= j; });
	std::sort(objectSize + 1, objectSize + numberOfObjects + 1, std::greater<int>());

	int n = numberOfObjects;

	BinType* bin = new BinType[n + 1];
	for (int i = 1; i <= n; ++i) {
		bin[i].unusedCapacity = binCapacity;
	}
	CompleteWinnerTree<BinType> winTree(bin, n, false);

	int rightMost = 1;
	int binToUse = 1;
	for (int i = 1; i <= n; ++i) {
		int child;
		if (rightMost == 1) {
			child = winTree.getParentForExt(1);
		}
		else {
			child = winTree.getCommonAncestor(1, rightMost, true);
		}
		if (bin[winTree.winner(child)].unusedCapacity < objectSize[i]) {
			++rightMost;
			binToUse = rightMost;
		}
		else {
			while (child < n) {
				int winner = winTree.winner(child);
				if (bin[winner].unusedCapacity < objectSize[i]) {
					++child;
				}
				child *= 2;
			}
			child /= 2;
			if (child < n) {
				binToUse = winTree.winner(child);
				if (binToUse > 1 && bin[binToUse - 1].unusedCapacity >= objectSize[i]) {
					--binToUse;
				}
			}
			else {
				binToUse = winTree.winner(child / 2);
			}
		}
		if (rightMost < binToUse) {
			rightMost = binToUse;
		}

		//std::cout << "Pack object " << i << " in bin " << binToUse << std::endl;
		bin[binToUse].unusedCapacity -= objectSize[i];
		winTree.rePlay(binToUse);

	}
}

//Exercise 29
void nextFitPack(int* objectSize, int numberOfObjects, int binCapacity) {
	int n = numberOfObjects;

	BinType* bin = new BinType[n + 1];
	for (int i = 1; i <= n; ++i) {
		bin[i].unusedCapacity = binCapacity;
	}
	CompleteWinnerTree<BinType> winTree(bin, n, false);

	//std::cout << "Pack object 1 in bin 1" << std::endl;
	bin[1].unusedCapacity -= objectSize[1];
	winTree.rePlay(1);

	int rightMost = 1;
	int binToUse = 1;
	for (int i = 2; i <= n; ++i) {
		int j = binToUse + 1;
		if (j <= rightMost && bin[j].unusedCapacity >= objectSize[i]) {
			binToUse = j;
		}
		else if (j + 1 <= n && j + 1 <= rightMost && bin[j+1].unusedCapacity >= objectSize[i]) {
			binToUse = j+1;
		}
		else {//search in right sub-tree
			int p = winTree.getParentForExt(binToUse);
			if (p != winTree.offset && winTree.offset != n -1 && p != winTree.s - 1) {//if there IS right sub-tree
				if (p == n - 1 && p != 1)//p is the last tree node
					p /= 2;
				while (p > 1 && bin[winTree.tree[p + 1]].unusedCapacity < objectSize[i]) {
					p /= 2;
				}
			}
			if (p != 1//not whole tree
				&& p != winTree.offset && winTree.offset != n - 1 && p != winTree.s - 1 //there IS right sub-tree
				&&  winTree.winner(p + 1) <= rightMost) { //and the bin in right sub-tree is used
				binToUse = winTree.winner(p + 1);
			}
			else {//search in left sub-tree
				if (binToUse == 1) {//if no left sub-tree
					if (bin[1].unusedCapacity < objectSize[i]) {
						binToUse = rightMost + 1;
					}//else binToUse = 1;
				}
				else {
					int child = winTree.getCommonAncestor(1, binToUse, true);
					if (bin[winTree.tree[child]].unusedCapacity >= objectSize[i]) {
						while (child < n) {
							int winner = winTree.winner(child);
							if (bin[winner].unusedCapacity < objectSize[i]) {
								++child;
							}
							child *= 2;
						}
						child /= 2;
						if (child < n) {
							binToUse = winTree.winner(child);
							if (binToUse > 1 && bin[binToUse - 1].unusedCapacity >= objectSize[i]) {
								--binToUse;
							}
						}
						else {
							binToUse = winTree.winner(child / 2);
						}
					}
					else {
						binToUse = rightMost + 1;
					}
				}
			}
			
		}
		if (rightMost < binToUse) {
			rightMost = binToUse;
		}

		//std::cout << "Pack object " << i << " in bin " << binToUse << std::endl;
		bin[binToUse].unusedCapacity -= objectSize[i];
		winTree.rePlay(binToUse);
	}
}

//Exercise 30
void rightFitPack(int* objectSize, int numberOfObjects, int binCapacity) {
	int n = numberOfObjects;

	BinType* bin = new BinType[n + 1];
	for (int i = 1; i <= n; ++i) {
		bin[i].unusedCapacity = binCapacity;
	}
	CompleteWinnerTree<BinType> winTree(bin, n, false);

	int rightMost = 1;
	int binToUse = 1;
	for (int i = 1; i <= n; ++i) {
		int child;
		if (rightMost == 1) {
			child = winTree.getParentForExt(1);
		}
		else {
			child = winTree.getCommonAncestor(1, rightMost, true);
		}
		if (bin[winTree.winner(child)].unusedCapacity < objectSize[i]) {
			++rightMost;
			binToUse = rightMost;
		}
		else {
			child *= 2;
			while (child < n) {
				if (child + 1 < n - 1)
					++child;
				int winner = winTree.winner(child);
				if (bin[winner].unusedCapacity < objectSize[i]) {
					--child;
				}
				child *= 2;
			}
			child /= 2;
			if (child < n) {
				binToUse = winTree.winner(child);
				if (rightMost > 1 && binToUse + 1 <= rightMost && bin[binToUse + 1].unusedCapacity >= objectSize[i]) {
					++binToUse;
				}
				else if (binToUse > 1 && bin[binToUse - 1].unusedCapacity >= objectSize[i]) {
					--binToUse;
				}
			}
			else {
				binToUse = winTree.winner(child / 2);
			}
		}
		if (rightMost < binToUse) {
			rightMost = binToUse;
		}

		std::cout << "Pack object " << i << " in bin " << binToUse << std::endl;
		bin[binToUse].unusedCapacity -= objectSize[i];
		winTree.rePlay(binToUse);

	}
}

bool greater_equal(const BinType& bt1, const BinType& bt2) {
	return bt1 >= bt2;
}

bool less_equal(const BinType& bt1, const BinType& bt2) {
	return bt1 <= bt2;
}


TestPacking::TestPacking(int theSize) :size(theSize) {
	int lowBound = 1;
	int highBound = 50;
	std::default_random_engine e(static_cast<unsigned int>(time(nullptr)));
	std::uniform_int_distribution<int> u(lowBound, highBound);

	objects = new int[size + 1];
	for (int k = 1; k <= size; ++k) {
		objects[k] = u(e);
	}
}

void TestPacking::test(PACK_METHOD method) {
	clock_t start, finish;
	double insertTime = 0.0;
	ItemNode* items = new ItemNode[size];
	for (int i = 0; i < size; ++i) {
		items[i].id = i + 1;
		items[i].space = objects[i + 1];
	}
	start = clock();
	switch (method) {
	case FIRST_FIT:					firstFitPack(objects, size, 100); break;
	case FIRST_FIT2:				firstFitPack2(objects, size, 100); break;
	case FIRST_FIT_DECREASING:		firstFitDecreasingPack(objects, size, 100); break;
	case WORST_FIT:					packItems(items, size, size * 2 / 3, 100); break;
	case NEXT_FIT:					nextFitPack(objects, size, 100); break;
	case RIGHT_FIT:					rightFitPack(objects, size, 100); break;
	}
	finish = clock();
	std::cout << size << " Time cost: " << (double)(finish - start) / CLK_TCK << std::endl;
}