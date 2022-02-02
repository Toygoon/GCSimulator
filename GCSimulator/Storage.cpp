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