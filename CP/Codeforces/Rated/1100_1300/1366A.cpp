// https://codeforces.com/problemset/problem/1366/A

#include <cstddef>
#include <cstdint>
#include <iostream>

bool check(int64_t x, int64_t& a, int64_t& b) {
    int64_t min_shovels =
        std::max(static_cast<int64_t>(0), static_cast<int64_t>(2 * x - b));
    int64_t max_shovels = std::min(x, a - x);
    if (min_shovels <= max_shovels) {
        return true;
    } else {
        return false;
    }
}

void solve() {

    int64_t a = 0UL, b = 0UL;
    std::cin >> a >> b;

    int64_t low = 0L, high = (a + b) / 3;
    int64_t max_tools = 0L;
    while (low <= high) {
        int64_t mid = low + (high - low) / 2;
        if (check(mid, a, b)) {
            max_tools = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    std::cout << max_tools << std::endl;
    return;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int64_t t = 0UL;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}