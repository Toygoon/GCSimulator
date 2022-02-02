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
private :
	int pageNum;
	vector<Block*> block;

public:
	Page(int);
	int getPageNum(void);
	vector<Block*> getPage(void);
};

#endif