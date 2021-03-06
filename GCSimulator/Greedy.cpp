/* Greedy Algorithm Header for Flash Storage
 * from "Cleaning policies in mobile computers using flash memory"
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#include "Greedy.hpp"

Greedy::Greedy(Storage** s) {
	// Calculate pageStats
	for (int i = 0; i < (*s)->totalBlockCount; i++) {
		// Save location to counts of each page status
		int pageCurrentStatus[3] = { 0, 0, 0 };

		for (int j = 0; j < PAGES_PER_BLOCK; j++) {
			switch ((*s)->getBlock(i)->getPage()[j].getPageStatus()) {
			case PageStatus::PAGE_VALID:
				pageCurrentStatus[0]++;
				break;
			case PageStatus::PAGE_INVALID:
				pageCurrentStatus[1]++;
				break;
			case PageStatus::PAGE_FREE:
				pageCurrentStatus[2]++;
				break;
			}
		}
		this->pageStats.push_back(make_tuple(i, PageStatus::PAGE_VALID, pageCurrentStatus[0]));
		this->pageStats.push_back(make_tuple(i, PageStatus::PAGE_INVALID, pageCurrentStatus[1]));
		this->pageStats.push_back(make_tuple(i, PageStatus::PAGE_FREE, pageCurrentStatus[2]));
	}
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

	for (int i = 0; i < this->pageStats.size(); i++) {
		PAGE_STAT p = this->pageStats[i];
		// Grab only invalid pages
		if ((get<1>(p) == PageStatus::PAGE_INVALID) && (get<2>(p) > 0)) {
			// Calculate percentages
			tmp = (double)get<2>(p) / (double)PAGES_PER_BLOCK * 100.0;
			// Puch each pair
			invalids.push_back(make_pair(get<0>(p), tmp));

			// Add victims; not 0, also not 100 percents
			if (tmp > 0 && tmp < 100)
				victims.push_back(get<0>(p));
		}
	}

	// Sort the values by percentage
	sort(this->invalids.begin(), this->invalids.end(), cmpInvalid);
}

void Greedy::calcFreeSpace(Storage* s) {
	int tmp;

	for (int i = 0; i < this->pageStats.size(); i++) {
		PAGE_STAT p = this->pageStats[i];
		// Grab only free pages
		if (get<1>(p) == PageStatus::PAGE_FREE) {
			// Grab only full of free pages in a block
			if (get<2>(p) == PAGES_PER_BLOCK) {
				// Calculate erase count
				tmp = 0;
				for (int j = 0; j < PAGES_PER_BLOCK; j++)
					tmp += s->getBlock(get<0>(p))->getPage()[j].getEraseCount();

				// Puch each pair
				freeBlocks.push_back(make_pair(get<0>(p), 0));
			}
		}
	}

	// Sort the values by erase count
	sort(this->freeBlocks.begin(), this->freeBlocks.end(), cmpEraseCount);
}

void Greedy::cleanAllInvalids(Storage** s) {
	int count = 0;
	// Format data if a block has only invalid pages
	for (int i = 0; i < this->invalids.size(); i++) {
		// RAW level format, format only 100 percent
		if (this->invalids.at(i).second == 100) {
			count++;
			for (int j = 0; j < PAGES_PER_BLOCK; j++)
				(*s)->getBlock(this->invalids[i].first)->getPage()[j].formatPage(true);
		}
	}

	cout << "Invalid " << count << " blocks cleaned" << endl << endl;
}

/* In-place-update() algorithms
** in Cleaning policies in mobile computers using flash memory */
void Greedy::greedyMain(Storage** s) {
	int freeBlocksPos = 0, freeBlockNum, victimBlockNum;
	Page* systemBuffer;

	// Calculate free spaces
	this->calcFreeSpace(*s);

	/* Select a victim segment for cleaning;
	** Identify valid data in the segment; */
	this->calcVictims(*s);

	// Calculate free spaces
	this->calcFreeSpace(*s);

	// Check the page has enough blocks
	if (this->freeBlocks.size() == 0) {
		cout << "There's no free blocks in the storage." << endl;
		return;
	}

	// Clean 100% invalid blocks
	this->cleanAllInvalids(s);

	// Swap valid part to other part
	for (int i = 0; i < this->victims.size(); i++) {
		freeBlockNum = this->freeBlocks.at(freeBlocksPos).first;
		victimBlockNum = victims.at(i);
		cout << "Victim block " << victimBlockNum << " has selected." << endl;

		systemBuffer = new Page[PAGES_PER_BLOCK];
		for (int j = 0; j < PAGES_PER_BLOCK; j++) {
			/* Read all data in the segment into a system buffer; */
			systemBuffer[j].setData((*s)->getBlock(victimBlockNum)->getPage()[j].getData());

			/* Update data in the system buffer; */
			if ((*s)->getBlock(victimBlockNum)->getPage()[j].getPageStatus() == PageStatus::PAGE_INVALID)
				systemBuffer[j].setPageStatus(PageStatus::PAGE_INVALID);
		}

		/* Erase the segment; */
		for (int j = 0; j < PAGES_PER_BLOCK; j++)
			(*s)->getBlock(victimBlockNum)->getPage()[j].formatPage(true);


		/* Write back all data from system buffer to segment; */
		cout << "Writing buffer into the " << freeBlockNum << " block." << endl;
		for (int j = 0; j < PAGES_PER_BLOCK; j++)
			// Copy only valid pages to the free block
			if (!(systemBuffer[j].getPageStatus() == PageStatus::PAGE_INVALID))
				(*s)->getBlock(freeBlockNum)->getPage()[j].setData(systemBuffer[j].getData());

		freeBlocksPos++;
	}
}