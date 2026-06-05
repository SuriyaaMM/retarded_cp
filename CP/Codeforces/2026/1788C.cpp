#include <bits/stdc++.h>

void solve() {
    int32_t n = 0;
    std::cin >> n;

    if (n % 2 == 0) {
        std::cout << "NO\n";
        return;
    }

    std::cout << "YES\n";
    int32_t pair_1 = 1, pair_2 = 2 * n;
    for (int32_t i = 0; i < n; ++i) {
        if (pair_1 > n) { pair_1 = 2; }
        std::cout << pair_1 << " " << pair_2 << "\n";
        pair_1 += 2;
        pair_2--;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int32_t t = 1;
    std::cin >> t;

    while (t--) { solve(); }
}