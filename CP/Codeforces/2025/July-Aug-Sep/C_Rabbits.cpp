#include <algorithm>
#include <cmath>
#include <cstdint>
#include <format>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// reads the vector
#define read_vec(begin, end, vec) \
    for (int64_t i = begin; i < end; ++i) std::cin >> vec[i];

// reads the vector pair
#define read_vecp(begin, end, vec)        \
    for (int64_t i = begin; i < end; ++i) \
        std::cin >> vec[i].first >> vec[i].second;

// prints the vector
#define print_vec(begin, end, vec) \
    for (int64_t i = begin; i < end; ++i) std::cout << vec[i] << " ";

// infinity
constexpr const int64_t inf = std::numeric_limits<int64_t>::max();
// negative infinity
constexpr const int64_t ninf = std::numeric_limits<int64_t>::min();

// pair
using pair_t = std::pair<int64_t, int64_t>;
// generic pair
template <typename T1, typename T2>
using gpair_t = std::pair<T1, T2>;
// unweighted graph
using graph_t = std::vector<std::vector<int64_t>>;
// weighted graph
using wgraph_t = std::vector<std::vector<pair_t>>;

// disjoint set union by  & path compression
struct dsur_t {
    std::vector<int64_t> parent, rank;

    dsur_t(int64_t n) {
        // O(n)
        parent.resize(n + 1);
        // O(n)
        rank.resize(n + 1, 0);

        for (int64_t i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }
    // O(1)
    int64_t find_parent(int64_t x) {
        if (parent[x] != x) parent[x] = find_parent(parent[x]);
        return parent[x];
    }

    void unite(int64_t u, int64_t v) {
        u = find_parent(u);
        v = find_parent(v);

        if (v == u) return;

        if (rank[u] < rank[v]) std::swap(u, v);

        parent[v] = u;
        if (rank[u] == rank[v]) ++rank[u];
    }
};

struct dsur_parity_t {
    std::vector<int64_t> parent, rank, parity;

    dsur_parity_t(int64_t nn) {
        int64_t n = nn;
        parent.resize(n);
        rank.resize(n, 0);
        parity.resize(n, 0);
        for (int64_t k = 0; k < n; k++) parent[k] = k;
    }

    std::pair<int64_t, int64_t> find(int64_t x) {
        if (parent[x] != x) {
            auto [p, pr] = find(parent[x]);
            parity[x] ^= pr;
            parent[x] = p;
        }
        return {parent[x], parity[x]};
    }

    bool unite(int64_t x, int64_t y, int64_t xorv) {
        auto [px, rx] = find(x);
        auto [py, ry] = find(y);
        if (px == py) {
            return (rx ^ ry) == xorv;
        }
        if (rank[px] < rank[py]) {
            std::swap(px, py);
            std::swap(rx, ry);
        }
        parent[py] = px;
        parity[py] = rx ^ ry ^ xorv;
        if (rank[px] == rank[py]) ++rank[px];
        return true;
    }
};

void solve() {
    int64_t n = 0LL;
    std::cin >> n;

    std::string s = "";
    std::cin >> s;

    std::vector<int64_t> seg_lengths;
    std::vector<int64_t> sep;

    int64_t i = 0LL, prev_end = -1LL, leading = 0LL, trailing = 0LL;

    bool first = true;
    while (i < n) {
        if (s[i] == '1') {
            i++;
            continue;
        }
        int64_t start = i;
        while (i < n && s[i] == '0') i++;
        int64_t len = i - start;
        seg_lengths.push_back(len);
        if (first) {
            leading = start;
            first = false;
        } else {
            int64_t ones = start - (prev_end + 1);
            sep.push_back(ones);
        }
        prev_end = i - 1;
    }
    if (!seg_lengths.empty()) {
        trailing = n - 1 - prev_end;
    }
    int64_t num_seg = seg_lengths.size();
    if (num_seg == 0) {
        std::cout << "YES" << std::endl;
        return;
    }
    bool possible = true;
    int64_t nodes = 2 * num_seg + 2;
    dsur_parity_t dsu(nodes);
    int64_t TRUE_ID = nodes - 2;
    int64_t FALSE_ID = nodes - 1;
    if (!dsu.unite(TRUE_ID, FALSE_ID, 1)) possible = false;
    for (int64_t j = 0; j < num_seg; j++) {
        int64_t ll = 2 * j;
        int64_t rr = 2 * j + 1;
        if (seg_lengths[j] == 1) {
            if (!dsu.unite(ll, rr, 1)) possible = false;
        }
    }
    if (leading >= 1) {
        if (!dsu.unite(0, FALSE_ID, 0)) possible = false;
    }
    if (trailing >= 1) {
        if (!dsu.unite(2 * (num_seg - 1) + 1, FALSE_ID, 0)) possible = false;
    }
    for (int64_t j = 0; j < num_seg - 1; j++) {
        int64_t m = sep[j];
        int64_t rr_prev = 2 * j + 1;
        int64_t ll_next = 2 * (j + 1);
        if (m == 1) {
            if (!dsu.unite(rr_prev, ll_next, 0)) possible = false;
        } else {
            if (!dsu.unite(rr_prev, FALSE_ID, 0)) possible = false;
            if (!dsu.unite(ll_next, FALSE_ID, 0)) possible = false;
        }
    }
    std::cout << (possible ? "YES" : "NO") << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#define MT
#ifdef MT
    int64_t tt = 0L;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
#else
    solve();
#endif

    return 0;
}