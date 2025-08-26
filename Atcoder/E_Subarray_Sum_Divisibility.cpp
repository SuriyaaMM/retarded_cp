#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// reads the vector
#define read_vec(begin, end, vec)         \
    for (int64_t i = begin; i < end; ++i) \
        std::cin >> vec[i];

// reads the vector pair
#define read_vecp(begin, end, vec)        \
    for (int64_t i = begin; i < end; ++i) \
        std::cin >> vec[i].first >> vec[i].second;

// prints the vector
#define print_vec(begin, end, vec)        \
    for (int64_t i = begin; i < end; ++i) \
        std::cout << vec[i] << " ";

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
        if (parent[x] != x)
            parent[x] = find_parent(parent[x]);
        return parent[x];
    }

    void unite(int64_t u, int64_t v) {
        u = find_parent(u);
        v = find_parent(v);

        if (v == u)
            return;

        if (rank[u] < rank[v])
            std::swap(u, v);

        parent[v] = u;
        if (rank[u] == rank[v])
            ++rank[u];
    }
};

void solve() {
    int64_t n = 0L, m = 0L, l = 0L;
    std::cin >> n >> m >> l;

    std::vector<int64_t> a(n, 0);
    read_vec(0, n, a);

    std::vector<std::vector<int64_t>> groups(l);
    for (int64_t i = 0; i < n; ++i) {
        groups[i % l].push_back(a[i]);
    }

    std::vector<std::vector<int64_t>> cost(l, std::vector<int64_t>(m));
    for (int i = 0; i < l; ++i) {
        for (int k = 0; k < m; ++k) {
            int64_t current_cost = 0;
            for (int64_t element : groups[i]) {
                current_cost += (k - element + m) % m;
            }
            cost[i][k] = current_cost;
        }
    }

    std::vector<std::vector<int64_t>> dp(l + 1, std::vector<int64_t>(m, inf));
    dp[0][0] = 0;

    for (int i = 1; i <= l; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < m; ++k) {
                int prev_sum = (j - k + m) % m;
                if (dp[i - 1][prev_sum] != inf) {
                    dp[i][j] = std::min(dp[i][j],
                                        dp[i - 1][prev_sum] + cost[i - 1][k]);
                }
            }
        }
    }

    std::cout << dp[l][0] << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

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