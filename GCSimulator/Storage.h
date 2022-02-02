/* The Header for Simulation of Storage
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#ifndef STORAGE
#define STORAGE

#include <iostream>
#include <vector>
#include "Block.h"
using namespace std;

class Storage {
private:

public:
	vector<vector<Block>> table;
	Storage();
};

#endif