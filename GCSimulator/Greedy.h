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
#include "Storage.h"
using namespace std;

class Greedy {
private:
	// The page number that all blocks are free status
	// vector's tuple structure : <pageNum, total eraseCount>
	// To sort the eraseCount, the data will be saved into tuple structure
	vector<pair<int, int>> freePages;

	// Percentage of invalid blocks per each page
	// vector's tuple structure : <pageNum, invalid percentage>
	// To sort the percentage, the data will be saved into tuple structure
	vector<pair<int, double>> invalids;

	// victims to be "Garbage Collection"
	vector<int> victims;

	// valid blocks will be appended into the "validInVictims[pageNum]"
	// Because valid blocks should be copied to another free blocks
	vector<int> validInVictims[PAGE_COUNT];

public:
	Greedy();
	void calcVictims(Storage*);
	void calcFreeSpace(Storage*);
	void cleanAllInvalids(Storage**);
	void greedyMain(Storage**);
};

static bool cmpInvalid(pair<int, double>&, pair<int, double>&);
static bool cmpEraseCount(pair<int, int>&, pair<int, int>&);

#endif