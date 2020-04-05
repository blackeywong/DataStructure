#ifndef _TESTHASHCHAIN_H
#define _TESTHASHCHAIN_H
#include "HashChain.h"
#include "HashChainsWithVector.h"

class TestHashChain {
public:
	double calProbingUnsuccess(int bucket, int record) { double f = (double)record / bucket; return f * (f + 3.0) / 2.0 / (f + 1.0); }
	double calProbingSuccess(int bucket, int record) { double f = (double)record / bucket; return 1.0 + 0.5 * f; }

	double realProbingUnsuccess(const HashChain<int, int>& ht, int* keys);
	double realProbingSuccess(const HashChain<int, int>& ht, int* keys);
	double realProbingUnsuccess(const HashChainsWithVector<int, int>& ht, int* keys);
	double realProbingSuccess(const HashChainsWithVector<int, int>& ht, int* keys);

	void run(int loopTotal, int loopReal);
};

double TestHashChain::realProbingUnsuccess(const HashChain<int, int>& ht, int* keys) {
	int total = 0;
	for (int i = 0; i < ht.divisor; ++i) {
		int sz = ht.table[i].size();
		total += (sz + 1) * (1 + sz + 1) / 2;
	}
	return (double)total / ht.divisor;
}

double TestHashChain::realProbingSuccess(const HashChain<int, int>& ht, int* keys) {
	int total = 0;
	for (int i = 0; i < ht.divisor; ++i) {
		int sz = ht.table[i].size();
		total += sz * (1 + sz) / 2;
	}

	return (double)total / ht.dSize;
}

double TestHashChain::realProbingUnsuccess(const HashChainsWithVector<int, int>& ht, int* keys) {
	int total = 0;
	for (int i = 0; i < ht.divisor; ++i) {
		int sz = ht.table[i]->size();
		total += (sz + 1) * (1 + sz + 1) / 2;
	}
	return (double)total / ht.divisor;
}

double TestHashChain::realProbingSuccess(const HashChainsWithVector<int, int>& ht, int* keys) {
	int total = 0;
	for (int i = 0; i < ht.divisor; ++i) {
		int sz = ht.table[i]->size();
		total += sz * (1 + sz) / 2;
	}

	return (double)total / ht.dSize;
}


void TestHashChain::run(int loopTotal, int loopReal) {

	for (int i = 0; i < loopTotal; ++i) {
		std::default_random_engine e(static_cast<unsigned int>(time(nullptr)));
		std::uniform_int_distribution<int> u(23, 32765);
		//std::uniform_int_distribution<int> u(1, 5);
		int divisor = u(e);
		if (divisor < 0)
			divisor = -divisor;
		if (divisor % 2 == 0)
			divisor += 1;

		int record = u(e);
		if (record < 0)
			record = -record;

		std::cout << "Bucket number: " << divisor << "; Record number: " << record << std::endl;
		//cal linear
		std::cout << "\tUnsuccess\tSuccess" << std::endl;
		std::cout << "Calculated Unsuccess/Success Linear Probling" << std::endl;;
		printf("\t%8.3f\t%8.3f\n", calProbingUnsuccess(divisor, record), calProbingSuccess(divisor, record));
		std::cout << std::endl;
		//real linear
		std::cout << "Real" << std::endl;
		for (int j = 0; j < loopReal; ++j) {
			int* keys = new int[record];
			HashChain<int, int> ht(divisor);
			HashChainsWithVector<int, int> hcwv(divisor);
			for (int k = 0; k < record; ++k) {
				keys[k] = u(e) % divisor;
				if (keys[k] < 0)
					keys[k] = -keys[k];
				ht.insert({ keys[k], k });
				hcwv.insert({ keys[k], k });
			}
			printf("HashChain\t\t%8.3f\t%8.3f\n", realProbingUnsuccess(ht, keys), realProbingSuccess(ht, keys));
			printf("HashChainWithVector\t%8.3f\t%8.3f\n", realProbingUnsuccess(hcwv, keys), realProbingSuccess(hcwv, keys));
			delete keys;
		}

	}
}

#endif