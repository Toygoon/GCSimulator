#ifndef BLOCKSTATUS
#define BLOCKSTATUS

#include <iostream>
using namespace std;

enum class BlockStatus {
	BLOCK_VALID,
	BLOCK_INVALID,
	BLOCK_FREE
};

string getBlockStatusString(BlockStatus);

#endif