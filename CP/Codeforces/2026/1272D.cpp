#include <bits/stdc++.h>


void solve() {
    int32_t n = 0;
    std::cin >> n;

    std::vector<int64_t> a(n, 0);
    for (int32_t i = 0; i < n; ++i) std::cin >> a[i];

    std::vector<std::array<int32_t, 2>> cache(n + 1, std::array<int32_t, 2>());

    cache[0][0] = 1;
    cache[0][1] = 0;

    int32_t answer = 0;

    for (int32_t i = 1; i < n; ++i) {
        cache[i][0] = 1;
        cache[i][1] = 1;

        if (a[i - 1] < a[i]) {
            cache[i][0] = std::max(cache[i][0], cache[i - 1][0] + 1);
            cache[i][1] = std::max(cache[i][1], cache[i - 1][1] + 1);
        }

        if (i - 2 >= 0 && a[i - 2] < a[i]) {
            cache[i][1] = std::max(cache[i][1], cache[i - 2][0] + 1);
        }

        answer = std::max({answer, cache[i][0], cache[i][1]});
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