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

	return string(istreambuf_iterator<char>(input_file), istreambuf_iterator<char>());
}

string getString(string s, int a) {
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
		if (currentPage == PAGE_COUNT)
			currentPage = 0;
		if (currentBlock == BLOCK_COUNT)
			currentBlock = 0;

		//cout << currentPage << "p, " << currentBlock << "b, " << tmp << endl;
		cout << tmp  << endl;
		(*s)->getPage(currentPage)->getPageBlock()[currentBlock].setData(tmp);
		currentPage++;
		currentBlock++;
		currentPos += MAX_LENGTH;
	}
}