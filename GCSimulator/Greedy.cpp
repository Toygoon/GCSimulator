/* Greedy Algorithm Header for Flash Storage
 * from "Cleaning policies in mobile computers using flash memory"
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#include "Greedy.h"

Greedy::Greedy() {
	// Constructors to initalize values
}

// To sort the second value in tuples by descending order
static bool cmpInvalid(pair<int, double>& v1, pair<int, double>& v2) {
	return get<1>(v1) > get<1>(v2);
}

// To sort the second value in tuples by descending order
static bool cmpEraseCount(pair<int, int>& v1, pair<int, int>& v2) {
	return get<1>(v1) < get<1>(v2);
}

void Greedy::calcVictims(Storage* s) {
	// Temporary value for saving percentage
	double tmp;

	// calcInvalids calculates the list : invalids, victims
	// Calculate; invalids
	for (int i = 0; i < PAGE_COUNT; i++) {
		tmp = 0;
		for (int j = 0; j < BLOCK_COUNT; j++)
			if (s->getPage(i)->getPageBlock()[j].getBlockStatus() == BlockStatus::BLOCK_INVALID)
				tmp++;
		tmp /= BLOCK_COUNT;
		// Push it to the tuple
		this->invalids.push_back({ i, tmp });
	}

	// Calculate; victims, validInVictims
	for (int i = 0; i < PAGE_COUNT; i++) {
		// Find out valid blocks, victims
		// 1 : all blocks are invalid, so just be deleted
		// 0.x : needs to work gc.
		tmp = this->invalids.at(i).second;
		if (0 < tmp && tmp < 1) {
			// Save current pageNum
			this->victims.push_back(i);

			for (int j = 0; j < BLOCK_COUNT; j++)
				if (s->getPage(i)->getPageBlock()[j].getBlockStatus() == BlockStatus::BLOCK_VALID)
					this->validInVictims->push_back(j);
		}
	}

	// Sort the values by percentage
	sort(this->invalids.begin(), this->invalids.end(), cmpInvalid);
}

void Greedy::calcFreeSpace(Storage* s) {
	// Tempoary buffer for saving free status of flash storage
	double* buffer = new double[BLOCK_COUNT];
	int totalEc;

	for (int i = 0; i < PAGE_COUNT; i++) {
		buffer[i] = 0;
		for (int j = 0; j < BLOCK_COUNT; j++) {
			if (s->getPage(i)->getPageBlock()[j].getBlockStatus() == BlockStatus::BLOCK_FREE) {
				buffer[i]++;
			}
		}
	}

	// calcFreeSpace calculates the list : freeSpace
	for (int i = 0; i < PAGE_COUNT; i++) {
		totalEc = 0;
		if (buffer[i] == BLOCK_COUNT) {
			for (int j = 0; j < BLOCK_COUNT; j++)
				totalEc += s->getPage(i)->getPageBlock()[j].getEraseCount();
			this->freePages.push_back({ i, totalEc });
		}
	}

	// Sort the values by erase count
	sort(this->freePages.begin(), this->freePages.end(), cmpEraseCount);
}

void Greedy::cleanAllInvalids(Storage** s) {
	// Format data if a page has only invalid blocks
	for (int i = 0; i < this->invalids.size(); i++) {
		if (invalids.at(i).second == 1)
			(*s)->formatData(invalids.at(i).first, invalids.at(i).first);
	}
}

/* In-place-update() algorithms
** in Cleaning policies in mobile computers using flash memory */
void Greedy::greedyMain(Storage** s) {
	int freePagesPos = 0, freePageNum, victimPageNum;
	Block* systemBuffer;

	/* Select a victim segment for cleaning;
	** Identify valid data in the segment; */
	this->calcVictims(*s);

	// Just gc
	this->cleanAllInvalids(s);

	// Calculate free spaces
	this->calcFreeSpace(*s);

	// Check the block has enough pages
	if (freePages.size() == 0) {
		cout << "There's no free pages in the storage." << endl;
		return;
	}

	for (int i = 0; i < this->victims.size(); i++)  {
		freePageNum = this->freePages.at(freePagesPos).first;
		victimPageNum = victims.at(i);
		cout << "Victim page " << victimPageNum << " has selected." << endl;

		systemBuffer = new Block[BLOCK_COUNT];
		for (int j = 0; j < BLOCK_COUNT; j++) {
			/* Read all data in the segment into a system buffer; */
			// memcpy(systemBuffer, (*s)->getPage(victimNum), sizeof(Page)); // not working memcpy
			systemBuffer[j].setData((*s)->getPage(victimPageNum)->getPageBlock()[j].getData());

			/* Update data in the system buffer; */
			if ((*s)->getPage(victimPageNum)->getPageBlock()[j].getBlockStatus() == BlockStatus::BLOCK_INVALID) {
				systemBuffer[j].formatBlock();
				systemBuffer[j].setBlockStatus(BlockStatus::BLOCK_INVALID);
			}
		}

		/* Erase the segment; */
		(*s)->formatData(victimPageNum, victimPageNum);

		/* Write back all data from system buffer to segment; */
		cout << "Writing buffer into the " << freePageNum << " page." << endl;
		for (int j = 0; j < BLOCK_COUNT; j++)
			if (!(systemBuffer[j].getBlockStatus() == BlockStatus::BLOCK_INVALID))
			(*s)->getPage(freePageNum)->getPageBlock()[j].setData(systemBuffer[j].getData());

		freePagesPos++;
		// No more free spaces
		if (freePagesPos > freePages.size())
			break;
	}
	cout << endl;

}