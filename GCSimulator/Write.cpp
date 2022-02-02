#include "Write.h"

inline char separator() {
	// Returns file separator.
	
	#ifdef _WIN32
		return '\\';
	#else
		return '/';
	#endif
}

string readText() {
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

void writeText(Storage** s) {
	// Read data.
	string data = readText();
	int total_blocks = BLOCK_COUNT * PAGE_COUNT, total_times = data.length() / total_blocks, current = 0;

	// Write data into the cell separately.
	for (int i = 0; i < total_times; i++) {
		for (int j = current; j < current + MAX_LENGTH; j++) {
			// TODO : HERE, solve
			current++;
		}
	}

	cout << current << endl;
}