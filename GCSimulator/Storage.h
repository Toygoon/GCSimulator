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
#include "Page.h"
#include "BlockStatus.h"
using namespace std;

class Storage {
private:
	vector<Page*> pages;
public:
	Storage(void);
	Storage(const Storage&);
	Page* getPage(int);
	void setPage(int, Page*);
	void printStat(void);
	void formatData(int, int);
};

#endif