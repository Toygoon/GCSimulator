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
		
		for (int j = 0; j < BLOCK_COUNT; j++)
			currentAvg += this->pages.at(i)->getBlock(j).getAccessTime();

		currentAvg /= BLOCK_COUNT;
		cout << "[PAGE] Page " << i << ", Average access time : " << currentAvg << endl;
	}
}