// https://atcoder.jp/contests/abc407/tasks/abc407_b

#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector>

constexpr size_t abs_int64_t(int64_t& num) noexcept {

    if (num < 0)
        return static_cast<size_t>(-num);
    else
        return static_cast<size_t>(num);
}

int main(int, char**) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t x = 0UL, y = 0UL;

    std::cin >> x >> y;

    size_t total_outcomes = 36UL, fav_outcomes = 0UL;

    for (size_t i = 1; i < 7; ++i) {
        for (size_t j = 1; j < 7; ++j) {

            int64_t diff = static_cast<int64_t>(i - j);
            if (((i + j) >= x) || abs_int64_t(diff) >= y) {
                ++fav_outcomes;
            }
        }
    }

    std::cout << std::setprecision(11)
              << (double)fav_outcomes / (double)total_outcomes << std::endl;

    return 0;
}