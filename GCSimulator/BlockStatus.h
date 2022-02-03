/* The Header for Simulation of Block Status
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#ifndef BLOCKSTATUS
#define BLOCKSTATUS

#include <iostream>
using namespace std;

enum class BlockStatus {
	BLOCK_VALID,
	BLOCK_INVALID,
	BLOCK_FREE
};

string getBlockStatusString(BlockStatus);

#endif