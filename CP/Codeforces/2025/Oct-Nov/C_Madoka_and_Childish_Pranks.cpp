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

void solve() {
    int64_t n = 0LL, m = 0LL;
    std::cin >> n >> m;

    std::vector<std::vector<char>> grid(n, std::vector<char>(m, 0));
    for (int64_t i = 0; i < n; ++i) {
        std::string si = "";
        std::cin >> si;
        for (int64_t j = 0; j < m; ++j) {
            grid[i][j] = si[j];
        }
    }

    std::vector<std::tuple<int64_t, int64_t, int64_t, int64_t>> moves;
    if (grid[0][0] == '1') {
        std::cout << -1 << std::endl;
        return;
    }

    for (int64_t j = m - 1; j >= 0; --j) {
        for (int64_t i = n - 1; i >= 0; --i) {
            if (grid[i][j] == '1') {
                if (i != 0) {
                    moves.emplace_back(i, j + 1, i + 1, j + 1);
                } else {
                    moves.emplace_back(i + 1, j, i + 1, j + 1);
                }
            }
        }
    }
    std::cout << moves.size() << std::endl;
    for (const auto& [ulc1, ulc2, llc1, llc2] : moves) {
        std::cout << ulc1 << " " << ulc2 << " " << llc1 << " " << llc2
                  << std::endl;
    }
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

/*
  12345
1 01000
2 10100
3 01000
4 00110

*/