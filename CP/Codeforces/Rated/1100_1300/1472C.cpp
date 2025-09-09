// https://codeforces.com/problemset/problem/1472/C

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

void solve() {

    size_t n = 0UL;
    std::cin >> n;

    std::vector<size_t> a(n + 1);
    for (size_t i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }

    std::vector<size_t> dp(n + 1);
    dp[n] = a[n];

    for (int64_t i = n - 1; i > 0; --i) {
        if (a[i] + i <= n) {
            dp[i] = dp[a[i] + i] + a[i];
        } else {
            dp[i] = a[i];
        }
    }

    std::cout << *std::max_element(dp.begin(), dp.end()) << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t t = 0UL;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}