#include <bits/stdc++.h>

void solve() {
    int32_t n = 0;
    std::cin >> n;

    std::unordered_set<int32_t> y0, y1;
    for (int32_t i = 0; i < n; ++i) {
        int32_t xi = 0, yi = 0;
        std::cin >> xi >> yi;
        if (yi == 0)
            y0.emplace(xi);
        else
            y1.emplace(xi);
    }

    int64_t answer = 0;
    for (const auto &xi : y0) {
        if (y1.count(xi)) answer += (n - 2);
        if (y1.count(xi - 1) && y1.count(xi + 1)) answer++;
    }
    for (const auto &xi : y1) {
        if (y0.count(xi - 1) && y0.count(xi + 1)) answer++;
    }

    std::cout << answer << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int32_t t = 1;
    std::cin >> t;

    while (t--) { solve(); }
}