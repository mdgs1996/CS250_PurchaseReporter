#ifndef MENU_H
#define MENU_H
#include "Records.h"

class Menu {
public:
	void runMainMenu();
private:
	void printMenu(const char* t_options[], unsigned int t_numStrings, unsigned char t_width);
	unsigned int getMenuChoice(unsigned int t_maxChoice);
	void promptRepeatOptionOne(unique_ptr<Records>& records);

	int NUM_OPTIONS = 4;
	const unsigned int MENU_SIZE = 75;
};
#endif