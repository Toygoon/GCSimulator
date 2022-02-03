#include "Write.h"

inline char separator(void) {
	// Returns file separator.
	
	#ifdef _WIN32
		return '\\';
	#else
		return '/';
	#endif
}

string readText(void) {
	// Get current path.
	char tmp[256];
	_getcwd(tmp, 256);

	string workdir(tmp), data;
	workdir += separator();
	workdir += "data.txt";

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
	// Make 'a + 10' indexes of string.
	char buffer[11];

	for (int i = 0; i<MAX_LENGTH; i++)
		buffer[i] = s.at(a++);
	buffer[10] = '\0';

	return buffer;
}

void writeText(Storage** s, int times, int* range) {
	// Valid status check
	for (int i = range[0]; i <= range[1]; i++) {
		if ((*s)->getPage(i)->hasInvalidBlock()) {
			cout << "Page " << i << " has an invalid block. Do the gc first." << endl;
			return;
		}
	}

	// Read data.
	string data = "";

	// Make text many times.
	const string readData = readText();
	for (int i = 0; i < times; i++)
		data += readData;

	// Recalculate page counts.
	const int page_count = range[1] - range[0];

	int totalBlocks = page_count * BLOCK_COUNT, totalTimes = data.length() / totalBlocks, currentPos = 0, currentPage = range[0], currentBlock = 0;

	// Write data into the cell separately.
	while (currentPos + MAX_LENGTH <= data.length()) {
		string tmp = getString(data, currentPos);

		// Set a data.
		int res = (*s)->getPage(currentPage)->getPageBlock()[currentBlock].setData(tmp);

		if (res == -1) {
			cout << "Failed to write data, canceled. " << currentPage << "p, " << currentBlock << "b." << endl;
			return;
		}
		currentBlock++;
		currentPos += MAX_LENGTH;

		// It works like the circular queue.
		// When block count exceeds the limits, increase the current page number.
		if (currentBlock == BLOCK_COUNT) {
			currentBlock = 0;
			currentPage++;

			if (currentPage > range[1])
				currentPage = range[0];
		};
	}

	cout << "Writing done at " << currentPage << "p, " << currentBlock << "b." << endl << endl;

	// Make another block invalid
	for (int i = currentBlock + 1; i < BLOCK_COUNT; i++)
		(*s)->getPage(currentPage)->getPageBlock()[i].setBlockStatus(BlockStatus::BLOCK_INVALID);

	if (currentPage + 1 <= range[1]) {
		for (int i = currentPage + 1; i <= range[1]; i++) {
			for (int j = 0; j < BLOCK_COUNT; j++) {
				(*s)->getPage(i)->getPageBlock()[j].setBlockStatus(BlockStatus::BLOCK_INVALID);
			}
		}
	}
}