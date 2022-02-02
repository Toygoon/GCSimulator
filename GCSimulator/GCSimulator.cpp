#include <iostream>
#include "Storage.h"
using namespace std;

int main(void) {
	Page* page = new Page(0);
	for (int i = 0; i < PAGE_COUNT; i++) {
		cout << page->getBlock(i).getData() << endl;
	}

	Storage* storage = new Storage();
	for (int i = 0; i < PAGE_COUNT; i++) {
		for (int j = 0; j < BLOCK_COUNT; j++)
			cout << storage->getPage(i)->getBlock(j).getData() << endl;
	}
	return 0;
}