/* The File Writing Header of Simulation for Flash Storage
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#ifndef WRITE
#define WRITE

#include <iostream>
#include <string>
#include <filesystem>
#include <direct.h>
#include <fstream>
#include <sstream>
#include "Storage.hpp"
#include "ProgressBar.hpp"
using namespace std;

inline char separator(void);
string readText(string);
string getString(string, int);
void writeText(Storage**, bool, int*, string);
int* selectBlocks(Storage*);

#endif