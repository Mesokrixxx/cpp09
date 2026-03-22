#include <iostream>
#include "RPN.hpp"

int main(int argc, char **argv) {
	if (argc < 2) {
		std::cerr << ERROR "arguments are expected." << std::endl;
		return 1;
	}

	for (int i = 1; i < argc; i++) {
		RPN rpn;

		try {
			for (size_t j = 0; argv[i][j]; j++) {
				char c = argv[i][j];
				if ((unsigned)(c - '\t') <= 4 || c == ' ')
					continue ;
				if ((unsigned)(c - '0') <= 9)
					rpn.add(c - '0');
				else
					rpn.op(c);
			}

			i64 result = rpn.result();
			std::cout << result << std::endl;
		} catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}

	return 0;
}
