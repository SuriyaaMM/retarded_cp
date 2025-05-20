
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

int main(int argc, char* argv[]) {

	std::ios_base::sync_with_stdio(false);

	size_t testCases = 0ULL;

	std::cin >> testCases;

	std::vector<std::string> strings = {};

	for (size_t i = 0; i < testCases; ++i) {

		std::string stringi = "";
		std::cin >> stringi;
		strings.emplace_back(stringi);
	}

	for (std::string& rstring : strings) {

		uint32_t numA = 0U, numB = 0U;

		for (const char& rchar : rstring) {

			rchar == 'A' ? ++numA : ++numB;
		}

		if (numA > numB)
			std::cout << "A" << std::endl;
		else
			std::cout << "B" << std::endl;
	}
}
