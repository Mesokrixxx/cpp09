#include <iostream>
#include "PmergeMe.hpp"

int main(int argc, char **argv) {
	try {
		PmergeMe pme(argc - 1, argv + 1);
		std::cout << "std::vector stats:\n"
					 "  - init insertion: " << pme.vecIInsertTime() << "us\n"
					 "  - merge         : " << pme.vecMergeTime() << "us\n"
					 "  - insert        : " << pme.vecInsertTime() << "us\n"
					 "Total: " << pme.vecTotalTime() << "us\n" << std::endl;
		std::cout << "std::deque stats:\n"
					 "  - init insertion: " << pme.deqIInsertTime() << "us\n"
					 "  - merge         : " << pme.deqMergeTime() << "us\n"
					 "  - insert        : " << pme.deqInsertTime() << "us\n"
					 "Total: " << pme.deqTotalTime() << "us" << std::endl;
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	
	return 0;
}
