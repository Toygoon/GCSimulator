/* The Header for Simulation of Page
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#ifndef PAGE
#define PAGE

#include <iostream>
#include "Global.hpp"
#include "PageStatus.hpp"
using namespace std;

class Page {
private:
	/* Page simulation class
	pageNum : current index number of page
	isDisabled : erase limit exceeded page
	eraseCount : the count of erasures
	accessTime : when data input, this value increases (1 / MAX_ERASURE_LIMIT) seconds.
	data : the data page saves
	pageStatus : page valid, invalid, free status
	*/
	int pageNum;
	int eraseCount;
	bool isDisabled;
	double accessTime;
	string data;
	PageStatus pageStatus;

public:
	Page(void);
	void setPageNum(int);
	int setData(string);
	void setPageStatus(PageStatus);
	int getPageNum(void);
	int getEraseCount(void);
	string getData(void);
	double getAccessTime(void);
	PageStatus getPageStatus(void);
	bool isDisabledPage(void);
	void formatPage(void);
};

#endif