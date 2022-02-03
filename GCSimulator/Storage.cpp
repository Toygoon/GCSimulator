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

double* Storage::calcTimes(void) {
	// Create average tables.
	double* times= new double[PAGE_COUNT];

	for (int i = 0; i < PAGE_COUNT; i++) {
		cout << times[i] << endl;
	}

	return 0;
}

void Storage::printStat(void) {
	cout << "[STAT] Max erasure limit : " << MAX_ERASURE_LIMIT << endl
		<< "[STAT] Total pages : " << PAGE_COUNT << endl
		<< "[STAT] Blocks per page : " << BLOCK_COUNT << endl;

	double currentAvg = 0;
	for (int i = 0; i < PAGE_COUNT; i++) {
		currentAvg = 0;
		// Set fixed numbers.
		cout.precision(4);
		
		for (int j = 0; j < BLOCK_COUNT; j++) {
			// setw(2) is same as printf("%2d");
			cout << "[BLCK] " << setw(to_string(PAGE_COUNT).length()) << i << "p " << setw(to_string(BLOCK_COUNT).length()) << j << "b, "
				<< "ec : " << setw(to_string(MAX_ERASURE_LIMIT).length()) << this->getPage(i)->getPageBlock()[j].getEraseCount()
				<< ", " << setw(getBlockStatusString(BlockStatus::BLOCK_INVALID).length()) << getBlockStatusString(this->getPage(i)->getPageBlock()[j].getBlockStatus())
				<< ", Data : " << this->getPage(i)->getPageBlock()[j].getData() << endl;
		}
	}
}

void Storage::formatData(void) {
	// Just deletes all data, and make all cells free.
	for (int i = 0; i < PAGE_COUNT; i++) {
		for (int j = 0; j < BLOCK_COUNT; j++) {
			this->getPage(i)->getPageBlock()[j].setData("");
		}
	}
}