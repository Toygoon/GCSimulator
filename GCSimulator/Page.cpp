/* The Simulation of Page
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#include "Page.h"

Page::Page(int pageNum) {
	this->pageNum = pageNum;
	for (int i = 0; i < BLOCKS_PER_PAGE; i++) {
		block.push_back(new Block());
		block.at(i)->setBlockNum(i);
		block.at(i)->setData(to_string(pageNum) + " Page, " + to_string(i) + " Block Data.");
	}
}

int Page::getPageNum(void) {
	return this->pageNum;
}
vector<Block*> Page::getPage(void) {
	return this->block;
}