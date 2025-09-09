#include <algorithm>  // For std::max and std::max_element
#include <iostream>
#include <vector>
// #include <unordered_map> // Not strictly needed if using vector for points_for_num

void solve() {
    size_t n;
    std::cin >> n;

    std::vector<long long> points_for_num(100001, 0);
    long long max_val = 0;

    for (size_t i = 0; i < n; ++i) {
        size_t num;
        std::cin >> num;
        points_for_num[num] += num;
        if (num > max_val) {
            max_val = num;
        }
    }

    std::vector<long long> dp(max_val + 1, 0);

    // Base cases
    if (max_val >= 1) {
        dp[1] = points_for_num[1];
    }
    // Note: dp[0] is already 0 by vector initialization

    // Fill DP table
    for (size_t i = 2; i <= max_val; ++i) {
        // Option 1: Don't take number 'i'. Max points are dp[i-1].
        // Option 2: Take number 'i'. Points are points_for_num[i] + dp[i-2].
        //           (dp[i-2] because taking 'i' means we can't take 'i-1').
        dp[i] = std::max(dp[i - 1], dp[i - 2] + points_for_num[i]);
    }

    // The maximum points will be stored in dp[max_val]
    std::cout << dp[max_val] << std::endl;
}

int main(int, char**) {
    // Optimize C++ standard streams for faster input/output
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}