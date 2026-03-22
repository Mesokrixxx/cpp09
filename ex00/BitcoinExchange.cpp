#include "BitcoinExchange.hpp"
#include <fstream>
#include <algorithm>
#include <stdint.h>
#include <iostream>
#include <math.h>

#define DATAFILE "data.csv"

const char *BitcoinExchange::DateNotPossibleException::what() const throw() {
	return ERROR ": date couldn't associate with any echange value";
}

BitcoinExchange::BitcoinExchange(): _db() {
	std::ifstream dbf(DATAFILE);
	std::string line;

	std::getline(dbf, line);
	while (std::getline(dbf, line)) {
		stringTrim(line);
		std::string::iterator commait = std::find(line.begin(), line.end(), ',');
		if (commait == line.end()) {
			std::cerr << ERROR ": expecting format 'date,value' => '" << line << "'" << std::endl;
			continue ;
		}
		uint64_t commapos = commait - line.begin();
		std::string date = line.substr(0, commapos);
		if (!validDate(date))
			continue ;
		float value = std::atof(line.substr(commapos + 1, line.length() - commapos).c_str());
		_db[date] = value;
	}
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other): _db(other._db) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other) {
		_db = other._db;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::validDate(const std::string& date) {
	std::string::const_iterator begit = date.begin();
	int year = 0;
	int month = 0;
	int day = 0;
	for (int i = 0; i < 3; i++) {
		if (begit >= date.end()) {
			std::cerr << ERROR ": date format must be year-month-day => '" << date << "'" << std::endl;
			return false;
		}
		std::string::const_iterator sepit = std::find(begit, date.end(), '-');
		int seppos = sepit - begit;
		int begpos = begit - date.begin();
		std::string tmp = date.substr(begpos, seppos);
		size_t nondigit = tmp.find_first_not_of("0123456789");
		if (nondigit != tmp.npos) {
			std::cerr << ERROR ": date format must be composed only by digits => '" << date << "'" << std::endl;
			return false;
		}
		if (i == 0)
			year = std::atoi(tmp.c_str());
		else if (i == 1) {
			month = std::atoi(tmp.c_str());
			if (month < 1 && month > 12) {
				std::cerr << ERROR ": month must be between 1 and 12 => '" << date << "'" << std::endl;
				return false;
			}
		} 
		else if (i == 2) {
			day = std::atoi(tmp.c_str());
			int maxday = 28 + (month + (int)floor(month / 8)) % 2 + 2 % month + 2 * floor(1 / month);
			bool leapyear = ((year % 100) != 0) ? ((year % 4) == 0) : ((year % 400) == 0);
			if (month == 2 && leapyear)
				maxday = 29;
			if (day < 1 || day > maxday) {
				std::cerr << ERROR ": day must be between 1 and " << maxday 
						<< " for month " << month << " (be careful with leap years)"
						<< " => '" << date << "'" << std::endl;
				return false;
			}
		}
		begit = sepit + 1;
	}
	return true;
}

void BitcoinExchange::stringTrim(std::string& str) {
	const char *ws = " \t\n\f\r\v";

	str.erase(str.find_last_not_of(ws) + 1);
	str.erase(0, str.find_first_not_of(ws));
}

float BitcoinExchange::getExchangeRate(const std::string& str) {
	std::map<std::string, float>::iterator it = _db.lower_bound(str);

	if (it->first == str)
		return it->second;

	if (it == _db.begin())
		throw BitcoinExchange::DateNotPossibleException();

	--it;
	return it->second;
}
