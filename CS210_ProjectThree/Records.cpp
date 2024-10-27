#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "Records.h"
#include "Utility.h"
#include "RecordInquiryException.cpp"
using namespace std;

Records::Records(string filename_read) {
	this->filename = filename_read;
	
	inRecordsFS.open(filename_read);
	if (!inRecordsFS.is_open()) {
		cout << printf("Could not open file %s.", filename_read.c_str()) << endl;
	}
	
	this->records = getRecords(filename_read); // Allows read-only access to the map of records.

	outRecordsFS.open(FILENAME_WRITE);
	if (!outRecordsFS.is_open()) {
		cout << printf("Could not open file %s.", FILENAME_WRITE.c_str()) << endl;
	}
	writeReport(records); // Generate report of items and frequencies.

	configureResultsFormat();
}

/*
Menu Option One:

Prompt a user to input the item, or word, they wish to look for.
Return a numeric value for the frequency of the specific word.
*/
void Records::viewItemPurchaseFrequency() {
	string item;
	cout << "What item would you like to see?\n~ ";
	try {
		cin >> item;
		item[0] = toupper(item[0]); // Ensures the entries (which are capitalized) are found, if present
		cout << endl;
		if (!records.count(item)) {
			throw RecordInquiryException(("Item '" + item + "' does not exist. Refer to available list of items.\n").c_str());
		}

		// Grammar check
		if (item[item.size() - 1] == 's') {
			printf("%s have been purchsed %d times.\n\n", item.c_str(), records.at(item));
		} else {
			printf("%s has been purchsed %d times.\n\n", item.c_str(), records.at(item));
		}
	}
	catch (RecordInquiryException& e) {
		cout << e.what() << endl;
	}
}

/*
Menu Option Two:

Print the list with numbers that represent the frequency of all items purchased.
The screen output should include every item (represented by a word) paired with the number of times that item appears in the input file, CS210_Project_Three_Input_File.txt.
*/
void Records::viewOverallPurchaseFrequency() {
	int tableLength = (maxStrLen + maxIntLength + 5 + 1) * 5; // '+5': Buffer space between entries; '+1': Space between item and frequency
	printTitle("OVERALL PURCHASE FREQUENCY", tableLength);

	int rowIndex = 1;
	for (auto record : records) {
		string item = record.first;
		unsigned int frequency = record.second;

		cout << item << " " << frequency << nCharString(maxStrLen - item.size() - to_string(frequency).size() + 3 + 5, ' ').c_str();

		if (rowIndex == 5) { // Each row will receive 5 entries
			rowIndex = 1;
			cout << endl;
			continue;
		}
		rowIndex++;
	}

	cout << endl;
}

/*
Menu Option Three:

Print the same frequency information for all the items in the form of a histogram.
Then print the name, followed by asterisks or another special character to represent the numeric amount.
The number of asterisks should equal the frequency read from the provided txt file.
*/
void Records::viewOverallPurchaseFrequency_Histogram() {
	string title = "[HISTOGRAM] OVERALL PURCHASE FREQUENCY";
	int tableLength = title.size() + 10;
	printTitle(title, tableLength);

	for (auto record : records) {
		string item = record.first;
		unsigned int frequency = record.second;
		string bar = nCharString(frequency, '*');
		
		vector<string> items = getItemsList();
		string alignRight = nCharString(maxStringLength(items) - item.size(), ' ');
		int entryLength = maxStrLen + 3 + highestFrequency; // '+3':  Seperator " | "
		string histogramAlignCenter = nCharString((tableLength - entryLength) / 2, ' ');

		printf("%s%s%s | %s\n", histogramAlignCenter.c_str(), alignRight.c_str(), item.c_str(), bar.c_str());
	}
	cout << endl;
}

/**************************************************************/
/************************HELPER METHODS************************/
/**************************************************************/

/**
 * Retrieves a map of items and their associated frequency read from a given file.
 *
 * @param String of file's name
 * @return Map with key of string and value of int
 */
map<string, unsigned int> Records::getRecords(string filename_read) {
	string item;
	map<string, unsigned int> records;

	while (!inRecordsFS.eof()) {
		inRecordsFS >> item;

		if (!records.count(item)) {
			records.emplace(item, 1);
		}
		else {
			records.at(item)++;
		}
	}

	inRecordsFS.close();

	return records;
}

/**
 * Stores all keys from a map into a vector
 *
 * @param Map with key of string and value of int
 */
void Records::writeReport(map<string, unsigned int> map) {
	for (auto record : map) {
		string item = record.first;
		unsigned int frequency = record.second;

		outRecordsFS << item << " " << frequency << endl;
	}

	outRecordsFS.close();
}

/*
	Acquires all proper dimensions for formatting the option results.
 */
void Records::configureResultsFormat() {
	this->maxStrLen = maxStringLength(getItemsList()); // Formats Titles.
	this->maxIntLength = maxIntegerLength(getFrequenciesList()); // Formats Titles.
	this->highestFrequency = getHighestFrequency(); // Formats Histogram.
}

/**
 * Stores all keys from a map into a vector
 *
 * @param Map with key of string and value of int
 * @return Vector of strings
 */
vector<string> Records::getItemsList() {
	vector<string> keys;

	for (auto record : records) {
		string item = record.first;
		keys.push_back(item);
	}

	return keys;
}

/**
 * Stores all values from a map into a vector
 *
 * @param Map with key of string and value of int
 * @return Vector of int's
 */
vector<int> Records::getFrequenciesList() {
	vector<int> values;

	for (auto record : records) {
		int frequency = record.second;
		values.push_back(frequency);
	}

	return values;
}

/*
	Prints all items acquired from data collection.
 */
void Records::viewItemsList() {
	vector<string> itemsList = getItemsList();
	int maxStrLen = maxStringLength(itemsList);

	printTitle("ITEMS LIST", (maxStrLen + 5) * 5);
	int rowIndex = 1;
	for (string item : itemsList) {
		cout << item << nCharString(maxStrLen - item.size() + 5, ' ').c_str();

		if (rowIndex == 5) {
			rowIndex = 1;
			cout << endl;
			continue;
		}
		rowIndex++;
	}
	cout << endl;
}

/*
	Prints selected option's title.
 */
void Records::printTitle(string title, int tableLength) {
	int titleStrLen = title.size();

	// Properly aligns Vertical Borders
	if (tableLength % 2 == 1) {
		tableLength--;
	}

	string titleAlignCenter = nCharString(((tableLength - titleStrLen - 1) / 2), ' ');
	string horizontalBorder = nCharString(tableLength, '=').c_str();

	printf("%s\n%c%s%s%s%c\n%s\n",
		horizontalBorder.c_str(),
		'|', titleAlignCenter.c_str(), title.c_str(), titleAlignCenter.c_str(), '|',
		horizontalBorder.c_str());
}

/*
	Helper Method for formatting the Histogram.
 */
int Records::getHighestFrequency() {
	int highestFreq = 0;
	vector<int> frequencies = getFrequenciesList();
	for (int frequency : frequencies) {
		int currFreq = frequency;
		if (currFreq > highestFreq) {
			highestFreq = currFreq;
		}
	}

	return highestFreq;
}