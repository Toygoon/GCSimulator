/* The Simulation of Page
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#include "Page.h"

Page::Page(void) {
	for (int i = 0; i < BLOCKS_PER_PAGE; i++) {
		block.push_back(new Block());
		block.at(i)->setBlockNum(i);
		block.at(i)->setData("Initial " + to_string(i) + " block data.");
	}
}

void Page::setCurrentPage(int currentPage) {
	this->currentPage = currentPage;
}

int Page::getCurrentPage(void) {
	return this->currentPage;
}
vector<Block*> Page::getPage(void) {
	return this->block;
}