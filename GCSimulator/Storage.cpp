/* The Simulation of Flash Storage
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#include "Storage.h"

Storage::Storage() {
	for (int i = 0; i < BLOCK_COUNT; i++)
		this->blocks.push_back(new Block(i));
}

Storage::Storage(const Storage& copy) : blocks(copy.blocks) {
	// Copy Constructor
}

Block* Storage::getBlock(int blockNum) {
	return blocks.at(blockNum);
}

void Storage::setBlock(int blockNum, Block* p) {
	memcpy(this->blocks[blockNum], p, sizeof(Block));
}

void Storage::printStat(void) {
	cout << "[STAT] Max erasure limit : " << MAX_ERASURE_LIMIT << endl
		<< "[STAT] Total blocks : " << BLOCK_COUNT << endl
		<< "[STAT] Pages in a block : " << PAGE_COUNT << endl;

	double currentAvg = 0;
	for (int i = 0; i < BLOCK_COUNT; i++) {
		currentAvg = 0;
		// Set fixed numbers
		cout.precision(4);
		
		for (int j = 0; j < PAGE_COUNT; j++) {
			// setw(2) is same as printf("%2d");
			cout << "[BLCK] "
				// prints current block
				<< setw(to_string(BLOCK_COUNT).length()) << i << "b " 
				// prints current page
				<< setw(to_string(PAGE_COUNT).length()) << j << "p, "
				// prints current erase count
				<< "ec : " << setw(to_string(MAX_ERASURE_LIMIT).length()) << this->getBlock(i)->getBlockPage()[j].getEraseCount()
				// prints current page status
				<< ", " << setw(getPageStatusString(PageStatus::PAGE_INVALID).length()) << getPageStatusString(this->getBlock(i)->getBlockPage()[j].getPageStatus())
				// prints current data
				<< ", Data : " << this->getBlock(i)->getBlockPage()[j].getData() << endl;
		}
	}
}

void Storage::formatData(int start, int end) {
	if (start > BLOCK_COUNT || end > BLOCK_COUNT || start < 0 || end < 0) {
		cout << "Parameter error; formatData(" << start << ", " << end << ")" << endl;
		return;
	}

	// The block of start <= _RANGE_ <= end will be deleted
	// Just deletes all data, and make all cells free
	for (int i = start; i <= end; i++)
		for (int j = 0; j < PAGE_COUNT; j++)
			this->getBlock(i)->getBlockPage()[j].formatPage();
}
