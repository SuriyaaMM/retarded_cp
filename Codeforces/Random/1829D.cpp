// https://codeforces.com/problemset/problem/1829/D

#include <cstddef>
#include <iostream>
#include <unordered_map>

bool dp(size_t n, size_t m, std::unordered_map<size_t, bool>& memo) {

    if (n == m)
        return true;
    if (m > n || n < 3 || n % 3 != 0)
        return false;
    if (memo.count(n))
        return memo[n];

    return memo[n] = dp(n / 3, m, memo) || dp(2 * n / 3, m, memo);
}

int main(int, char**) {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t t = 0UL;
    std::cin >> t;

    for (size_t i = 0; i < t; ++i) {

        size_t n = 0UL, m = 0UL;
        std::cin >> n >> m;

        // solution
        /*
            we can split n into x and y such that x = 2y and x + y = n, this is a linear equation
            solving:
                2y + y = n, 3y = n, (y = n/3, x = 2n/3)
            so at each step we can try splitting to n/3 and 2n/3
            also m must be less than n which is one constraint
            and n >= 3, else we cannot split so 0
        */

        std::unordered_map<size_t, bool> memo;

        if (dp(n, m, memo))
            std::cout << "YES" << std::endl;
        else
            std::cout << "NO" << std::endl;
    }

    return 0;
}