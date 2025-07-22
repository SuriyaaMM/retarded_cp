#include <algorithm>
#include <cmath>
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
    int64_t n = 0LL, q = 0LL;
    std::cin >> n >> q;

    std::vector<int64_t> colour(n);
    read_vec(0, n, colour);

    wgraph_t graph(n);
    std::vector<int64_t> degree(n, 0);
    std::vector<std::tuple<int64_t, int64_t, int64_t>> edges;
    for (int64_t i = 0; i < n - 1; ++i) {
        int64_t ui, vi, ci;
        std::cin >> ui >> vi >> ci;
        --ui;
        --vi;
        graph[ui].emplace_back(vi, ci);
        graph[vi].emplace_back(ui, ci);
        edges.emplace_back(ui, vi, ci);
        degree[ui]++;
        degree[vi]++;
    }

    // heavy-light optim
    const int64_t B = static_cast<int64_t>(std::sqrt(n));
    std::vector<bool> is_heavy(n, false);
    std::vector<int64_t> heavy_nodes;
    for (int64_t i = 0; i < n; ++i) {
        if (degree[i] > B) {
            is_heavy[i] = true;
            heavy_nodes.push_back(i);
        }
    }

    // heavy
    std::vector<std::unordered_map<int64_t, int64_t>> heavy_neighbor_sums(n);
    for (int64_t h : heavy_nodes) {
        for (auto& edge : graph[h]) {
            int64_t neighbor = edge.first;
            int64_t cost = edge.second;
            heavy_neighbor_sums[h][colour[neighbor]] += cost;
        }
    }

    int64_t total_sum = 0LL;
    for (const auto& edge : edges) {
        if (colour[std::get<0>(edge)] != colour[std::get<1>(edge)]) {
            total_sum += std::get<2>(edge);
        }
    }

    // queries
    for (int64_t i = 0; i < q; ++i) {
        int64_t v, x;
        std::cin >> v >> x;
        --v;

        int64_t old_c = colour[v];
        if (x == old_c) {
            std::cout << total_sum << std::endl;
            continue;
        }

        int64_t cost_change = 0LL;

        if (is_heavy[v]) {
            // heavy
            int64_t sum_for_old_c = heavy_neighbor_sums[v][old_c];
            int64_t sum_for_new_c = heavy_neighbor_sums[v][x];
            cost_change = sum_for_old_c - sum_for_new_c;
        } else {
            // light
            for (auto& edge : graph[v]) {
                int64_t neighbor = edge.first;
                int64_t edge_cost = edge.second;
                if (colour[neighbor] == old_c) {
                    cost_change += edge_cost;
                }
                if (colour[neighbor] == x) {
                    cost_change -= edge_cost;
                }
            }
        }

        total_sum += cost_change;

        for (auto& edge : graph[v]) {
            int64_t neighbor = edge.first;
            int64_t edge_cost = edge.second;
            // heavy update
            if (is_heavy[neighbor]) {
                heavy_neighbor_sums[neighbor][old_c] -= edge_cost;
                heavy_neighbor_sums[neighbor][x] += edge_cost;
            }
        }

        // colour change
        colour[v] = x;

        std::cout << total_sum << std::endl;
    }
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int64_t t = 0LL;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}