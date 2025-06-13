// https://codeforces.com/problemset/problem/357/A

#include <cstddef>
#include <iostream>
#include <numeric>
#include <vector>

void solve() {

    size_t m = 0UL;
    std::cin >> m;

    std::vector<size_t> a(m);

    for (size_t i = 0; i < m; ++i) {
        std::cin >> a[i];
    }

    size_t total_sum = std::accumulate(a.begin(), a.end(), 0ULL);

    size_t x = 0UL, y = 0UL;
    std::cin >> x >> y;

    size_t running_sum = 0UL, complement_running_sum = 0UL;
    for (size_t i = 1; i < m + 1; ++i) {

        if (i > 1) {
            running_sum += a[i - 2];
        }

        complement_running_sum = total_sum - running_sum;

        if (running_sum >= x && running_sum <= y &&
            complement_running_sum >= x && complement_running_sum <= y) {
            std::cout << i << std::endl;
            return;
        }
    }

    std::cout << 0 << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}