// https://codeforces.com/problemset/problem/1926/C

#include <cstddef>
#include <iostream>
#include <vector>

const size_t MAXN = static_cast<size_t>(2e5) + 10;

std::vector<size_t> dp(MAXN, 0);

size_t sum_of_digits(size_t x) {
    size_t sum = 0;
    while (x) {
        sum += x % 10;
        x /= 10;
    }

    return sum;
}

void solve() {

    size_t n = 0UL;
    std::cin >> n;

    std::cout << dp[n] << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    dp[0] = 0;
    for (size_t i = 1; i < MAXN; ++i) {
        dp[i] = dp[i - 1] + sum_of_digits(i);
    }

    size_t t = 0UL;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}