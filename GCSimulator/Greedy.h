/* Greedy Algorithm Header for Flash Storage
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#ifndef GREEDY
#define GREEDY

#include <iostream>
#include <vector>
#include <unordered_map>
#include "Storage.h"
using namespace std;

class Greedy {
private:
	// How many victims in this section
	int victimCounts;
	// The page number that all blocks are free status
	vector<int> freeSpace;
	// Percentage of invalid blocks per each page
	// index : page number
	double* invalids;
public:
	Greedy();
	void calcVictim(Storage*);
	void calcFreeSpace(Storage*);
	void greedyMain(Storage**);
};

#endif