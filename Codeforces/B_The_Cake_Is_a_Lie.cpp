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
    /*
    so we have two options, we can move either right | down, moving right costs x burles
    moving down costs y burles.
    */

    int64_t n = 0L, m = 0L, k = 0L;
    std::cin >> n >> m >> k;

    // we will start at (0, 0)
    std::vector<std::vector<int64_t>> dp(n, std::vector<int64_t>(m, 0));
    // it costs k rubles to reach this cell
    dp[0][0] = 0;

    // if it is along the 0th row, we can reach it only from the right
    for (int64_t column = 1; column < m; ++column) {
        dp[0][column] = dp[0][column - 1] + 1;
    }
    // if it is along the 0th column, we can reach it only from the top
    for (int64_t row = 1; row < n; ++row) {
        dp[row][0] = dp[row - 1][0] + 1;
    }
    // else general calculation
    for (int64_t row = 1; row < n; ++row) {
        for (int64_t column = 1; column < m; ++column) {
            // we can reach this cell (row, column) from (row - 1, column) (top)
            dp[row][column] = std::min(dp[row - 1][column] + (column + 1),
                                       dp[row][column - 1] + (row + 1));
        }
    }

    if (dp[n - 1][m - 1] == k) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int64_t tt = 0LL;
    std::cin >> tt;

    while (tt--) {
        solve();
    }
    return 0;
}