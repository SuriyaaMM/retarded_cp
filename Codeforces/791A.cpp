#include <iostream>
#include <cmath>

int main(int argc, char* argv[]) {

	size_t a = 0ULL, b = 0ULL, n = 0ULL;

	std::cin >> a >> b;

	while (a <= b){
		
		a *= 3; b *= 2; ++n;
	}

	std::cout << n;

	return 0;
}
