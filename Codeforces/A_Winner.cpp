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

/*
<name> points
whomever reached the points first will be the winner in case of the tie
mike -> (3, t = 0)
andwer -> (3, t = 0)
mike -> (3, t = 1)
mike & andrew -> same number of points, andrew time = 0, mike time = 1, 
andrew is the winner
*/
void solve() {
    int64_t n = 0L;
    std::cin >> n;

    std::vector<std::pair<std::string, int64_t>> rounds(n, {"", 0});

    for (int64_t i = 0; i < n; ++i) {
        std::cin >> rounds[i].first >> rounds[i].second;
    }

    std::unordered_map<std::string, int64_t> final_scores;
    for (const auto& [name, score] : rounds) {
        final_scores[name] += score;
    }

    int64_t max_score = 0L;
    for (const auto& [_, final_score] : final_scores) {
        max_score = std::max(final_score, max_score);
    }

    std::unordered_map<std::string, int64_t> running;
    for (const auto& [name, score] : rounds) {
        running[name] += score;
        if (running[name] >= max_score && final_scores[name] == max_score) {
            std::cout << name << std::endl;
            return;
        }
    }
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