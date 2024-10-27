#include <iostream>
#include <vector>
#include <string>
#include "Menu.h"
#include "Utility.h"
#include "Records.h"
#include "MenuException.cpp"
using namespace std;

const static char* OPTIONS[] = { "View Item Frequency", "View Overall Purchase Frequency", "View Overall Purchase Frequency [Histogram]" , "Exit Program" };
const string FILENAME = "CS210_Project_Three_Input_File.txt";

void Menu::runMainMenu() {
    auto records = make_unique<Records>(FILENAME);
    
    unsigned int input = 0;
    while (input != NUM_OPTIONS) {
        printMenu(OPTIONS, NUM_OPTIONS, MENU_SIZE);
        cout << "Select an option (1 - 4):\n~ ";
        input = getMenuChoice(NUM_OPTIONS);

        switch (input) {
            case 1: {
                records.get()->viewItemsList();
                records.get()->viewItemPurchaseFrequency();
                promptRepeatOptionOne(records);
                break;
            }
            case 2:
                records.get()->viewOverallPurchaseFrequency();
                break;
            case 3:
                records.get()->viewOverallPurchaseFrequency_Histogram();
                break;
        }

        if (input != NUM_OPTIONS) {
            cout << "Press ENTER to continue . . .";
            cin.ignore();
            cin.get(); // Allows ENTER to continue loop
            cout << endl;
        }
    }
}

/******************************************************************************************************************************/
/******************************************************************************************************************************/

/**
 * Prints menu
 *
 * @param *strings[], nonempty array of choices
 * @param Width, width of each line, will be comfortably bigger than the longest string
 *
 */
void Menu::printMenu(const char* t_options[], unsigned int t_numStrings, unsigned char t_width) {
    cout << nCharString(t_width, '*') << endl;

    for (int i = 0; i < t_numStrings; ++i) {
        const char* option = OPTIONS[i];

        cout << "* " << i + 1 << " - " << option
            << nCharString((t_width - 7) - strlen(option), ' ') << "*"
            << endl;
    }

    cout << nCharString(t_width, '*') << endl;
}

/**
 * Gets menu choice 1 through maxChoice, inclusive
 *
 * @param maxChoice, maximum choice index, a number between 1 and 9, inclusive
 * @return The first legal choice input, could be 1 through maxChoice, inclusive
 */
unsigned int Menu::getMenuChoice(unsigned int t_maxChoice) {
    unsigned int input;
    bool isValidInput = false;

    cin >> input;
    isValidInput = (input > 0 && input <= NUM_OPTIONS) ? true : false;
        
    while (isValidInput == false) {
        printf("\nInvalid input. Choose a selection between 1 and %d.\n~ ", NUM_OPTIONS);
        cin >> input;
        isValidInput = (input > 0 && input <= NUM_OPTIONS) ? true : false;
    }

    cout << endl;

    return input;
}

/**
 Prompts user the option the rerun option one: View Item Purchase Frequency.

 * @param Records object
 */
void Menu::promptRepeatOptionOne(unique_ptr<Records>& records) {
    string retry = "Y";

    while (retry == "Y" || retry == "V") {
        try {
            cout << "Would you like to view another item? Options:\n"
                << "   Y - Yes\n"
                << "   N - No\n"
                << "   V - View Items List\n~ ";
            cin >> retry;
            cout << endl;

            retry[0] = toupper(retry[0]);

            if (retry == "Y") { records.get()->viewItemPurchaseFrequency(); } 
            else if (retry == "V") { records.get()->viewItemsList(); } 
            else if (retry != "N" && retry != "Y") {
                throw MenuException(("Invalid input '" + retry + "'. Choose either 'Y' or 'N'.\n").c_str());
            }
            
        } catch (MenuException& e) {
            cout << e.what() << endl;
            promptRepeatOptionOne(records); // Run recursively until a valid option is chosen
        }
    }
}