/* The Simulation of Page
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#include "Page.h"

Page::Page(int pageNum) {
	// Initiates new array
	this->page = new Block[BLOCK_COUNT];
	// Set a page number
	this->pageNum = pageNum;

	for (int i = 0; i < BLOCK_COUNT; i++)
		this->page[i].setBlockNum(i);
}

int Page::getPageNum(void) {
	return this->pageNum;
}

Block* Page::getPageBlock(void) {
	return this->page;
}

bool Page::hasInvalidBlock(void) {
	for (int i = 0; i < BLOCK_COUNT; i++)
		if (this->page[i].getBlockStatus() == BlockStatus::BLOCK_INVALID)
			return true;

	return false;
}