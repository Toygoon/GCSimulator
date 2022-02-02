/* The Simulation of Block
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#include "Block.h"

// Constructor to reset all values.
Block::Block(void) {
	this->blockNum = -1;
	this->eraseCount = 0;
	this->isDisabled = false;
	this->accessTime = 0.0;
	this->data = "";
}

void Block::setBlockNum(int blockNum) {
	this->blockNum = blockNum;
}

int Block::setData(string data) {
	// Return -1 if attempt to write into the disabled block.
	if (this->isDisabledBlock())
		return -1;

	this->data = data;
	eraseCount++;

	// If the block is going to be disabled next time, make it disabled writing.
	if (this->eraseCount >= MAX_ERASURE_LIMIT)
		this->isDisabled = true;

	// Increase the access time, the max of time is 1 sec.
	accessTime += (1 / MAX_ERASURE_LIMIT) * 100;

	// Return 0 if succeed with writing.
	return 0;
}

int Block::getBlockNum(void) {
	return this->blockNum;
}

int Block::getEraseCount(void) {
	return this->eraseCount;
}

string Block::getData(void) {
	return this->data;
}

double Block::getAccessTime(void) {
	return this->accessTime;
}

bool Block::isDisabledBlock(void) {
	return this->isDisabled;
}