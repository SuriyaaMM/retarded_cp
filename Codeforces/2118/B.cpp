#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

void solve() {
    int n;
    std::cin >> n;

    std::cout << 2 * n - 1 << std::endl;

    for (int i = 1; i <= n; ++i) {
        std::cout << i << " " << 1 << " " << i << std::endl;
    }

    for (int i = 1; i <= n - 1; ++i) {
        std::cout << i << " " << i + 1 << " " << n << std::endl;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}