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
#include "Storage.h"
using namespace std;

inline char separator(void);
string readText(void);
string getString(string, int);
void writeText(Storage**, int, int*);

#endif