#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <map>
#include <ostream>
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
    int n;
    std::cin >> n;

    if (n <= 2) {
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            std::cin >> u >> v;
        }
        std::cout << -1 << "\n";
        return;
    }

    std::vector<std::vector<int>> adj(n + 1);
    std::vector<int> degree(n + 1, 0);
    bool is_path = true;

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        degree[u]++;
        degree[v]++;
    }

    for (int i = 1; i <= n; ++i) {
        if (degree[i] > 2) {
            is_path = false;
            break;
        }
    }
    if (is_path) {
        std::cout << -1 << "\n";
        return;
    }

    for (int b = 1; b <= n; ++b) {
        if (degree[b] > 2) {
            for (int c : adj[b]) {
                if (degree[c] == 1) {
                    int a = -1;
                    for (int neighbor : adj[b]) {
                        if (neighbor != c) {
                            a = neighbor;
                            break;
                        }
                    }
                    std::cout << a << " " << b << " " << c << "\n";
                    return;
                }
            }
        }
    }

    int max_degree = 0;
    int b = -1;
    for (int i = 1; i <= n; ++i) {
        if (degree[i] > max_degree) {
            max_degree = degree[i];
            b = i;
        }
    }
    int a = adj[b][0];
    int c = adj[b][1];
    std::cout << a << " " << b << " " << c << "\n";
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