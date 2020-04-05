#include "HashTable.h"


double TestHashTable::realProbingUnsuccess(const HashTable<int, int>& ht, int* keys) {
	int total = 0;
	for (int i = 0; i < ht.divisor; ++i) {
		int count = 0;
		int j = i;
		int k = 1;
		do {
			++count;
			if (ht.table[j] == nullptr)
				break;

			if (ht.randomProbing) {
				j = (i + ht.adder[k]) % ht.divisor;
				++k;
			}
			else {
				j = (j + 1) % ht.divisor;
			}
		} while (j != i);
		total += count;
	}
	return  (double)total / ht.divisor;
}

double TestHashTable::realProbingSuccess(const HashTable<int, int>& ht, int* keys) {
	int total = 0;
	for (int i = 0; i < ht.dSize; ++i) {
		int count = 0;
		int j = (int)ht.hash_key(keys[i]) % ht.divisor;
		if (j < 0)
			j += ht.divisor;
		int k = 1;
		do {
			++count;
			if (ht.table[j] == nullptr || ht.table[j]->first == keys[i])
				break;

			if (ht.randomProbing) {
				j = (i + ht.adder[k]) % ht.divisor;
				++k;
			}
			else {
				j = (j + 1) % ht.divisor;
			}
		} while (j != i);
		total += count;
	}
	return (double)total / ht.dSize;
}

void TestHashTable::run(int loopTotal, int loopReal) {

	for (int i = 0; i < loopTotal; ++i) {
		std::default_random_engine e(static_cast<unsigned int>(time(nullptr)));
		std::uniform_int_distribution<int> u(23, 32765);
		//std::uniform_int_distribution<int> u(1, 5);
		int divisor = u(e);
		if (divisor < 0)
			divisor = -divisor;
		if (divisor % 2 == 0)
			divisor += 1;

		int record = u(e) % divisor;
		if (record < 0)
			record = -record;

		std::cout << "Bucket number: " << divisor << "; Record number: " << record << std::endl;
		//cal linear
		std::cout << "\tUnsuccess\tSuccess" << std::endl;
		std::cout << "Calculated Unsuccess/Success Linear Probling" << std::endl;;
		printf("\t%8.3f\t%8.3f\n", calLinearProbingUnsuccess(divisor, record), calLinearProbingSuccess(divisor, record));
		std::cout << std::endl;
		//real linear
		std::cout << "Real" << std::endl;
		for (int j = 0; j < loopReal; ++j) {
			int* keys = new int[record];
			HashTable<int, int> ht(divisor);
			for (int k = 0; k < record; ++k) {
				keys[k] = u(e) % divisor;
				if (keys[k] < 0)
					keys[k] = -keys[k];
				ht.insert({ keys[k], k });
			}
			printf("\t%8.3f\t%8.3f\n", realProbingUnsuccess(ht, keys), realProbingSuccess(ht, keys));
			delete keys;
		}
		std::cout << std::endl;
		//cal random
		std::cout << "Calculated Unsuccess/Success Random Probling" << std::endl;;
		printf("\t%8.3f\t%8.3f\n", calRandomProbingUnsuccess(divisor, record), calRandomProbingSuccess(divisor, record));
		std::cout << std::endl;
		//real random
		std::cout << "Real" << std::endl;
		for (int j = 0; j < loopReal; ++j) {
			int* keys = new int[record];
			HashTable<int, int> ht(divisor, true);
			for (int k = 0; k < record; ++k) {
				keys[k] = u(e) % divisor;
				if (keys[k] < 0)
					keys[k] = -keys[k];
				ht.insert({ keys[k],k });
			}
			printf("\t%8.3f\t%8.3f\n", realProbingUnsuccess(ht, keys), realProbingSuccess(ht, keys));
			delete keys;
		}
	}
}

void TestHashTable::listValues() {
	int divisor = 100;
	std::cout << "Load Factor\tUnsuccess\tSuccess" << std::endl;
	std::cout << "Calculated Unsuccess/Success Linear Probling" << std::endl;;
	for (int record = 10; record < divisor; record += 10) {
		printf("%8.1f\t%8.3f\t%8.3f\n", (double)record / divisor, calLinearProbingUnsuccess(divisor, record), calLinearProbingSuccess(divisor, record));
	}
	std::cout << std::endl;
	std::cout << "Calculated Unsuccess/Success Random Probling" << std::endl;;
	for (int record = 10; record < divisor; record += 10) {
		printf("%8.1f\t%8.3f\t%8.3f\n", (double)record / divisor, calRandomProbingUnsuccess(divisor, record), calRandomProbingSuccess(divisor, record));
	}
}
