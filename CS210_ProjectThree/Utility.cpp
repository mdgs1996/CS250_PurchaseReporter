#include <iostream>
#include <string>
#include <vector>
#include "Utility.h"
using namespace std;

/**
 * Returns a string of length n, each character a c.
 * For example, nCharString(5, '*') should return "*****"
 *
 * @param n string length, >=0
 * @return string of n c's
 */
string nCharString(size_t n, char c) {
    string str;
    for (int i = 0; i < n; i++) {
        str += c;
    }

    return str;
}

/**
 * Returns an int representing the largest 
 * string length in a string vector
 * 
 * @param string list
 * @return string length of longest string in list
 */
int maxStringLength(vector<string> list) {
    int maxStrLen = 0;
    for (string str : list) {
        int currLen = str.size();
        if (currLen > maxStrLen) {
            maxStrLen = currLen;
        }
    }

    return maxStrLen;
}

/**
 * Returns an int based on the int 
 * having the largest string-represented size
 * in an int vector
 * 
 * @param int list
 * @return string length of longest string in list
 */
int maxIntegerLength(vector<int> list) {
    int maxVal = 0;
    for (int i : list) {
        int currVal = to_string(i).size();
        if (currVal > maxVal) {
            maxVal = currVal;
        }
    }

    return maxVal;
}