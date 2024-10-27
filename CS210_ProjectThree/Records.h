#ifndef RECORDS_H
#define RECORDS_H
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Records {
public:
	Records(string filename_read);
	void viewItemPurchaseFrequency();
	void viewOverallPurchaseFrequency();
	void viewOverallPurchaseFrequency_Histogram();
	void viewItemsList();

private:
	map<string, unsigned int> getRecords(string filename_read);
	void writeReport(map<string, unsigned int> map);
	void configureResultsFormat();
	vector<string> getItemsList();
	vector<int> getFrequenciesList();
	void printTitle(string title, int entryLength);
	int getHighestFrequency();

	const string FILENAME_WRITE = "frequency.dat";
	string filename;
	map<string, unsigned int> records;
	int maxStrLen;
	int maxIntLength;
	int highestFrequency;
	ifstream inRecordsFS;
	ofstream outRecordsFS;
};
#endif