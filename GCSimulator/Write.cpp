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

void writeText(Storage** s, int times, int* range, string fileName) {
	// Valid status check
	/*
	for (int i = range[0]; i <= range[1]; i++) {
		if ((*s)->getBlock(i)->hasInvalidPage()) {
			cout << "Block " << i << " has an invalid page. Do the gc first." << endl;
			return;
		}
	}
	*/

	// Read data
	string data = "", tmp;

	// Make text many times
	const string readData = readText(fileName);
	for (int i = 0; i < times; i++)
		data += readData;

	// Recalculate block counts
	int block_count = range[1] - range[0];

	// If user want to write data in a single block
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
			pertmp = (currentPos + 1.0) / (data.length() + 1.0) * 100;
			if ((int)pertmp != percent) {
				percent++;
				bar.update();
			}

			if (isDone)
				break;

			if (currentPos + MAX_LENGTH > data.length()) {
				tmp = data.substr(currentPos);
				isDone = true;
			}
			else {
				tmp = data.substr(currentPos, currentPos + MAX_LENGTH);
				currentPos += MAX_LENGTH;
			}

			(*s)->getBlock(currentBlock)->getPage()[currentPage].setData(tmp);
		}

		if (isDone)
			break;
	}

	/*
	// Write data into the cell separately
	while (currentPos + MAX_LENGTH <= data.length()) {
		string tmp = getString(data, currentPos);

		// Set a data
		int res = (*s)->getBlock(currentBlock)->getPage()[currentPage].setData(tmp);

		if (res == -1) {
			cout << "Failed to write data, canceled. " << currentBlock << "p, " << currentPage << "b." << endl;
			return;
		}
		currentPage++;
		currentPos += MAX_LENGTH;

		// It works like the circular queue
		// When page count exceeds the limits, increase the current block number
		if (currentPage == PAGE_SIZE) {
			currentPage = 0;
			currentBlock++;

			if (currentBlock > range[1])
				currentBlock = range[0];
		};
	}

	cout << "Writing done at " << currentBlock << "b, " << currentPage << "p." << endl << endl;

	// Make another page invalid
	for (int i = currentPage + 1; i < PAGE_SIZE; i++)
		(*s)->getBlock(currentBlock)->getPage()[i].setPageStatus(PageStatus::PAGE_INVALID);

	if (currentBlock + 1 <= range[1]) {
		for (int i = currentBlock + 1; i <= range[1]; i++) {
			for (int j = 0; j < PAGE_SIZE; j++) {
				(*s)->getBlock(i)->getPage()[j].setPageStatus(PageStatus::PAGE_INVALID);
			}
		}
	}
	*/
}