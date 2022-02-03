/* The Simulation of Block Status
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#include "BlockStatus.h"

string getBlockStatusString(BlockStatus bs) {
	if (bs == BlockStatus::BLOCK_FREE)
		return "free";
	else if (bs == BlockStatus::BLOCK_INVALID)
		return "invalid";
	
	return "valid";
}