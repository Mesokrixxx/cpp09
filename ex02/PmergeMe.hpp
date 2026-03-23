#pragma once

#include <exception>
#include <vector>
#include <deque>
#include <stdint.h>

typedef uint64_t u64;
typedef double   f64;

#define COLRESET "\033[0m"
#define COLRED "\033[0;31m"
#define ERROR COLRED "Error" COLRESET ": "

template <typename T>
T min(T a, T b) {
	return a < b ? a : b;
}

class PmergeMe {
public:
	class NoArgumentException : public std::exception {
		const char *what(void) const throw();
	};

	class InvalidArgumentException : public std::exception {
		const char *what(void) const throw();
	};

	PmergeMe();
	PmergeMe(int argc, char **argv);
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();

	f64 vecIInsertTime() const;
	f64 vecMergeTime() const;
	f64 vecInsertTime() const;
	f64 vecTotalTime() const;

	f64 deqIInsertTime() const;
	f64 deqMergeTime() const;
	f64 deqInsertTime() const;
	f64 deqTotalTime() const;

private:
	u64 _now();

	void _sortvec();
	std::vector<int> _vec;
	u64 _viinst, _vmrgt, _vinst;

	void _sortdeq();
	std::deque<int> _deq;
	u64 _diinst, _dmrgt, _dinst;
};
