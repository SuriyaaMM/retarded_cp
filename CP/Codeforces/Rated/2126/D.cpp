#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <string>
#include <tuple>
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
    int64_t n = 0LL, k = 0LL;
    std::cin >> n >> k;

    using state_t = std::tuple<int64_t, int64_t, int64_t>;
    int64_t l = 0LL, r = 0LL, real = 0LL;
    std::vector<state_t> casinos(n, {0, 0, 0});

    for (int64_t i = 0; i < n; ++i) {
        std::cin >> l >> r >> real;
        casinos[i] = std::make_tuple(l, r, real);
    }

    std::ranges::sort(casinos);
    std::priority_queue<pair_t> available_casinos;

    int64_t current_coins = k;
    int64_t max_coins = k;
    int64_t casino_idx = 0;

    while (casino_idx < n || !available_casinos.empty()) {
        // playable to pq
        while (casino_idx < n &&
               std::get<0>(casinos[casino_idx]) <= current_coins) {
            auto& casino = casinos[casino_idx];
            available_casinos.push({std::get<2>(casino), std::get<1>(casino)});
            casino_idx++;
        }

        while (!available_casinos.empty() &&
               available_casinos.top().second < current_coins) {
            available_casinos.pop();
        }

        if (available_casinos.empty()) {
            break;
        } else {
            // greedy
            pair_t best_game = available_casinos.top();
            available_casinos.pop();

            current_coins = best_game.first;
            max_coins = std::max(max_coins, current_coins);
        }
    }

    std::cout << max_coins << std::endl;
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