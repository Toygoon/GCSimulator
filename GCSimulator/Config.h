/* The configuration class for GCSimulator
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#ifndef CONFIG
#define CONFIG

#include "Global.h"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <map>
using namespace std;

class Config {
private:
	// Configuration tables
	map<string, string> table;
public:
	Config(const string&);
	int createDefaultConfigs(void);
	bool isConfigExists(void);
	bool containsConfig(const string&);
	size_l getSizeL(const string&);
	int getInt(const string&);
	string getString(const string&);
};
#endif