#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdint.h>
#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << ERROR ": couldn't open the file." << std::endl;
		return 1;
	}
	std::ifstream inputfile(argv[1]);
	if (!inputfile.is_open()) {
		std::cerr << ERROR ": couldn't open " << argv[1] << "." << std::endl;
		return 1;
	}

	BitcoinExchange be;
	std::string line;

	std::getline(inputfile, line);
	while (std::getline(inputfile, line)) {
		std::string::iterator pipeit = std::find(line.begin(), line.end(), '|');
		if (pipeit == line.end()) {
			std::cerr << ERROR ": bad input => '" << line << "'" << std::endl;
			continue ;
		}
		uint64_t pipepos = pipeit - line.begin();
		std::string date = line.substr(0, pipepos);
		be.stringTrim(date);
		if (!be.validDate(date))
			continue ;
		float value = std::atof(line.substr(pipepos + 1, line.length() - pipepos).c_str());
		if (value < 0 || value > 1000) {
			std::cerr << ERROR ": value must be between 0 and 1000 => '" << line << "'" << std::endl;
			continue ;
		}
		
		try {
			float exchangeRate = be.getExchangeRate(date);
			std::cout << date << " => " << value << " = " << value * exchangeRate << std::endl;
		} catch (std::exception& e) {
			std::cerr << e.what() << " => '" << line << "'" << std::endl;
		}
	}
	return 0;
}
