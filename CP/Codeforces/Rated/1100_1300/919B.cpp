// https://codeforces.com/problemset/problem/919/B

#include <cstddef>
#include <cstdlib>
#include <iostream>

size_t sum_of_digits(size_t n) {
    size_t sum = 0UL;
    while (n) {
        sum += (n % 10);
        n /= 10;
    }
    return sum;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t k = 0UL;

    std::cin >> k;

    size_t number = 1UL, perfect_numbers_found = 0UL;

    while (true) {

        if (sum_of_digits(number) == 10) {

            ++perfect_numbers_found;

            if (perfect_numbers_found == k) {
                std::cout << number << std::endl;
                break;
            }
        }
        ++number;
    }

    return 0;
}