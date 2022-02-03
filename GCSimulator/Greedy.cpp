/* Greedy Algorithm Header for Flash Storage
 * from "Cleaning policies in mobile computers using flash memory"
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#include "Greedy.h"

Greedy::Greedy() {
	// Constructors to initalize values.
	this->victimCounts = 0;
	this->invalids = new double[PAGE_COUNT];
	for (int i = 0; i < PAGE_COUNT; i++)
		this->invalids[i] = 0;
}

void Greedy::calcVictim(Storage* s) {
	// calcVictim calculates the list : invalids
	// Also calculates the value : victimCounts;
	for (int i = 0; i < PAGE_COUNT; i++) {
		for (int j = 0; j < BLOCK_COUNT; j++) {
			if (s->getPage(i)->getPageBlock()[j].getBlockStatus() == BlockStatus::BLOCK_INVALID) {
				this->invalids[i]++;
				victimCounts++;
			}
		}
		this->invalids[i] /= BLOCK_COUNT;
	}
}

void Greedy::calcFreeSpace(Storage* s) {
	// Tempoary buffer for saving free status of flash storage.
	double* buffer = new double[BLOCK_COUNT];

	for (int i = 0; i < PAGE_COUNT; i++) {
		buffer[i] = 0;
		for (int j = 0; j < BLOCK_COUNT; j++) {
			if (s->getPage(i)->getPageBlock()[j].getBlockStatus() == BlockStatus::BLOCK_FREE) {
				buffer[i]++;
			}
		}
	}

	// calcFreeSpace calculates the list : freeSpace
	for (int i = 0; i < PAGE_COUNT; i++)
		if (this->invalids[i] == BLOCK_COUNT)
			this->freeSpace.push_back(i);

	delete(buffer);
}

void Greedy::greedyMain(Storage** s) {
	this->calcVictim(*s);
	this->calcFreeSpace(*s);

	// Find out invalid segments
	// 1 : all blocks are invalid, so just delete
	// 0.x : needs to work gc.
	for (int i = 0; i < PAGE_COUNT; i++) {
		// todo here
	}
}