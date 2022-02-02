/* The Simulation of Page
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#include "Page.h"

Page::Page(int pageNum) {
	// Initiates new array.
	this->page = new Block[BLOCK_COUNT];
	// Set a page number.
	this->pageNum = pageNum;

	for (int i = 0; i < BLOCK_COUNT; i++) {
		page[i].setBlockNum(i);
		// It's just an initial data.
		page[i].setData(to_string(pageNum) + " Page, " + to_string(i) + " Block Data.");
	}
}

int Page::getPageNum(void) {
	return this->pageNum;
}

Block Page::getBlock(int blockNum) {
	if (blockNum >= BLOCK_COUNT)
		throw out_of_range("Out of range.");
	return this->page[blockNum];
}