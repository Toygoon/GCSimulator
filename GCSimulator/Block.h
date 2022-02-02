/* The Header for Simulation of Block
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#ifndef BLOCK
#define BLOCK

#include <iostream>
#include "Global.h"
using namespace std;

class Block {
private:
	int blockNum;
	int eraseCount;
	bool isDisabled;
	double accessTime;
	string data;

public:
	Block();
	void setBlockNum(int);
	int setData(string);
	int getBlockNum(void);
	int getEraseCount(void);
	string getData(void);
	bool isDisabledBlock(void);
};

#endif