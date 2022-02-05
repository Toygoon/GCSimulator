/* The Simulation of Flash Storage
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#include "Storage.h"

Storage::Storage() {
	for (int i = 0; i < PAGE_COUNT; i++)
		this->pages.push_back(new Page(i));
}

Page* Storage::getPage(int pageNum) {
	return pages.at(pageNum);
}

vector<pair<int, double>> Storage::calcPageTimesAvg(void) {
	/* Returns pair of average in pages for their access time 
	vector's structure : <pageNum, average of access time> */

	vector<pair<int, double>> avg;
	double tmp;
	
	for (int i = 0; i < PAGE_COUNT; i++) {
		tmp = 0;
		for (int j = 0; j < BLOCK_COUNT; j++)
			tmp += this->getPage(i)->getPageBlock()[j].getAccessTime();
		tmp /= BLOCK_COUNT;

		avg.push_back({ i, tmp });
	}

	return avg;
}

void Storage::setPage(int pageNum, Page* p) {
	memcpy(this->pages[pageNum], p, sizeof(Page));
}

void Storage::printStat(void) {
	cout << "[STAT] Max erasure limit : " << MAX_ERASURE_LIMIT << endl
		<< "[STAT] Total pages : " << PAGE_COUNT << endl
		<< "[STAT] Blocks per page : " << BLOCK_COUNT << endl;

	double currentAvg = 0;
	for (int i = 0; i < PAGE_COUNT; i++) {
		currentAvg = 0;
		// Set fixed numbers
		cout.precision(4);
		
		for (int j = 0; j < BLOCK_COUNT; j++) {
			// setw(2) is same as printf("%2d");
			cout << "[BLCK] "
				// prints current page
				<< setw(to_string(PAGE_COUNT).length()) << i << "p " 
				// prints current block
				<< setw(to_string(BLOCK_COUNT).length()) << j << "b, "
				// prints current erase count
				<< "ec : " << setw(to_string(MAX_ERASURE_LIMIT).length()) << this->getPage(i)->getPageBlock()[j].getEraseCount()
				// prints current block status
				<< ", " << setw(getBlockStatusString(BlockStatus::BLOCK_INVALID).length()) << getBlockStatusString(this->getPage(i)->getPageBlock()[j].getBlockStatus())
				// prints current data
				<< ", Data : " << this->getPage(i)->getPageBlock()[j].getData() << endl;
		}
	}
}

void Storage::formatData(int start, int end) {
	if (start > PAGE_COUNT || end > PAGE_COUNT || start < 0 || end < 0) {
		cout << "Parameter error; formatData(" << start << ", " << end << ")" << endl;
		return;
	}

	// The page of start <= _RANGE_ <= end will be deleted
	// Just deletes all data, and make all cells free
	for (int i = start; i <= end; i++)
		for (int j = 0; j < BLOCK_COUNT; j++)
			this->getPage(i)->getPageBlock()[j].formatBlock();
}