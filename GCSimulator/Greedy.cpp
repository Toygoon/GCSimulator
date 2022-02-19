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
	for (int i = 0; i < BLOCK_COUNT; i++) {
		tmp = 0;
		for (int j = 0; j < PAGE_SIZE; j++)
			if (s->getBlock(i)->getBlockPage()[j].getPageStatus() == PageStatus::PAGE_INVALID)
				tmp++;
		tmp /= PAGE_SIZE;
		// Push it to the tuple
		this->invalids.push_back({ i, tmp });
	}

	// Calculate; victims, validInVictims
	for (int i = 0; i < BLOCK_COUNT; i++) {
		// Find out valid pages, victims
		// 1 : all pages are invalid, so just be deleted
		// 0.x : needs to work gc.
		tmp = this->invalids.at(i).second;
		if (0 < tmp && tmp < 1) {
			// Save current blockNum
			this->victims.push_back(i);

			for (int j = 0; j < PAGE_SIZE; j++)
				if (s->getBlock(i)->getBlockPage()[j].getPageStatus() == PageStatus::PAGE_VALID)
					this->validInVictims->push_back(j);
		}
	}

	// Sort the values by percentage
	sort(this->invalids.begin(), this->invalids.end(), cmpInvalid);
}

void Greedy::calcFreeSpace(Storage* s) {
	// Tempoary buffer for saving free status of flash storage
	double* buffer = new double[PAGE_SIZE];
	int totalEc;

	for (int i = 0; i < BLOCK_COUNT; i++) {
		buffer[i] = 0;
		for (int j = 0; j < PAGE_SIZE; j++) {
			if (s->getBlock(i)->getBlockPage()[j].getPageStatus() == PageStatus::PAGE_FREE) {
				buffer[i]++;
			}
		}
	}

	// calcFreeSpace calculates the list : freeSpace
	for (int i = 0; i < BLOCK_COUNT; i++) {
		totalEc = 0;
		if (buffer[i] == PAGE_SIZE) {
			for (int j = 0; j < PAGE_SIZE; j++)
				totalEc += s->getBlock(i)->getBlockPage()[j].getEraseCount();
			this->freeBlocks.push_back({ i, totalEc });
		}
	}

	// Sort the values by erase count
	sort(this->freeBlocks.begin(), this->freeBlocks.end(), cmpEraseCount);
}

void Greedy::cleanAllInvalids(Storage** s) {
	// Format data if a block has only invalid pages
	for (int i = 0; i < this->invalids.size(); i++) {
		if (invalids.at(i).second == 1)
			(*s)->formatData(invalids.at(i).first, invalids.at(i).first);
	}
}

/* In-place-update() algorithms
** in Cleaning policies in mobile computers using flash memory */
void Greedy::greedyMain(Storage** s) {
	int freeBlocksPos = 0, freeBlockNum, victimBlockNum;
	Page* systemBuffer;

	/* Select a victim segment for cleaning;
	** Identify valid data in the segment; */
	this->calcVictims(*s);

	// Just gc
	this->cleanAllInvalids(s);

	// Calculate free spaces
	this->calcFreeSpace(*s);

	// Check the page has enough blocks
	if (freeBlocks.size() == 0) {
		cout << "There's no free blocks in the storage." << endl;
		return;
	}

	for (int i = 0; i < this->victims.size(); i++)  {
		freeBlockNum = this->freeBlocks.at(freeBlocksPos).first;
		victimBlockNum = victims.at(i);
		cout << "Victim block " << victimBlockNum << " has selected." << endl;

		systemBuffer = new Page[PAGE_SIZE];
		for (int j = 0; j < PAGE_SIZE; j++) {
			/* Read all data in the segment into a system buffer; */
			// memcpy(systemBuffer, (*s)->getBlock(victimNum), sizeof(Block)); // not working memcpy -> TODO: use copy constuctor later
			systemBuffer[j].setData((*s)->getBlock(victimBlockNum)->getBlockPage()[j].getData());

			/* Update data in the system buffer; */
			if ((*s)->getBlock(victimBlockNum)->getBlockPage()[j].getPageStatus() == PageStatus::PAGE_INVALID) {
				systemBuffer[j].formatPage();
				systemBuffer[j].setPageStatus(PageStatus::PAGE_INVALID);
			}
		}

		/* Erase the segment; */
		(*s)->formatData(victimBlockNum, victimBlockNum);

		/* Write back all data from system buffer to segment; */
		cout << "Writing buffer into the " << freeBlockNum << " block." << endl;
		for (int j = 0; j < PAGE_SIZE; j++)
			// Copy only valid pages to the free block
			if (!(systemBuffer[j].getPageStatus() == PageStatus::PAGE_INVALID))
			(*s)->getBlock(freeBlockNum)->getBlockPage()[j].setData(systemBuffer[j].getData());

		freeBlocksPos++;
		// No more free spaces
		if (freeBlocksPos > freeBlocks.size())
			break;
	}

	cout << endl;
}