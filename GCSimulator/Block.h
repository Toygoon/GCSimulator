/* The Header for Simulation of Block
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#ifndef BLOCK
#define BLOCK

#include <iostream>
#include "Global.h"
#include "BlockStatus.h"
using namespace std;

class Block {
private:
	/* Block simulation class
	blockNum : current index number of block
	isDisabled : erase limit exceeded block
	eraseCount : the count of erasures
	accessTime : when data input, this value increases (1 / MAX_ERASURE_LIMIT) seconds.
	data : the data block saves
	blockStatus : block valid, invalid, free status
	*/
	int blockNum;
	int eraseCount;
	bool isDisabled;
	double accessTime;
	string data;
	BlockStatus blockStatus;

public:
	Block();
	void setBlockNum(int);
	int setData(string);
	void setBlockStatus(BlockStatus);
	int getBlockNum(void);
	int getEraseCount(void);
	string getData(void);
	double getAccessTime(void);
	BlockStatus getBlockStatus(void);
	bool isDisabledBlock(void);
};

#endif