#include <iostream>
#include "Page.h"
using namespace std;

int main(void) {
	Page* p = new Page(0);
	vector<Block*> one = p->getPage();

	for (int i = 0; i < BLOCKS_PER_PAGE; i++) {
		cout << one.at(i)->getData() << endl;
	}


	return 0;
}