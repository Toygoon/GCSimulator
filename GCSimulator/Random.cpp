#include "Random.hpp"

void writeRandom(Storage** s) {
	// Random initialize
	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<> dist(0, MAX_ERASURE_LIMIT);
	vector<int> random_nums;

	for (int i = 1; i < MAX_ERASURE_LIMIT * MAX_ERASURE_LIMIT; i *= 10) {
		random_nums.reserve(i);

		for (int j = 0; j < i; j++)
			random_nums.push_back(dist(gen));
	}

	for (int i = 0; i < PAGES_PER_BLOCK; i++) {
		for (int j = 0; j < PAGE_SIZE; j++) {
			string data =  ( * s)->getBlock(i)->getBlockPage()[j].getData();
			for (int k = 0; k < random_nums.at(j); k++)
				(*s)->getBlock(i)->getBlockPage()[j].setData(data);
		}
	}
}