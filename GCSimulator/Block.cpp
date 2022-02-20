/* The Simulation of Block
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#include "Block.hpp"

Block::Block(int blockNum) {
	// Initiates new array
	this->block = new Page[PAGES_PER_BLOCK];
	// Set a block number
	this->blockNum = blockNum;

	for (int i = 0; i < PAGES_PER_BLOCK; i++)
		this->block[i].setPageNum(i);
}

Block::~Block(void) {
	delete block;
}

int Block::getBlockNum(void) {
	return this->blockNum;
}

Page* Block::getPage(void) {
	return this->block;
}

bool Block::hasInvalidPage(void) {
	for (int i = 0; i < PAGES_PER_BLOCK; i++)
		if (this->block[i].getPageStatus() == PageStatus::PAGE_INVALID)
			return true;

	return false;
}