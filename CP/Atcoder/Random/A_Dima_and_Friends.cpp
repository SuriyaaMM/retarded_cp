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

/*
if number of friends is odd, & sum of fingers shown by his friends are even
2
3 5

sum = 8, number of friends is even = 2
if dima shows one finger, 
8 + 1 = 9 % 3 = 0 we will end up in friend 2
8 + 2 = 10 % 3 = 1, we will end up in friend dima
8 + 3 = 11 % 3 = 2, we will end up in friend 1
8 + 4 = 12 % 3 = 0, we will end up in friend 2
8 + 5 = 13 % 3 = 1, we will end up in friend dima

dima -> f1 -> f2 -> dima -> f1 -> f2 -> dima -> f1 -> f2
*/
void solve() {
    int64_t n = 0L, ai = 0L;
    int64_t sum = 0L;
    std::cin >> n;

    for (int64_t i = 0; i < n; ++i) {
        std::cin >> ai;
        sum += ai;
    }

    int64_t num_ways = 0L;
    for (int64_t i = 1; i <= 5; ++i) {
        if ((sum + i) % (n + 1) != 1) {
            ++num_ways;
        }
    }
    std::cout << num_ways << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}