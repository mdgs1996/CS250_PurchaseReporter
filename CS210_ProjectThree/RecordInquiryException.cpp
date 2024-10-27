#include <exception>
#include <iostream>
#include <string>

using namespace std;

class RecordInquiryException : public exception {
public:
	RecordInquiryException(const char* msg) : m_message(msg) {}
	const char* what() const throw() { return m_message.c_str(); }
private:
	string m_message;
};