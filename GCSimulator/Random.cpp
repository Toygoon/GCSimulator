#include "Random.h"

void writeRandom(Storage** s) {
	// Random initialize
	random_device rd;
	mt19937_64 gen(rd());

	uniform_int_distribution<int> dis(0, MAX_ERASURE_LIMIT);

	for (int i = 0; i < PAGE_COUNT; i++) {
		for (int j = 0; j < BLOCK_COUNT; j++) {
			string data =  ( * s)->getPage(i)->getBlock(j).getData();
			for (int k = 0; k < dis(gen); k++)
				(*s)->getPage(i)->getBlock(j).setData("fafF");
		}
	}
}