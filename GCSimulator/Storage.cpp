/* The Simulation of Flash Storage
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#include "Storage.hpp"

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
	cout << "* Storage size : " << this->flashSizeBytes << " Bytes" << endl
		<< "* Single page size : " << PAGE_SIZE << " Bytes" << endl
		<< "* Pages per block : " << PAGES_PER_BLOCK << " Pages" << endl
		<< "* Total blocks : " << this->totalBlockCount << " Blocks" << endl
		<< "* Total pages : " << this->totalPageCount << " Pages" << endl
		<< "* Max erasure limit : " << MAX_ERASURE_LIMIT << " times" << endl;


	int pageCurrentStatus[3] = { 0, 0, 0 };

	for (int i = 0; i < this->totalBlockCount; i++) {
		for (int j = 0; j < PAGES_PER_BLOCK; j++) {
			switch (this->getBlock(i)->getPage()[j].getPageStatus()) {
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
	}

	cout << endl
		<< "* Valid blocks : " << ceil((double)pageCurrentStatus[0] / (double)PAGES_PER_BLOCK) << endl
		<< "* Invalid blocks : " << ceil((double)pageCurrentStatus[1] / (double)PAGES_PER_BLOCK) << endl
		<< "* Free blocks : " << ceil((double)pageCurrentStatus[2] / (double)PAGES_PER_BLOCK) << endl;
}

void Storage::formatData(int start, int end) {
	// The block of start <= _RANGE_ <= end will be deleted
	// Just deletes all data, and make all cells free
	for (int i = start; i <= end; i++)
		for (int j = 0; j < PAGES_PER_BLOCK; j++)
			this->getBlock(i)->getPage()[j].formatPage(false);
}
