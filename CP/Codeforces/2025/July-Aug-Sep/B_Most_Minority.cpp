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
    int64_t n = 0L, m = 0L;
    std::cin >> n >> m;
    std::vector<std::vector<char>> votes(n, std::vector<char>(m, '0'));

    for (int64_t i = 0; i < n; ++i) {
        for (int64_t j = 0; j < m; ++j) {
            std::cin >> votes[i][j];
        }
    }

    std::vector<int64_t> voteboard(n, 0);
    int64_t x = 0L, y = 0L;
    for (int64_t i = 0; i < m; ++i) {
        x = 0L, y = 0L;
        for (int64_t j = 0; j < n; ++j) {
            if (votes[j][i] == '1')
                ++y;
            else
                ++x;
        }

        if (x == 0 || y == 0) {
            for (int64_t k = 0; k < n; ++k) {
                ++voteboard[k];
            }
        } else if (x < y) {
            for (int64_t k = 0; k < n; ++k) {
                if (votes[k][i] == '0') {
                    ++voteboard[k];
                }
            }
        } else if (x > y) {
            for (int64_t k = 0; k < n; ++k) {
                if (votes[k][i] == '1') {
                    ++voteboard[k];
                }
            }
        }
    }

    int64_t max_score = *std::max_element(voteboard.begin(), voteboard.end());
    for (int64_t i = 0; i < n; ++i) {
        if (voteboard[i] == max_score) {
            std::cout << i + 1 << " ";
        }
    }
    std::cout << std::endl;
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