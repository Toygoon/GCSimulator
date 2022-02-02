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
	/* Block simulation class
	blockNum : current index number of block
	isDisabled : erase limit exceeded block
	eraseCount : the count of erasures
	accessTime : when data input, this value increases (1 / MAX_ERASURE_LIMIT) seconds.
	data : the data block saves
	*/

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
	double getAccessTime(void);
	bool isDisabledBlock(void);
};

#endif