// https://codeforces.com/problemset/problem/1418/C

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

void solve() {

    int64_t n = 0LL;
    std::cin >> n;

    std::vector<int64_t> a(n, 0);
    for (auto it = a.begin(); it != a.end(); ++it) {
        std::cin >> *it;
    }

    std::vector<std::vector<int64_t>> dp(
        n + 2,
        std::vector<int64_t>(2, std::numeric_limits<int64_t>::max() - 2));

    // initially it is our friends turn
    dp[0][0] = 0;

    for (size_t i = 0; i < n; ++i) {
        for (size_t who = 0; who < 2; ++who) {
            // Skip unreachable states
            if (dp[i][who] >= 10e9) {
                continue;
            }

            if (who == 0) {  // Friend's turn
                // Option 1: Kill 1 boss, then it's your turn
                if (i + 1 <= n) {
                    int64_t cost = dp[i][who] + (a[i] == 1);
                    dp[i + 1][1] = std::min(dp[i + 1][1], cost);
                }

                // Option 2: Kill 2 bosses, then it's your turn
                if (i + 2 <= n) {
                    int64_t cost = dp[i][who] + (a[i] == 1) + (a[i + 1] == 1);
                    dp[i + 2][1] = std::min(dp[i + 2][1], cost);
                }

            } else {  // Your turn
                // Option 1: Kill 1 boss, then it's friend's turn
                if (i + 1 <= n) {
                    dp[i + 1][0] = std::min(dp[i + 1][0], dp[i][who]);
                }

                // Option 2: Kill 2 bosses, then it's friend's turn
                if (i + 2 <= n) {
                    dp[i + 2][0] = std::min(dp[i + 2][0], dp[i][who]);
                }
            }
        }
    }
    std::cout << std::min(dp[n][0], dp[n][1]) << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int64_t t = 0LL;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}