#include <iostream>
#include <cstdint>
#include <cmath>
#include <vector>

int main() {

	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	size_t N = 0ULL, K = 0ULL;

	std::cin >> N >> K;

	std::vector<size_t> A(N);

	for (size_t i = 0; i < N; ++i) {

		size_t Ai = 0ULL;
		std::cin >> Ai;
		A[i] = Ai;
	}

	// solution
	
	// ex: for k = 3, 10^3 - 1 = 999
	
	size_t MaxDisplay = 1ULL;

	for (size_t i = 1; i <= K; ++i) {

		MaxDisplay *= 10;
	}

	MaxDisplay = MaxDisplay - 1;


	size_t Product = 1ULL;

	for (size_t i = 0; i < N; ++i) {

		if (Product  > (MaxDisplay / A[i])) {

			Product = 1ULL;
		}
		else {

			Product *= A[i];
		}
	}

	std::cout << Product << std::endl;

	return 0;
}
