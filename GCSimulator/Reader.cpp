#include "Reader.h"

int readData(Storage* s, bool isPage) {
	int index;
	string input;

	// Read command reads data from a single block from the single page and shows it.
	string info = "What ";
	if (isPage) {
		info += "page do you want to read ? (Total ";
		info += to_string(PAGE_COUNT);
		info += " pages)\n";
	}
	else {
		info += "block do you want to read ? (Total ";
		info += to_string(BLOCK_COUNT);
		info += " blocks)\n";
	}
	info += "Type \"abort\" to abort.\n";

	cout << info;

	while (true) {
		// index : temp value for reading page, and block values
		index = -1;
		// input : user input from stdin
		input = "";

		cout << "Page >>> ";
		cin >> input;

		if (input.compare("abort") == 0) {
			cout << "Aborted." << endl;
			break;
		}
		else {
			// Parse the integer from the string
			try {
				index = stoi(input);
			}
			catch (exception& e) {
			}
		}

		if (0 <= index && index <= PAGE_COUNT) {
			return index;
		}
		else {
			cout << endl << "Invalid input." << endl;
		}
	}

	return index;
}