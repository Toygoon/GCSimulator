/* The Header for Simulation of Page
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#ifndef PAGE
#define PAGE

#include <iostream>
#include <vector>
#include <string>
#include "Block.h"
#include "Global.h"
using namespace std;

class Page {
private:
	/* Page simulation class
	pageNum : indicates the current page number (it's just an id)
	page : the array of blocks
	*/

	int pageNum;
	Block* page;

public:
	Page(int);
	int getPageNum(void);
	Block getBlock(int);
};

#endif