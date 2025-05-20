#include <iostream>
#include <cstdint>

int main(int argc, char* argv[]) {

	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	size_t A = 0ULL, B = 0ULL, C = 0ULL, D = 0ULL;

	std::cin >> A >> B >> C >> D;

	if (A == C) {

		if (D < B) {

			std::cout << "Yes" << std::endl;
		}
		else {

			std::cout << "No" << std::endl;
		}
	}
	else if(A > C) {

		std::cout << "Yes" << std::endl;
	}
	else {
		
		std::cout << "No" << std::endl;
	}
	
	return 0;
}
