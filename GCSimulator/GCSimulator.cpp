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
using namespace std;

int main(void) {
	// Initalize new flash storage
	Storage* storage = new Storage();

	string input = "", p = "", b = "";
	int page = -1, block = -1;

	cout << "Operations : status, read, random, write, reset, exit" << endl
		<< "Algorithms : None" << endl;

	while (true) {
		cout << ">>> ";
		cin >> input;

		if (input.compare("exit") == 0) {
			return 0;
		}
		else if (input.compare("reset") == 0) {
			// Free the memory status.
			free(storage);
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
					<< storage->getPage(page)->getBlock(block).getData() << endl;
			}
			else {
				cout << "Invalid indexes." << endl;
			}

			cout << endl;
		}
		else if (input.compare("random") == 0) {

			random_device rd;
			mt19937_64 gen(rd());

			uniform_int_distribution<int> dis(0, MAX_ERASURE_LIMIT);

			for (int i = 0; i < PAGE_COUNT; i++) {
				for (int j = 0; j < BLOCK_COUNT; j++) {
					for (int k = 0; k < dis(gen); k++)
						storage->getPage(i)->getBlock(j).setData("fafF");
				}
			}
		}
		else {
			cout << "Invalid command." << endl;
		}
	}

	free(storage);
	return 0;
}