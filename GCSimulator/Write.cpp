/* The File Writing Simulation for Flash Storage
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#include "Write.hpp"

inline char separator(void) {
	// Returns file separator
	
	#ifdef _WIN32
		return '\\';
	#else
		return '/';
	#endif
}

string readText(string fileName) {
	// Get current path
	char tmp[256];
	_getcwd(tmp, 256);

	string workdir(tmp), data;
	workdir += separator();
	workdir += fileName;

	// data.txt to string
	ifstream input_file(workdir);
	if (!input_file.is_open()) {
		cerr << "Could not open the file." << endl;
		exit(EXIT_FAILURE);
	}

	// Return data.txt to string
	return string(istreambuf_iterator<char>(input_file), istreambuf_iterator<char>());
}

string getString(string s, int a) {
	// Make 'a + 10' indexes of string
	char buffer[11];

	for (int i = 0; i<MAX_LENGTH; i++)
		buffer[i] = s.at(a++);
	buffer[10] = '\0';

	return buffer;
}

void writeText(Storage** s, bool fillFull, int* range, string fileName) {
	// Read data
	string data = "", tmp;

	// Make text many times
	const string readData = readText(fileName);
	
	int fillTmp = 0;
	if (fillFull)
		while (data.length() + readData.length() < (*s)->totalPageCount * PAGE_SIZE)
			data += readData;
	else
		data = readData;

	// Recalculate block counts
	int block_count = range[1] - range[0];

	// If user wanted to write data in a single block
	if (range[0] == range[1])
		block_count++;

	int totalPages = block_count * PAGE_SIZE, totalTimes = data.length() / totalPages, currentPos = 0;
	bool isDone = false;

	// For percentage
	progressbar bar(100);
	int percent = -1;
	double pertmp;

	// Write texts (with pages)
	for (int currentBlock = range[0]; currentBlock <= range[1]; currentBlock++) {
		for (int currentPage = 0; currentPage < PAGES_PER_BLOCK; currentPage++) {
			// For percentage; current position divided by total length
			pertmp = (currentPos + 1.0) / (data.length() + 1.0) * 100;
			if ((int)pertmp != percent) {
				// Update when decimal part is increased
				percent++;
				bar.update();
			}

			// Break point
			if (isDone)
				break;

			// When total length exceeded
			if (currentPos + MAX_LENGTH > data.length()) {
				tmp = data.substr(currentPos);
				isDone = true;
			}
			else {
				tmp = data.substr(currentPos, currentPos + MAX_LENGTH);
				currentPos += MAX_LENGTH;
			}

			// Check block status before final writing
			if ((*s)->getBlock(currentBlock)->getPage()[currentPage].getPageStatus() == PageStatus::PAGE_FREE)
				(*s)->getBlock(currentBlock)->getPage()[currentPage].setData(tmp);
			else {
				cout << "There's invalid pages or block, please do the gc first." << endl << endl;
				return;
			}
		}

		if (isDone)
			break;
	}
}

int* selectBlocks(Storage* s) {
	int* range = new int[2];
	range[0] = 0;
	range[1] = s->totalBlockCount;
	
	for (int i = 0; i < s->totalBlockCount; i++) {
		if (s->getBlock(i)->getPage()[0].getPageStatus() == PageStatus::PAGE_FREE) {
			range[0] = i;
			break;
		}
	}
	if (range[0] == range[1]) {
		cout << "There are no blocks to write." << endl << endl;
		return NULL;
	}

	return range;
}