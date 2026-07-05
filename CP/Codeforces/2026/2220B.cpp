#include <bits/stdc++.h>

void solve() {
    std::int32_t n = 0, m = 0;
    std::cin >> n >> m;

    std::vector<std::int32_t> a(n, 0);
    for (auto &ai : a) std::cin >> ai;

    std::int32_t l = 0;
    for (std::int32_t r = 0; r < n; ++r) {
        if (a[r] != a[l]) {
            std::int32_t wlen = r - l;
            l = r;
            if (wlen >= m) {
                std::cout << "NO\n";
                return;
            }
        } else {
            continue;
        }
    }
    std::int32_t wlen = n - l;
    if (wlen >= m) {
        std::cout << "NO\n";
        return;
    }
    std::cout << "YES\n";
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::int32_t t = 1;
    std::cin >> t;

    while (t--) { solve(); }
}