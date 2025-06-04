// https://codeforces.com/gym/302977/problem/C

#include <array>
#include <cstddef>
#include <iostream>
#include <vector>

int main(int, char**) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t n = 0UL;
    std::cin >> n;

    using pair_t = std::pair<size_t, std::array<char, 3>>;

    std::vector<pair_t> vitamins(n + 1);

    for (size_t i = 1; i < n + 1; ++i) {
        std::string s = "";
        std::cin >> vitamins[i].first;

        if (s.size() == 1) {
            vitamins[i].second[0] = s[0];
            vitamins[i].second[1] = '0';
            vitamins[i].second[2] = '0';
        } else if (s.size() == 2) {
            vitamins[i].second[0] = s[0];
            vitamins[i].second[1] = s[1];
            vitamins[i].second[2] = '0';
        } else {
            vitamins[i].second[0] = s[0];
            vitamins[i].second[1] = s[1];
            vitamins[i].second[2] = s[2];
        }
    }

    // solution

    // 4 states are 0 vitamins, 1 vitamin, 2 vitamin, 3 vitamins
    // dp(i, j) -> minimum number of obtaining j vitamins at ith index in given vitamins
    std::vector<std::array<size_t, 4>> dp;
    // base cases
    dp[0][0] = 1;
    dp[0][1] = 0;
    dp[0][2] = 0;
    dp[0][3] = 0;

    for (size_t i = 1; i < n; ++i) {

        auto& [current_juice_cost, vitamins_in_current_juice] = vitamins[i];
    }

    return 0;
}
