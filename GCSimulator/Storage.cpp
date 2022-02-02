/* The Simulation of Flash Storage
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#include "Storage.h"

Storage::Storage() {
	for (int i = 0; i < BLOCK_COUNT; i++)
		pages.push_back(new Page(i));
}

Page* Storage::getPage(int pageNum) {
	return pages.at(pageNum);
}

void Storage::printStat(void) {
	cout << "[STAT] Max erasure limit : " << MAX_ERASURE_LIMIT << endl
		<< "[STAT] Total pages : " << PAGE_COUNT << endl
		<< "[STAT] Blocks per page : " << BLOCK_COUNT << endl;

	double currentAvg = 0;
	for (int i = 0; i < PAGE_COUNT; i++) {
		currentAvg = 0;
		// Set fixed numbers.
		cout.precision(4);

		for (int j = 0; j < BLOCK_COUNT; j++) {
			cout << "Access time : " << fixed << this->getPage(i)->getPageBlock()[j].getAccessTime()
				<< "Erasure count : " << this->getPage(i)->getPageBlock()[j].getEraseCount() << endl;
		}
		/*
		for (int j = 0; j < BLOCK_COUNT; j++)
			currentAvg += this->getPage(i)->getPageBlock()[j].getAccessTime();

		currentAvg /= BLOCK_COUNT;
		cout << "[PAGE] Page " << i << ", Average access time : " << fixed << currentAvg << endl;
		*/
	}
}