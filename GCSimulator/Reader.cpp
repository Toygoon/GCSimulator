#include "Reader.h"

int readData(Storage* s, bool isBlock) {
	int index;
	string input;

	// Read command reads data from a single page from the single block and shows it
	string info = "What ";
	if (isBlock) {
		info += "block do you want to read ? (Total ";
		info += to_string(BLOCK_COUNT);
		info += " blocks)\n";
	}
	else {
		info += "page do you want to read ? (Total ";
		info += to_string(PAGE_SIZE);
		info += " pages)\n";
	}
	info += "Type \"abort\" to abort.\n";

	cout << info;

	while (true) {
		// index : temp value for reading block, and page values
		index = -1;
		// input : user input from stdin
		input = "";

		cout << "Block >>> ";
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

		if (0 <= index && index <= BLOCK_COUNT) {
			return index;
		}
		else {
			cout << endl << "Invalid input." << endl;
		}
	}

	return index;
}