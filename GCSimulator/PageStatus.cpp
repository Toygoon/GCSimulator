/* The Simulation of Page Status
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#include "PageStatus.h"

string getPageStatusString(PageStatus bs) {
	if (bs == PageStatus::PAGE_FREE)
		return "free";
	else if (bs == PageStatus::PAGE_INVALID)
		return "invalid";
	
	return "valid";
}