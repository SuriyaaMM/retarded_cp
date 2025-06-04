#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

int main(int, char**) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t n = 0UL;
    std::cin >> n;

    std::vector<std::vector<char>> grid(
        n, std::vector<char>(n));  // No need to initialize to '.'
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            std::cin >> grid[i][j];
        }
    }

    // dp table
    // dp[i][j] = number of paths that can be used to arrive at cell (i, j)
    std::vector<std::vector<size_t>> dp(
        n, std::vector<size_t>(n, 0));  // Initialize all to 0

    const size_t MOD = 1000000000 + 7;  // Correct modulo constant

    // Handle starting position
    if (grid[0][0] == '*') {
        dp[0][0] = 0;  // Start is a trap, no paths
    } else {
        dp[0][0] = 1;  // One way to be at the start
    }

    // Fill first row
    for (size_t j = 1; j < n; ++j) {
        if (grid[0][j] == '*') {
            dp[0][j] = 0;  // Current cell is a trap
        } else {
            // Paths to (0,j) only come from (0,j-1).
            // dp[0][j-1] will be 0 if (0,j-1) was a trap or unreachable.
            dp[0][j] = dp[0][j - 1];
        }
    }

    // Fill first column
    for (size_t i = 1; i < n; ++i) {
        if (grid[i][0] == '*') {
            dp[i][0] = 0;  // Current cell is a trap
        } else {
            // Paths to (i,0) only come from (i-1,0).
            // dp[i-1][0] will be 0 if (i-1,0) was a trap or unreachable.
            dp[i][0] = dp[i - 1][0];
        }
    }

    // Fill the rest of the grid
    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 1; j < n; ++j) {
            if (grid[i][j] == '*') {
                dp[i][j] = 0;  // Current cell is a trap
            } else {
                // Sum paths from above and from left, applying modulo at each addition
                dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % MOD;
            }
        }
    }

    std::cout << dp[n - 1][n - 1]
              << std::endl;  // Modulo already applied in the loop

    return 0;
}