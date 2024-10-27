#include <exception>
#include <iostream>
#include <string>

using namespace std;

class MenuException : public exception {
public:
	MenuException(const char* msg) : m_message(msg) {}
	const char* what() const throw() { return m_message.c_str(); }
private:
	string m_message;
};