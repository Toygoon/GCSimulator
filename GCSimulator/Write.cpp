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

void writeText(Storage** s) {
	// Read data.
	string data = readText();
	int totalBlocks = BLOCK_COUNT * PAGE_COUNT, totalTimes = data.length() / totalBlocks, currentPos = 0, currentPage = 0, currentBlock = 0;

	// Write data into the cell separately.
	while (currentPos + MAX_LENGTH <= data.length()) {
		string tmp = getString(data, currentPos);

		// It works like the circular queue.
		if (currentPage == PAGE_COUNT) {
			currentPage = 0;
			currentBlock = 0;
		}
		// When block count exceeds the limits, increase the current page number.
		if (currentBlock == BLOCK_COUNT) {
			currentBlock = 0;
			currentPage++;
		};

		// Set a data.
		(*s)->getPage(currentPage)->getPageBlock()[currentBlock].setData(tmp);
		currentBlock++;
		currentPos += MAX_LENGTH;
	}

	// Make another block invalid
	for (int i = currentBlock + 1; i < BLOCK_COUNT; i++)
		(*s)->getPage(currentPage)->getPageBlock()[i].setBlockStatus(BlockStatus::BLOCK_INVALID);

	if (currentPage + 1 < PAGE_COUNT) {
		for (int i = currentPage + 1; i < PAGE_COUNT; i++) {
			for (int j = 0; j < BLOCK_COUNT; j++) {
				(*s)->getPage(i)->getPageBlock()[j].setBlockStatus(BlockStatus::BLOCK_INVALID);
			}
		}
	}

	//cout << "Writing ended with " << currentPage << "p, " << currentBlock << "b." << endl;
	
}