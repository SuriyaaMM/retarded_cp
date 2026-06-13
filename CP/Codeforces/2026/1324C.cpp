#include <bits/stdc++.h>

void solve() {
    int32_t n = 0;
    std::cin >> n;

    std::vector<int64_t> a(n, 0), b(n, 0);
    for (int32_t i = 0; i < n; ++i) std::cin >> a[i];
    for (int32_t i = 0; i < n; ++i) std::cin >> b[i];

    std::vector<int64_t> c(n, 0);
    for (int32_t i = 0; i < n; ++i) c[i] = a[i] - b[i];

    std::sort(c.begin(), c.end());

    int64_t answer = 0;
    for (int32_t i = 0; i < n; ++i) {
        auto it = std::lower_bound(c.begin() + i + 1, c.end(), -c[i]);
        answer += std::distance(it, c.end());
    }

    std::cout << answer << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int32_t t = 1;
    //std::cin >> t;

    while (t--) { solve(); }
}