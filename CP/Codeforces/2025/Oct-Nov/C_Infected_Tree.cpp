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

// disjoint set union by rank & path compression
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
    // O(alpha(n))
    int64_t find_parent(int64_t x) {
        if (parent[x] != x) parent[x] = find_parent(parent[x]);
        return parent[x];
    }
    // O(alpha(n))
    void unite(int64_t u, int64_t v) {
        u = find_parent(u);
        v = find_parent(v);

        if (v == u) return;

        if (rank[u] < rank[v]) std::swap(u, v);

        parent[v] = u;
        if (rank[u] == rank[v]) ++rank[u];
    }
};

void count_children(int64_t c, int64_t p, graph_t& btree,
                    std::vector<int64_t>& counts) {
    for (const auto& nbr : btree[c]) {
        if (nbr == p) continue;
        count_children(nbr, c, btree, counts);
        counts[c] += counts[nbr];
    }

    counts[c]++;
    return;
}

void solve() {
    int64_t n = 0LL;
    std::cin >> n;

    graph_t btree(n);
    for (int64_t i = 0; i < n - 1; ++i) {
        int64_t ui = 0LL, vi = 0LL;
        std::cin >> ui >> vi;
        ui--;
        vi--;
        btree[vi].emplace_back(ui);
        btree[ui].emplace_back(vi);
    }

    std::vector<int64_t> cc(n + 1, 0);
    count_children(0, -1, btree, cc);

    std::vector<int64_t> dp(n + 1, 0);

    std::deque<int64_t> q;
    q.emplace_back(0);

    std::vector<int64_t> vis(n, false);

    while (!q.empty()) {
        auto u = q.front();
        q.pop_front();

        int64_t c = dp[u];

        for (const auto& v : btree[u]) {
            if (!vis[v]) {
                vis[v] = true;
                c = std::max(c, dp[u] + cc[v] - 1);
                q.emplace_back(v);
            }
        }

        dp[u + 1] = c;
    }

    std::cout << *std::max_element(dp.begin(), dp.end()) << std::endl;
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