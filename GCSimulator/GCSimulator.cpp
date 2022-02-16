﻿/* The Simulation of Garbage Collection
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
#include "Greedy.h"
using namespace std;

int main(void) {
	// Initalize new flash storage
	Storage* storage = new Storage();

	string input = "", p = "", b = "";
	int block = -1, page = -1;

	cout << "Operations : status, read, write, reset, format, exit" << endl
		<< "Garbage Collectors : greedy" << endl;

	while (true) {
		cout << ">>> ";
		cin >> input;

		if (input.compare("exit") == 0) {
			return 0;
		}
		else if (input.compare("reset") == 0) {
			// Free the memory status
			delete(storage);
			// Initalize new storage pointer
			storage = new Storage();
			cout << "Reset complete." << endl << endl;
		}
		else if (input.compare("status") == 0) {
			// Status command shows simple status of the flash storage
			storage->printStat();
			cout << endl;
		}
		else if (input.compare("read") == 0) {
			// Read command reads data from a single page from the single block and shows it
			cout << "Input (Block Page) : ";
			cin >> p >> b;

			// Parse the integer from the string
			try {
				block = stoi(p);
				page = stoi(b);
			}
			catch (exception& e) {
				cout << "Invalid values." << endl;
			}

			if (0 <= block && block <= BLOCK_COUNT && 0 <= page && page <= PAGE_COUNT) {
				cout << "Block " << block << ", Page " << page << " : "
					<< storage->getBlock(block)->getBlockPage()[page].getData() << endl;
			}
			else {
				cout << "Invalid indexes." << endl;
			}

			cout << endl;
		}
		else if (input.compare("write") == 0) {
			/* range[0] : begin block
			range[1] : end block */
			int* range = new int[2];

			// Input sequence
			cout << endl << "Input range of block (begin end). Last block num : " << BLOCK_COUNT - 1 << endl
				<< "Range >>> ";
			cin >> range[0] >> range[1];

			// Write data to cell
			int times, max = ceil(MAX_ERASURE_LIMIT / ceil((double)readText().length()
				/ ((range[1] - range[0]) * PAGE_COUNT * MAX_LENGTH)));

			// Calculate max times of writing
			cout << "How many times do you want to write? (Max : " << max << ")" << endl
				<< "Times >>> ";
			cin >> times;

			// Write text
			writeText(&storage, times, range);

		}
		else if (input.compare("greedy") == 0) {
			Greedy* g = new Greedy();
			g->greedyMain(&storage);
		}
		else if (input.compare("format") == 0) {
			storage->formatData(0, BLOCK_COUNT - 1);
			cout << "Format completed." << endl;
		}
		else {
			cout << "Invalid command." << endl;
		}
	}

	delete(storage);
}