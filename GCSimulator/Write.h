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

inline char separator();
string readText();
void writeText(Storage**);

#endif