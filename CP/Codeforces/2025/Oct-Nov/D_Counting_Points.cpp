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

int64_t npic(int64_t ri) { return (ri * (2 * ri + 1) + 3); }

void solve() {
    int64_t n = 0LL, m = 0LL;
    std::cin >> n >> m;

    std::vector<int64_t> x(n, 0), r(n, 0);
    read_vec(0, n, x);
    read_vec(0, n, r);

    std::map<int64_t, std::priority_queue<int64_t>> mm;
    for (int64_t i = 0; i < n; ++i) {
        mm[x[i]].emplace(r[i]);
    }

    int64_t tt = 0LL, nn = 0LL;
    for (auto it = mm.begin(); it != mm.end(); ++it) {
        tt -= nn;
        nn = 0LL;
        auto in = std::next(it);
        const auto& [xi, pqi] = *it;
        const auto ri = pqi.top();
        if (in != mm.end()) {
            const auto& [xii, pqii] = *in;
            const auto rii = pqii.top();

            int64_t di = xi + ri, dii = xii - rii;

            if (dii > di) {
                nn = 0LL;
            } else if (dii == di) {
                nn = 1LL;
            } else {
                if (dii == xi) {
                    nn = npic(ri) / 2;
                } else if (dii < xi) {
                    nn = (dii - di - 1) * (2 * ri - 1) + 1LL;
                } else {
                    nn = (npic(ri) / 2) + (dii - xi - 1) * (2 * ri - 1);
                }
            }
        }
        tt += npic(ri);
    }

    std::cout << tt << "\n";
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