#include <bits/stdc++.h>

int64_t recurse(int32_t i, int32_t row, std::vector<int64_t> &h0,
                std::vector<int64_t> &h1,
                std::vector<std::array<int64_t, 3>> &cache) {
    if (i >= h1.size()) return 0;
    if (cache[i][row] != -1) return cache[i][row];

    int64_t path_1 = 0, path_2 = 0;
    if (row == 0) {
        path_1 = recurse(i + 1, 1, h0, h1, cache) + h0[i];
        path_2 = recurse(i + 1, 2, h0, h1, cache);
    } else if (row == 1) {
        path_1 = recurse(i + 1, 0, h0, h1, cache) + h1[i];
        path_2 = recurse(i + 1, 2, h0, h1, cache);
    } else {
        path_1 = recurse(i + 1, 1, h0, h1, cache) + h0[i];
        path_2 = recurse(i + 1, 0, h0, h1, cache) + h1[i];
    }

    return cache[i][row] = std::max(path_1, path_2);
}

void solve() {
    int32_t n = 0;
    std::cin >> n;

    std::vector<int64_t> h1(n, 0), h2(n, 0);
    for (int32_t i = 0; i < n; ++i) std::cin >> h1[i];
    for (int32_t i = 0; i < n; ++i) std::cin >> h2[i];

    std::vector<std::array<int64_t, 3>> cache(n + 1, {0, 0});
    for (auto &ci : cache) {
        ci[0] = -1;
        ci[1] = -1;
        ci[2] = -1;
    }
    int64_t answer_1 = recurse(0, 0, h1, h2, cache);

    for (auto &ci : cache) {
        ci[0] = -1;
        ci[1] = -1;
        ci[2] = -1;
    }
    int64_t answer_2 = recurse(0, 1, h1, h2, cache);

    for (auto &ci : cache) {
        ci[0] = -1;
        ci[1] = -1;
        ci[2] = -1;
    }
    int64_t answer_3 = recurse(0, 2, h1, h2, cache);

    std::cout << std::max({answer_1, answer_2, answer_3}) << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int32_t t = 1;
    //std::cin >> t;

    while (t--) { solve(); }
}