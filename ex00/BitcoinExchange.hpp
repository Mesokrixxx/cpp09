#pragma once

#include <map>
#include <string>
#include <exception>

#define COLRESET "\033[0m"
#define COLRED "\033[0;31m"
#define ERROR COLRED "Error" COLRESET

class BitcoinExchange {
public:
	class DateNotPossibleException : public std::exception {
		const char *what(void) const throw();
	};

    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange& operator=(const BitcoinExchange &other);
    ~BitcoinExchange();

	bool validDate(const std::string& date);
	void stringTrim(std::string& date);
	float getExchangeRate(const std::string& date);

private:
    std::map<std::string, float> _db;
};
