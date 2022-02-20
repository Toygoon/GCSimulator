/* The Header for Simulation of Block
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#ifndef BLOCK
#define BLOCK

#include <iostream>
#include <vector>
#include <string>
#include "Page.hpp"
#include "Global.hpp"
using namespace std;

class Block {
private:
	/* Block simulation class
	blockNum : indicates the current block number (it's just an id)
	block : the array of pages
	*/
	int blockNum;
	Page* block;

public:
	Block(int);
	int getBlockNum(void);
	Page* getBlockPage(void);
	bool hasInvalidPage(void);
};

#endif