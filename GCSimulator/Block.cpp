/* The Simulation of Block
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#include "Block.hpp"

Block::Block(int blockNum) {
	// Initiates new array
	this->block = new Page[PAGE_SIZE];
	// Set a block number
	this->blockNum = blockNum;

	for (int i = 0; i < PAGE_SIZE; i++)
		this->block[i].setPageNum(i);
}

int Block::getBlockNum(void) {
	return this->blockNum;
}

Page* Block::getBlockPage(void) {
	return this->block;
}

bool Block::hasInvalidPage(void) {
	for (int i = 0; i < PAGE_SIZE; i++)
		if (this->block[i].getPageStatus() == PageStatus::PAGE_INVALID)
			return true;

	return false;
}