/* The Header for Simulation of Storage
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#ifndef STORAGE
#define STORAGE

#include <iostream>
#include "Page.h"
using namespace std;

class Storage {
private:
	vector<Page*> pages;
public:
	Storage(void);
	Page* getPage(int);
	void printStat(void);
};

#endif