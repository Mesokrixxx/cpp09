#pragma once

#include <stack>
#include <stdint.h>
#include <exception>

typedef int8_t i8;
typedef int64_t i64;

#define COLRESET "\033[0m"
#define COLRED "\033[0;31m"
#define ERROR COLRED "Error" COLRESET ": "

class RPN {
public:
	class UnknownOperationException : public std::exception {
		const char *what(void) const throw();
	};

	class ImpossibleOperationException : public std::exception {
		const char *what(void) const throw(); 
	};

	class StackNotEmptyException : public std::exception {
		const char *what(void) const throw();
	};

	class DivisionByZeroException : public std::exception {
		const char *what(void) const throw();
	};

	RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN();

	void add(i8 digit);
	void op(char op);
	i64 result(void);

private:
	std::stack<i64> _st; 
};
