// https://codeforces.com/problemset/problem/1791/E

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main(int, char**) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t t = 0UL;
    std::cin >> t;

    for (size_t i = 0; i < t; ++i) {

        size_t n = 0UL;
        std::cin >> n;

        std::vector<int64_t> a(n, 0);

        for (size_t j = 0; j < n; ++j) {
            std::cin >> a[j];
        }

        // flow of negatives concept
        int64_t abs_sum = 0UL;
        int64_t num_negative = 0UL,
                min_abs = std::numeric_limits<int64_t>::max();

        for (size_t j = 0; j < n; ++j) {

            if (a[j] < 0) {
                ++num_negative;
            }
            abs_sum += std::abs(a[j]);
            min_abs = std::min(min_abs, std::abs(a[j]));
        }

        if (num_negative % 2 == 0) {
            std::cout << abs_sum << std::endl;
        } else {
            std::cout << abs_sum - 2 * min_abs << std::endl;
        }
    }

    return 0;
}