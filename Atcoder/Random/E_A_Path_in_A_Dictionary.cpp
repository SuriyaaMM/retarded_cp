#include <algorithm>
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <stack>
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

void dfs(int64_t u, int64_t y, bool& found, std::vector<int64_t>& path,
         std::vector<bool>& visited, graph_t& adj) {
    if (found) {
        return;
    }

    path.push_back(u);
    visited[u] = true;

    if (u == y) {
        found = true;
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i] << (i == path.size() - 1 ? "" : " ");
        }
        std::cout << "\n";
        return;
    }

    for (int64_t v : adj[u]) {
        if (!visited[v]) {
            dfs(v, y, found, path, visited, adj);
            if (found) {
                return;
            }
        }
    }

    path.pop_back();
    visited[u] = false;
}

void solve() {
    using path_t = std::vector<int64_t>;

    int64_t n, m, x, y;
    std::cin >> n >> m >> x >> y;

    graph_t adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int64_t u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int64_t i = 1; i <= n; ++i) {
        std::sort(adj[i].begin(), adj[i].end());
    }

    std::priority_queue<path_t, std::vector<path_t>, std::greater<path_t>> pq;
    pq.push({x});

    while (!pq.empty()) {
        path_t p = pq.top();
        pq.pop();
        int64_t u = p.back();

        if (u == y) {
            for (size_t i = 0; i < p.size(); ++i) {
                std::cout << p[i] << (i == p.size() - 1 ? "\n" : " ");
            }
            return;
        }

        for (int64_t v : adj[u]) {
            if (std::find(p.begin(), p.end(), v) == p.end()) {
                path_t new_p = p;
                new_p.push_back(v);
                pq.push(new_p);
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}