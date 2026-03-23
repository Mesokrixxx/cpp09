#include "PmergeMe.hpp"
#include <stdlib.h>
#include <time.h>

#define TOMICRO(ns) ((f64)(ns) / 1000.0)

const char *PmergeMe::InvalidArgumentException::what() const throw() {
	return ERROR "arguments must be positive integers";
}

const char *PmergeMe::NoArgumentException::what() const throw() {
	return ERROR "no given arguments";
}

PmergeMe::PmergeMe() {
	throw PmergeMe::NoArgumentException();
}

PmergeMe::PmergeMe(int argc, char **argv) {
	if (!argc)
		throw PmergeMe::NoArgumentException();
	_viinst = _now();
	_vec.reserve(argc);
	for (int i = 0; i < argc; i++) {
		int num = std::atoi(argv[i]);
		if (num < 0)
			throw PmergeMe::InvalidArgumentException();
		_vec.push_back(num);
	}
	_viinst = _now() - _viinst;
	_sortvec();

	_diinst = _now();
	for (int i = 0; i < argc; i++) {
		int num = std::atoi(argv[i]);
		if (num < 0)
			throw PmergeMe::InvalidArgumentException();
		_deq.push_back(num);
	}
	_diinst = _now() - _diinst;
	_sortdeq();
}

PmergeMe::PmergeMe(const PmergeMe& other): _vec(other._vec) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	if (this != &other) {
		_vec = other._vec;
	}
	return *this;
}

#include <iostream>
PmergeMe::~PmergeMe() {};

f64 PmergeMe::vecIInsertTime() const { return TOMICRO(_viinst); }
f64 PmergeMe::vecMergeTime() const { return TOMICRO(_vmrgt); }
f64 PmergeMe::vecInsertTime() const { return TOMICRO(_vinst); }
f64 PmergeMe::vecTotalTime() const { return TOMICRO(_viinst + _vmrgt + _vinst); }

f64 PmergeMe::deqIInsertTime() const { return TOMICRO(_diinst); }
f64 PmergeMe::deqMergeTime() const { return TOMICRO(_dmrgt); }
f64 PmergeMe::deqInsertTime() const { return TOMICRO(_dinst); }
f64 PmergeMe::deqTotalTime() const { return TOMICRO(_diinst + _dmrgt + _dinst); }

u64 PmergeMe::_now() {
	timespec tp;
	
	clock_gettime(CLOCK_MONOTONIC, &tp);
	return (u64)tp.tv_sec * 1000000000UL + tp.tv_nsec;
}

void PmergeMe::_sortvec() {
	_vmrgt = _now();
	{
		for (size_t order = 1; order < _vec.size(); order *= 2) {
			int lasttop = -1;
			int lasttopindex;
			for (size_t i = 0; i < _vec.size(); i += order) {
				int topindex = min((size_t)(i + order - 1), _vec.size() - 1);
				int top = _vec[topindex];
				if (lasttop > top) {
					std::vector<int>::iterator begin = _vec.begin() + i;
					std::vector<int>::iterator end = _vec.begin() + topindex + 1;

					std::vector<int> tmp(begin, end);
					_vec.erase(begin, end);
					_vec.insert(_vec.begin() + lasttopindex - order, tmp.begin(), tmp.end());
				}
				lasttop = top;
				lasttopindex = topindex;
			}
		}
	}
	_vmrgt = _now() - _vmrgt;
	_vinst = _now();
	{

	}
	_vinst = _now() - _vinst;
}

void PmergeMe::_sortdeq() {
	_dmrgt = _now();
	_dmrgt = _now() - _dmrgt;
	
	_dinst = _now();
	_dinst = _now() - _dinst;
}
