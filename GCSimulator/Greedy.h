/* Greedy Algorithm Header for Flash Storage
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#ifndef GREEDY
#define GREEDY

#include <iostream>
#include <vector>
#include <tuple>
#include "Write.h"
#include "Storage.h"
using namespace std;

class Greedy {
private:
	// The block number that all pages are free status
	// vector's tuple structure : <blockNum, total eraseCount>
	// To sort the eraseCount, the data will be saved into tuple structure
	vector<pair<int, int>> freeBlocks;

	// Percentage of invalid pages per each block
	// vector's tuple structure : <blockNum, invalid percentage>
	// To sort the percentage, the data will be saved into tuple structure
	vector<pair<int, double>> invalids;

	// victims to be "Garbage Collection"
	vector<int> victims;

	// valid pages will be appended into the "validInVictims[blockNum]"
	// Because valid pages should be copied to another free pages
	vector<int> validInVictims[BLOCK_COUNT];

	// Functions
	void calcVictims(Storage*);
	void calcFreeSpace(Storage*);
	void cleanAllInvalids(Storage**);
public:
	Greedy();
	void greedyMain(Storage**);
};

static bool cmpInvalid(pair<int, double>&, pair<int, double>&);
static bool cmpEraseCount(pair<int, int>&, pair<int, int>&);

#endif