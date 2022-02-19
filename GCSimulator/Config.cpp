/* The configuration methods for GCSimulator
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#include "Config.h"
#include "Write.h"

Config::Config(const string& fileName) {
	// Read file
	ifstream file(fileName);

	if (file.is_open()) {
		string line;
		// Read each line
		while (getline(file, line)) {
			// Find text with delim equal
			string delim = " = ";

			// The case that there's not any space existing
			if (string::npos == line.find(delim))
				delim = "=";

			// token1 : configuration's name
			string token1 = line.substr(0, line.find(delim));
			// token2 : configuration set value
			string token2 = line.substr(line.find(delim) + delim.length(), line.length());

			// Add a config with current line (index)
			this->table[token1] = token2;
		}
		file.close();
	}
}

bool Config::isConfigExists(void) {
	return this->table.size() != 0;
}

bool Config::containsConfig(const string& name) {
	// If there's no such config
	if (this->table.find(name) == this->table.end())
		return false;

	return true;
}

/* Grab a configuration value and return a value with size_l */
size_l Config::getSizeL(const string& name) {
	if (this->containsConfig(name))
		return stol(this->table[name]);
	else
		throw invalid_argument("The config not exists.");
}

/* Grab a configuration value and return a value with int */
int Config::getInt(const string& name) {
	if (this->containsConfig(name))
		return stoi(this->table[name]);
	else
		throw invalid_argument("The config not exists.");
}


int Config::createDefaultConfigs(void) {
	ofstream file("config.txt");
	vector<string> config;

	config.push_back("FLASH_STORAGE_SIZE=128\n");
	config.push_back("DATA_FILE=data.txt\n");

	// Config contents
	/*
	config.push_back("# The count of each page size in Bytes\n");
	config.push_back("PAGE_SIZE=4096\n\n");
	config.push_back("# How many pages in a block\n");
	config.push_back("PAGES_PER_BLOCK=64\n\n");
	config.push_back("# The limit of erasure per cell\n");
	config.push_back("MAX_ERASURE_LIMIT=1000\n\n");
	*/

	if (file.is_open()) {
		// Write default configs
		for (const auto& e : config)
			file << e;
		file.close();

		return 0;
	}

	return -1;
}

string Config::getString(const string& name)
{
	if (this->containsConfig(name)) {
		if (this->table[name].find("\"") == std::string::npos)
			return this->table[name];
		else
			return this->table[name].substr(1, this->table[name].length() - 2);
	}
	else
		throw invalid_argument("The config not exists.");
}
