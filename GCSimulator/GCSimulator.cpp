/* The Simulation of Garbage Collection
 *
 * @author Lim Jung Min,
 * Department of Computer Engineering, Yeungnam University.
 */

#include <iostream>
#include <string>
#include <random>
#include "Storage.h"
#include "Random.h"
#include "Write.h"
using namespace std;

int main(void) {
	// Initalize new flash storage
	Storage* storage = new Storage();

	string input = "", p = "", b = "";
	int page = -1, block = -1;

	cout << "Operations : status, read, write, reset, exit" << endl
		<< "Algorithms : None" << endl;

	while (true) {
		cout << ">>> ";
		cin >> input;

		if (input.compare("exit") == 0) {
			return 0;
		}
		else if (input.compare("reset") == 0) {
			// Free the memory status.
			delete(storage);
			// Initalize new storage pointer.
			storage = new Storage();
			cout << "Reset complete." << endl;
		}
		else if (input.compare("status") == 0) {
			// Status command shows simple status of the flash storage.
			storage->printStat();
			cout << endl;
		}
		else if (input.compare("read") == 0) {
			// Read command reads data from a single block from the single page and shows it.
			cout << "Input (Page Block) : ";
			cin >> p >> b;

			// Parse the integer from the string
			try {
				page = stoi(p);
				block = stoi(b);
			}
			catch (exception& e) {
				cout << "Invalid values." << endl;
			}

			if (0 <= page && page <= PAGE_COUNT && 0 <= block && block <= BLOCK_COUNT) {
				cout << "Page " << page << ", Block " << block << " : "
					<< storage->getPage(page)->getPageBlock()[block].getData() << endl;
			}
			else {
				cout << "Invalid indexes." << endl;
			}

			cout << endl;
		}
		else if (input.compare("write") == 0) {
			// Write data to cell.
			int times, max = ceil(MAX_ERASURE_LIMIT / ceil((double)readText().length()
				/ (BLOCK_COUNT * PAGE_COUNT * MAX_LENGTH)));
			// Calculate max times of writing.

			cout << "How many times do you want to write? (Max : " << max << ")" << endl
				<< "Times >>> ";
			cin >> times;

			if (times > max) {
				cout << "Invalid input." << endl;
			}
			else {
				// Write times
				for (int i=0; i<times; i++)
					writeText(&storage);
			}

		}
		else {
			cout << "Invalid command." << endl;
		}
	}

	delete(storage);
	return 0;
}