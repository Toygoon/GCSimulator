#include <iostream>
#include <vector>
#include "Global.h"
#include "Block.h"
using namespace std;

int main(void) {
	vector<Block> block(BLOCKS_PER_PAGE);

	for (int i = 0; i < BLOCKS_PER_PAGE; i++) {
		cout << block.at(i).getEraseCount() << endl;
	}
	return 0;
}