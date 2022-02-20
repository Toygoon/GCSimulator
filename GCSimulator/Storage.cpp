/* The Simulation of Flash Storage
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#include "Storage.hpp"
#include "ProgressBar.hpp"
#include <climits>

Storage::Storage(Config* config) {
	// Set flashSizes
	this->flashSizeBytes = config->getSizeL("FLASH_STORAGE_SIZE") * 1024 * 1024 * 1024;
	this->totalPageCount = this->flashSizeBytes / PAGE_SIZE;
	this->totalBlockCount = this->totalPageCount / PAGES_PER_BLOCK;

	progressbar bar(100);
	blocks = vector<Block*>(this->totalBlockCount);
	int percent = -1;
	double tmp;
	//cout << "* Initiating Flash Storage" << endl;
	for (int i = 0; i < this->totalBlockCount; i++) {
		tmp = (i / (double) this->totalBlockCount) * 100;
		if ((int)tmp != percent) {
			bar.update();
			percent++;
		}
		blocks.at(i) = new Block(i);
	}
	cout << endl;
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
	cout << "[STAT] Page size : " << PAGE_SIZE << " Bytes" << endl
		<< "[STAT] Pages per block : " << PAGES_PER_BLOCK << endl
		<< "[STAT] Max erasure limit : " << MAX_ERASURE_LIMIT << endl
		<< "[STAT] Total blocks : " << this->totalBlockCount << endl
		<< "[STAT] Total pages : " << this->totalPageCount << endl;


	// Disabled for now
	for (int i = 0; i < this->totalBlockCount; i++) {
		int pageCurrentStatus[3] = { 0, 0, 0 };
		// Set fixed numbers
		cout.precision(4);

		for (int j = 0; j < PAGES_PER_BLOCK; j++) {
			if (this->getBlock(i)->getPage()[j].getPageStatus() == PageStatus::PAGE_VALID)
				pageCurrentStatus[0]++;
			if (this->getBlock(i)->getPage()[j].getPageStatus() == PageStatus::PAGE_INVALID)
				pageCurrentStatus[1]++;
			if (this->getBlock(i)->getPage()[j].getPageStatus() == PageStatus::PAGE_FREE)
				pageCurrentStatus[2]++;
			//cout << ", Data : " << this->getBlock(i)->getPage()[j].getData() << endl;
		}

	}
}

void Storage::formatData(int start, int end) {
	if (start > PAGES_PER_BLOCK || end > PAGES_PER_BLOCK || start < 0 || end < 0) {
		cout << "Parameter error; formatData(" << start << ", " << end << ")" << endl;
		return;
	}

	// The block of start <= _RANGE_ <= end will be deleted
	// Just deletes all data, and make all cells free
	for (int i = start; i <= end; i++)
		for (int j = 0; j < PAGE_SIZE; j++)
			this->getBlock(i)->getPage()[j].formatPage();
}
