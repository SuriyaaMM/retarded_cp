#include <algorithm>
#include <cstddef>
#include <iostream>
#include <limits>
#include <vector>

void solve() {
    size_t n = 0UL;
    std::cin >> n;

    std::vector<size_t> a(n, 0);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    std::vector<size_t> dp(n + 2, std::numeric_limits<size_t>::max());

    // Base case: no elements processed, no deletions
    dp[0] = 0;

    for (size_t i = 0; i < n; ++i) {
        // Case 1: skip a[i] (delete it)
        dp[i + 1] = std::min(dp[i + 1], dp[i] + 1);

        // Case 2: try forming a block at i
        if (i + a[i] < n) {
            dp[i + a[i] + 1] = std::min(dp[i + a[i] + 1], dp[i]);
        }
    }

    std::cout << dp[n] << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t t = 0UL;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
