#include <bits/stdc++.h>

void solve() {
    int32_t n = 0, q = 0;
    std::cin >> n >> q;

    std::vector<int32_t> a(n, 0);
    for (int32_t i = 0; i < n; ++i) std::cin >> a[i];

    int64_t cache_pick_add = 0, cache_pick_sub = 0;
    for (int32_t i = 1; i <= n; ++i) {
        int64_t answer_path_2 = cache_pick_add + a[i - 1];
        int64_t answer_path_3 = cache_pick_sub - a[i - 1];

        cache_pick_add = std::max(cache_pick_add, answer_path_3);
        cache_pick_sub = std::max(cache_pick_sub, answer_path_2);
    }

    int64_t answer = std::max(cache_pick_add, cache_pick_sub);

    std::cout << answer << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int32_t t = 1;
    std::cin >> t;

    while (t--) { solve(); }
}