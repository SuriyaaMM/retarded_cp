#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <map>
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
    int64_t n = 0;
    std::cin >> n;
    std::vector<int64_t> h(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> h[i];
    }

    if (n == 0) {
        std::cout << 0 << std::endl;
        return;
    }

    // dp[i][0] -> cost to kill 1..i, with i killed directly
    // dp[i][1] -> cost to kill 1..i, with i killed by fall damage
    std::vector<std::vector<int64_t>> dp(n, std::vector<int64_t>(2, 0));

    // Base Case for mob 0 (the first mob)
    dp[0][0] = h[0];
    dp[0][1] = inf;

    // Fill DP table for mobs 1 to n-1
    for (int64_t i = 1; i < n; ++i) {
        // Option 1: Kill mob i directly
        dp[i][0] = std::min(dp[i - 1][0], dp[i - 1][1]) + h[i];

        // Option 2: Kill mob i with fall damage from i-1
        // Note: Fall damage is (i-1)+1 = i because of 0-based indexing
        int64_t fall_damage = i;
        dp[i][1] = dp[i - 1][0] + std::max(0L, h[i] - fall_damage);
    }

    // The answer is the minimum cost to kill all n mobs (up to index n-1)
    std::cout << std::min(dp[n - 1][0], dp[n - 1][1]) << std::endl;
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