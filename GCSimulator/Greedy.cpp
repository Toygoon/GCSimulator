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
			for (int j = 0; j < PAGES_PER_BLOCK; j++) {
				(*s)->getBlock(this->invalids[i].first)->getPage()[j].setData("");
				(*s)->getBlock(this->invalids[i].first)->getPage()[j].setPageStatus(PageStatus::PAGE_FREE);
			}
		}
	}

	cout << "Invalid " << count << " blocks cleaned" << endl;
}

/* In-place-update() algorithms
** in Cleaning policies in mobile computers using flash memory */
void Greedy::greedyMain(Storage** s) {
	// Calculate free spaces
	this->calcFreeSpace(*s);

	/* Select a victim segment for cleaning;
	** Identify valid data in the segment; */
	this->calcVictims(*s);

	// Calculate free spaces
	this->calcFreeSpace(*s);

	// Check the page has enough blocks
	if (freeBlocks.size() == 0) {
		cout << "There's no free blocks in the storage." << endl;
		return;
	}

	this->cleanAllInvalids(s);
}