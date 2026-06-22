#include <bits/stdc++.h>

struct fenwick_t {
    std::vector<int32_t> tree;
    int32_t n;

    fenwick_t(int32_t n) : n(n), tree(n + 1, 0) {}

    void update(int32_t i, int32_t v) {
        for (; i <= n; i += (i & (-i))) tree[i] += v;
    }

    int64_t query(int32_t i) {
        int64_t sum = 0;
        for (; i > 0; i -= (i & (-i))) sum += tree[i];
        return sum;
    }
};

void solve() {
    int32_t n = 0;
    std::cin >> n;

    std::vector<std::pair<int64_t, int64_t>> pairs(n, {0, 0});
    for (int32_t i = 0; i < n; ++i)
        std::cin >> pairs[i].first >> pairs[i].second;

    std::sort(pairs.begin(), pairs.end());

    std::vector<int64_t> b(n, 0);
    for (int32_t i = 0; i < n; ++i) b[i] = pairs[i].second;

    std::sort(b.begin(), b.end());
    const auto rank = [&b](int64_t v) {
        return std::lower_bound(b.begin(), b.end(), v) - b.begin() + 1;
    };

    fenwick_t ft(n);
    int64_t answer = 0;
    for (int32_t i = n - 1; i >= 0; --i) {
        const auto &[ai, bi] = pairs[i];
        const auto rank_bi = rank(bi);
        answer += ft.query(rank_bi);
        ft.update(rank_bi, 1);
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