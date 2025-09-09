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
// generic graph
template <typename T>
using ggraph_t = std::vector<std::vector<T>>;

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

/*
so 
(1, 2), (1, 3)
(2, 2),
(3, 4)

so basically bipartiteness, if we can colour the nodes of two different colours
then we are good to go.
we want to count how many of these nodes are bipartite
so answer is always going to be a multiple of 2
number of pairs = number of bipartite nodes
*/

bool count_bipartite_nodes(int64_t current_node, int64_t parent_colour,
                           graph_t& graph, std::vector<int64_t>& colour,
                           int64_t& num_bipartites) {

    // this means this node is bipartite
    colour[current_node] = parent_colour;
    ++num_bipartites;

    for (const auto& neighbour : graph[current_node]) {
        // if this node isn't already coloured
        // but wait am should i continue in this path if i am already coloured?
        // no right, we will continue this path iff our parent node and this node is bipartite
        // else we are never going to take this path
        if (colour[neighbour] == inf) {
            if (!count_bipartite_nodes(neighbour, colour[current_node], graph,
                                       colour, num_bipartites)) {
                return false;
            }
        } else {
            if (colour[neighbour] == colour[current_node]) {
                return false;
            }
        }
    }

    return true;
}

void solve() {
    int64_t a = 0L, b = 0L, k = 0L;
    std::cin >> a >> b >> k;

    std::vector<int64_t> as(k, 0), bs(k, 0);
    read_vec(0, k, as);
    read_vec(0, k, bs);

    graph_t graph(a + b);

    for (int64_t i = 0; i < k; ++i) {
        --as[i];
        --bs[i];
        graph[as[i]].emplace_back(bs[i]);
        graph[bs[i]].emplace_back(as[i]);
    }

    std::vector<int64_t> colour(a + b, inf);
    int64_t num_bipartite_nodes = 0;
    for (int64_t i = 0; i < (a + b); ++i) {
        if (colour[i] == inf) {
            count_bipartite_nodes(i, 0, graph, colour, num_bipartite_nodes);
        }
    }

    std::cout << num_bipartite_nodes << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int64_t tt = 0L;
    std::cin >> tt;
    while (tt--) {
        solve();
    }

    return 0;
}