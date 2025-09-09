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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>

struct pair_hash {
    int64_t operator()(const pair_t& p) const {
        return std::hash<int64_t>()(p.first) ^
               (std::hash<int64_t>()(p.second) << 1);
    }
};

using namespace __gnu_pbds;
using fset = gp_hash_table<pair_t, null_type, pair_hash>;

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
    int64_t n = 0LL, m = 0LL, u = 0LL, v = 0LL, k = 0LL, u_component = 0LL,
            v_component = 0LL, q = 0LL;
    std::cin >> n >> m;

    dsur_t dsu(n);
    // connect all base edges
    for (int64_t i = 0; i < m; ++i) {
        std::cin >> u >> v;
        dsu.unite(u, v);
    }

    // forbidden components
    std::cin >> k;
    fset forbidden_pairs;
    for (int64_t i = 0; i < k; ++i) {
        std::cin >> u >> v;
        u_component = dsu.find_parent(u);
        v_component = dsu.find_parent(v);

        if (u_component == v_component)
            continue;
        if (u_component > v_component)
            std::swap(u_component, v_component);

        forbidden_pairs.insert(std::make_pair(u_component, v_component));
    }

    // answer queries
    std::cin >> q;
    for (int64_t i = 0; i < q; ++i) {
        std::cin >> u >> v;
        u_component = dsu.find_parent(u);
        v_component = dsu.find_parent(v);

        if (v_component == u_component) {
            std::cout << "Yes\n";
            continue;
        }
        if (u_component > v_component)
            std::swap(u_component, v_component);
        if (forbidden_pairs.find(std::make_pair(u_component, v_component)) !=
            forbidden_pairs.end())
            std::cout << "No\n";
        else
            std::cout << "Yes\n";
    }
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}