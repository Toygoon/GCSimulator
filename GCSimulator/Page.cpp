/* The Simulation of Page
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#include "Page.hpp"

// Constructor to reset all values
Page::Page(void) {
	this->pageNum = -1;
	this->eraseCount = 0;
	this->isDisabled = false;
	this->accessTime = 0.0;
	this->data = "";
	this->pageStatus = PageStatus::PAGE_FREE;
}

void Page::setPageNum(int pageNum) {
	this->pageNum = pageNum;
}

int Page::setData(string data) {
	// Return -1 if attempt to write into the disabled page
	if (this->isDisabledPage())
		return -1;

	this->data = data;
	eraseCount++;

	// If the page is going to be disabled next time, make it disabled writing
	if (this->eraseCount >= MAX_ERASURE_LIMIT)
		this->isDisabled = true;

	// Increase the access time, the max of time is 1 sec
	double tmp = 1.0 / (double)MAX_ERASURE_LIMIT;
	this->accessTime += tmp;

	// Set page as valid
	this->pageStatus = PageStatus::PAGE_VALID;

	// Return 0 if succeed with writing
	return 0;
}

void Page::setPageStatus(PageStatus pageStatus) {
	this->pageStatus = pageStatus;
}

int Page::getPageNum(void) {
	return this->pageNum;
}

int Page::getEraseCount(void) {
	return this->eraseCount;
}

string Page::getData(void) {
	return this->data;
}

double Page::getAccessTime(void) {
	return this->accessTime;
}

PageStatus Page::getPageStatus(void) {
	return this->pageStatus;
}

bool Page::isDisabledPage(void) {
	return this->isDisabled;
}

void Page::formatPage(void) {
	this->setData("");
	this->pageStatus = PageStatus::PAGE_FREE;
}