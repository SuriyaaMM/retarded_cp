
#include <iostream>
#include <vector>
#include <cstdint>

int main(int argc, char* argv[]) {

	std::ios_base::sync_with_stdio(false);

	size_t testCases = 0ULL;
	std::cin >> testCases;

	// binary array
	std::vector<std::vector<size_t>> barray;
	barray.reserve(testCases);  // optional but fine

	// construction
	for (size_t i = 0; i < testCases; ++i) {
		size_t barrayLength = 0ULL;
		std::cin >> barrayLength;

		std::vector<size_t> arr(barrayLength);  // temp vector

		for (size_t j = 0; j < barrayLength; ++j) {
			std::cin >> arr[j];
		}

		barray.emplace_back(std::move(arr));  // store the vector
	}

	for (size_t i = 0; i < barray.size(); ++i) {

		size_t numConsecZeroes = 0ULL, max = 0ULL;

		for (size_t j = 0; j < barray[i].size(); ++j) {

			if (barray[i][j] == 0) {
				++numConsecZeroes;
				if (numConsecZeroes > max)
					max = numConsecZeroes;
			}
			else {
				numConsecZeroes = 0;
			}
		}

		std::cout << max << std::endl;
	}

}
