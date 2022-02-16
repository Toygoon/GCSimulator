/* The Header for Simulation of Page Status
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#ifndef PAGESTATUS
#define PAGESTATUS

#include <iostream>
using namespace std;

enum class PageStatus {
	PAGE_VALID,
	PAGE_INVALID,
	PAGE_FREE
};

string getPageStatusString(PageStatus);

#endif