#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>

int64_t dp(int64_t index, int64_t& n, std::vector<int64_t>& h,
           std::unordered_map<int64_t, int64_t>& memo) {
    if (index == n - 1)
        return 0UL;
    if (index == n - 2)
        return std::abs(h[n - 2] - h[n - 2]);

    if (memo.count(index))
        return memo[index];

    memo[index] =
        std::min(dp(index + 1, n, h, memo) + std::abs(h[index + 1] - h[index]),
                 dp(index + 2, n, h, memo) + std::abs(h[index + 2] - h[index]));
    return memo[index];
}

void solve() {

    int64_t n = 0UL;
    std::cin >> n;
    std::vector<int64_t> h(n + 3, 0);
    for (int64_t i = 0; i < n; ++i) {
        std::cin >> h[i];
    }
    std::unordered_map<int64_t, int64_t> memo;
    std::cout << dp(0, n, h, memo) << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}