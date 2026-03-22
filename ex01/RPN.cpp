#include "RPN.hpp"

const char *RPN::ImpossibleOperationException::what() const throw() {
	return ERROR "not enough numbers to perform operation";
}

const char *RPN::UnknownOperationException::what() const throw() {
	return ERROR "unknown operation type";
}

const char *RPN::StackNotEmptyException::what() const throw() {
	return ERROR "stack isn't empty after taking the result";
}

const char *RPN::DivisionByZeroException::what() const throw() {
	return ERROR "division by zero";
}

RPN::RPN() {}

RPN::RPN(const RPN& other): _st(other._st) {}

RPN& RPN::operator=(const RPN& other) {
	if (this != &other) {
		_st = other._st;
	}
	return *this;
}

RPN::~RPN() {}

#include <iostream>

void RPN::add(i8 digit) {
	_st.push(digit);
} 

void RPN::op(char op) {
	if (op != '+' && op != '-' && op != '*' && op != '/')
		throw RPN::UnknownOperationException();
	if (_st.size() < 2)
		throw RPN::ImpossibleOperationException();
	i64 y = _st.top(); _st.pop();
	i64 x = _st.top(); _st.pop();
	switch (op) {
		case ('+'): {
			x += y;
		} break ;

		case ('-'): {
			x -= y;
		} break ;

		case ('*'): {
			x *= y;
		} break ;

		case ('/'): {
			if (y == 0)
				throw RPN::DivisionByZeroException();
			x /= y;
		} break ;
	}
	_st.push(x);
}

i64 RPN::result(void) {
	if (_st.size() > 1)
		throw RPN::StackNotEmptyException();
	return _st.top();
}
