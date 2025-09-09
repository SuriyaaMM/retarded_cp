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

/*
1 -> 3 coins
3 -> 10 coins
9 -> 33 coins

10 watermelons, 
9 + 1 -> 33 + 3 coins
1 + 1 + 3 + 3
*/
void solve(std::vector<pair_t>& pre_calculation) {
    int64_t n = 0L;
    std::cin >> n;

    int64_t cost = 0L, low = 0L, high = pre_calculation.size() - 1;
    while (n > 0) {
        low = 0L;
        high = pre_calculation.size() - 1;

        int64_t this_cost = 0L, this_val = 0L;
        while (low <= high) {
            int64_t mid = (low + high) / 2;
            if (pre_calculation[mid].second <= n) {
                this_cost = pre_calculation[mid].first;
                this_val = pre_calculation[mid].second;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        if (this_val == 0) {
            break;
        }

        cost += this_cost;
        n -= this_val;
    }

    std::cout << cost << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

#define MT
#ifdef MT
    int64_t tt = 0L;
    std::cin >> tt;

    std::vector<pair_t> pre_calculate;
    pre_calculate.emplace_back(3, 1);
    for (int64_t i = 1; i < 20; ++i) {
        pre_calculate.emplace_back(
            ((int64_t)std::pow(3, i + 1)) + i * (int64_t)(std::pow(3, i - 1)),
            (int64_t)(std::pow(3, i)));
    }

    std::sort(
        pre_calculate.begin(), pre_calculate.end(),
        [](const pair_t& a, const pair_t& b) { return a.second < b.second; });

    while (tt--) {
        solve(pre_calculate);
    }
#else
    solve();
#endif

    return 0;
}