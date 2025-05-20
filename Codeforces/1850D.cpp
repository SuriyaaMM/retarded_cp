#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>

int main(int argc, char* argv[]) {

	std::ios_base::sync_with_stdio(false);

	size_t numTestCases = 0ULL;

	std::cin >> numTestCases;

	std::vector <std::vector<size_t>> problems;
	std::vector<size_t> atMaxDifficulties;
	atMaxDifficulties.resize(numTestCases);
	problems.resize(numTestCases);

	for (size_t i = 0; i < numTestCases; ++i) {

		size_t numProblems = 0ULL, atMaxDifficulty = 0ULL;
		std::cin >> numProblems >> atMaxDifficulty;

		atMaxDifficulties[i] = atMaxDifficulty;

		problems[i].resize(numProblems);

		for (size_t j = 0; j < numProblems; ++j) {

			size_t problemDifficulty = 0ULL;
			std::cin >> problemDifficulty;

			problems[i][j] = problemDifficulty;
		}
	}

	for (size_t i = 0; i < numTestCases; ++i) {

		std::sort(problems[i].begin(), problems[i].end());

		size_t problemIndex = 0ULL;

		for (size_t j = 0; j < problems[i].size() - 1; ++j) {

			if (problems[i][j] - problems[i][j + 1] > atMaxDifficulties[j]) {

				
			}
		}

		std::cout << problems[i].size() - problemIndex << std::endl;
	}

	return 0;
}
