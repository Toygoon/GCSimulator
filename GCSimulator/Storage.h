/* The Header for Simulation of Storage
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#ifndef STORAGE
#define STORAGE

#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Block.h"
#include "PageStatus.h"
using namespace std;

class Storage {
private:
	size_l flashSizeBytes;
	size_l totalBlockCount;
	size_l totalPageCount;
	vector<Block*> blocks;
public:
	Storage(void);
	Storage(const Storage&);
	Block* getBlock(int);
	void setBlock(int, Block*);
	void printStat(void);
	void formatData(int, int);
};

#endif