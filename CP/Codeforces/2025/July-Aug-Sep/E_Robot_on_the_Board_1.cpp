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

void solve() {
    int64_t n = 0LL, m = 0LL;
    std::cin >> n >> m;
    std::string s = "";
    std::cin >> s;

    int64_t us = 0LL, ds = 0LL, rs = 0LL, ls = 0LL;
    int64_t ub = 1LL, db = n, rb = 1LL, lb = m;
    int64_t final_r = 1, final_c = 1;

    for (const auto& si : s) {
        if (si == 'L') {
            if (rs == 0) {
                ++ls;
            } else {
                --rs;
            }
        } else if (si == 'R') {
            if (ls == 0) {
                ++rs;
            } else {
                --ls;
            }
        } else if (si == 'U') {
            if (ds == 0) {
                ++us;
            } else {
                --ds;
            }
        } else if (si == 'D') {
            if (us == 0) {
                ++ds;
            } else {
                --us;
            }
        }

        ub = 1 + us;
        db = n - ds;
        rb = 1 + ls;
        lb = m - rs;

        if (ub > db || rb > lb) {
            break;
        }

        final_r = ub;
        final_c = rb;
    }

    std::cout << final_r << " " << final_c << std::endl;
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