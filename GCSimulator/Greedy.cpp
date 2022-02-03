#include "Greedy.h"

Greedy::Greedy() {
	this->invalids = new double[PAGE_COUNT];
	for (int i = 0; i < PAGE_COUNT; i++)
		this->invalids[i] = 0;
}

void Greedy::calcVictim(Storage* s) {
	for (int i = 0; i < PAGE_COUNT; i++) {
		for (int j = 0; j < BLOCK_COUNT; j++) {
			if (s->getPage(i)->getPageBlock()[j].getBlockStatus() == BlockStatus::BLOCK_INVALID) {
				this->invalids[i]++;
				this->victimMap.insert(make_pair(i, j));
			}
		}
		invalids[i] /= BLOCK_COUNT;
	}
}

