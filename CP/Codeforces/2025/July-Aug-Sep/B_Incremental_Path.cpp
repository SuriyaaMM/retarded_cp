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
    int64_t n, m;
    std::cin >> n >> m;
    std::string s;
    std::cin >> s;
    std::vector<int64_t> initial_black(m);
    for (int64_t i = 0; i < m; ++i) {
        std::cin >> initial_black[i];
    }

    // Set to store black cells (sorted, unique)
    std::set<int64_t> black_cells(initial_black.begin(), initial_black.end());

    // Simulate each prefix of commands
    int64_t current = 1;                     // Start at cell 1
    const int64_t max_cell = 1'000'000'000;  // 10^9

    for (int64_t i = 0; i < n; ++i) {
        // Execute the i-th command
        if (current > max_cell) {
            // If beyond strip, no further valid moves
            continue;
        }
        if (s[i] == 'A') {
            current++;  // Move to next cell
        } else {        // 'B'
            // Find next white cell (first cell > current that is not black)
            auto it = black_cells.upper_bound(current);
            if (it == black_cells.end() || *it > max_cell) {
                current = max_cell + 1;  // No white cell available
            } else {
                current = *it + 1;  // Next cell after the black cell
            }
        }
        // Color the current cell black if within bounds
        if (current <= max_cell) {
            black_cells.insert(current);
        }
    }

    // Output results
    std::cout << black_cells.size() << '\n';
    for (auto cell : black_cells) {
        std::cout << cell << ' ';
    }
    std::cout << '\n';
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