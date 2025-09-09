// #include <cstddef>
// #include <iostream>
// #include <unordered_map>
// #include <utility>
// #include <vector>

// using memo_t = std::vector<std::vector<std::vector<int64_t>>>;
// using q_t = std::vector<std::pair<size_t, size_t>>;

// size_t dp(size_t i, q_t& q, size_t h, size_t m, memo_t& memo) {

//     if (memo[i][h][m] != -1)
//         return memo[i][h][m];

//     if (i >= q.size()) {
//         return memo[i][h][m] = 0;
//     }

//     if (h == 0 && m >= q[i].second) {
//         return memo[i][h][m] = dp(i + 1, q, h, m - q[i].second, memo) + 1;
//     }
//     if (m == 0 && h >= q[i].first) {
//         return memo[i][h][m] = dp(i + 1, q, h - q[i].first, m, memo) + 1;
//     }

//     if ((h == 0 && m < q[i].second) || (m == 0 && h < q[i].first)) {
//         return memo[i][h][m] = 0;
//     }

//     size_t using_magic = 0UL, not_using_magic = 0UL;
//     if (h >= q[i].first) {
//         using_magic = dp(i + 1, q, h - q[i].first, m, memo) + 1;
//     }
//     if (m >= q[i].second) {
//         not_using_magic = dp(i + 1, q, h, m - q[i].second, memo) + 1;
//     }

//     return memo[i][h][m] = std::max(using_magic, not_using_magic);
// }

// int main(int, char**) {
//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr);
//     std::cout.tie(nullptr);

//     size_t n = 0UL, h = 0UL, m = 0UL;
//     std::cin >> n >> h >> m;

//     std::vector<std::pair<size_t, size_t>> q(n);

//     std::vector<std::vector<std::vector<int64_t>>> memo(
//         n + 1, std::vector<std::vector<int64_t>>(
//                    h + 1, std::vector<int64_t>(m + 1, -1)));

//     for (size_t i = 0; i < n; ++i) {

//         size_t ai = 0UL, bi = 0UL;
//         std::cin >> ai >> bi;

//         q[i] = {ai, bi};
//     }

//     std::cout << dp(0, q, h, m, memo) << std::endl;

//     return 0;
// }

// #include <algorithm>
// #include <iostream>
// #include <vector>

// const int INF = 1e9 + 7;

// int main() {
//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr);

//     int n, h, m;
//     std::cin >> n >> h >> m;

//     std::vector<std::pair<int, int>> monsters(n);
//     for (int i = 0; i < n; ++i) {
//         std::cin >> monsters[i].first >> monsters[i].second;
//     }

//     // dp[health] = min_magic_cost
//     // dp[j] will store the minimum magic cost to have j health remaining
//     std::vector<int> dp(h + 1, INF);
//     dp[h] = 0;

//     int monsters_defeated = 0;

//     for (int i = 0; i < n; ++i) {
//         int a = monsters[i].first;
//         int b = monsters[i].second;

//         std::vector<int> next_dp(h + 1, INF);
//         bool possible_to_defeat = false;

//         for (int current_h = 0; current_h <= h; ++current_h) {
//             if (dp[current_h] == INF) {
//                 continue;
//             }
//             if (current_h >= a) {
//                 int next_h = current_h - a;
//                 int magic_cost = dp[current_h];
//                 next_dp[next_h] = std::min(next_dp[next_h], magic_cost);
//                 possible_to_defeat = true;
//             }
//             int magic_cost = dp[current_h] + b;
//             if (magic_cost <= m) {
//                 int next_h = current_h;
//                 next_dp[next_h] = std::min(next_dp[next_h], magic_cost);
//                 possible_to_defeat = true;
//             }
//         }
//         if (!possible_to_defeat) {
//             break;
//         }
//         dp = next_dp;
//         monsters_defeated++;
//     }

//     std::cout << monsters_defeated << std::endl;

//     return 0;
// }

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

using q_t = std::vector<std::pair<int, int>>;

void solve() {
    size_t n, h, m;
    std::cin >> n >> h >> m;

    q_t q(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> q[i].first >> q[i].second;
    }

    // dp[i][j] = maximum health after defeating exactly i monsters using exactly j magic
    // Initialize with -1 (impossible state)
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, -1));

    // base case: 0 monsters defeated, 0 magic used, full health
    dp[0][0] = h;

    // for defeating each monster starting from 1
    for (size_t i = 0; i < n; ++i) {
        // we will iterate through all possible magic usages
        for (size_t j = 0; j <= m; ++j) {
            // if we haven't at all reached this state before,
            if (dp[i][j] == -1)
                continue;

            int current_health = dp[i][j];
            int health_cost = q[i].first;
            int magic_cost = q[i].second;

            // Option 1: Use health to defeat monster i
            if (current_health >= health_cost) {
                dp[i + 1][j] =
                    std::max(dp[i + 1][j], current_health - health_cost);
            }

            // Option 2: Use magic to defeat monster i
            if (j + magic_cost <= m) {
                dp[i + 1][j + magic_cost] =
                    std::max(dp[i + 1][j + magic_cost], current_health);
            }
        }
    }

    // Find the maximum number of monsters we can defeat
    int max_monsters = 0;
    for (size_t i = 0; i <= n; ++i) {
        for (size_t j = 0; j <= m; ++j) {
            if (dp[i][j] >= 0) {
                max_monsters = i;
            }
        }
    }

    std::cout << max_monsters << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();
    return 0;
}