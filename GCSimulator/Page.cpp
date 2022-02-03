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
		//page[i].setData(to_string(pageNum) + "p " + to_string(i) + "b");
	}
}

int Page::getPageNum(void) {
	return this->pageNum;
}

Block* Page::getPageBlock() {
	return this->page;
}