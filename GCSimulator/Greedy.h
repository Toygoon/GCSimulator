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
	unordered_map<int, int> victimMap;
	vector<Page*> victimPages;
	double* invalids;
public:
	Greedy();
	void calcVictim(Storage*);
};


#endif