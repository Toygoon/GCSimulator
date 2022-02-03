/* The Header for Simulation of Storage
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#ifndef STORAGE
#define STORAGE

#include <iostream>
#include <iomanip>
#include "Page.h"
#include "BlockStatus.h"
using namespace std;

class Storage {
private:
	vector<Page*> pages;
public:
	Storage(void);
	Page* getPage(int);
	double* calcTimes(void);
	void printStat(void);
	void formatData(void);
};

#endif