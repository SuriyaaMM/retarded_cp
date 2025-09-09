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
we are given a set of coin values and we want to produce sum of m using minimum number of coins

take the example 
11, from {1, 5, 7}

if we choose a greedy approach 
we will choose 7 + 1 + 1 + 1 + 1 -> 5 coins which is not the minimal, in this case the minmal
is 5 + 5 + 1
so we need to do exhaustive search using. but then that will be searching all the subsets 
which is 2^{max_elems_in_subset} which is not at all good.

            11
        7       5       1
        1   5       1
        1   1       
        1       5       1
        1

*/

int64_t min_number_of_coins(int64_t n, std::vector<int64_t>& coin_values,
                            std::vector<int64_t>& memo) {
    if (n < 0)
        return inf / 2;
    if (n == 0)
        return 0;

    if (memo[n] != ninf)
        return memo[n];

    int64_t min_number_of_ways = inf / 2;
    for (int64_t i = 0; i < (int64_t)coin_values.size(); ++i) {
        min_number_of_ways = std::min(
            min_number_of_ways,
            min_number_of_coins(n - coin_values[i], coin_values, memo) + 1);
    }
    return memo[n] = min_number_of_ways;
}

void solve() {
    int64_t n = 0L, m = 0L;
    std::cin >> n >> m;

    std::vector<int64_t> coin_values(n, 0);
    read_vec(0, n, coin_values);
    // top down dp
    // std::vector<int64_t> memo(1e7, ninf);
    // int64_t answer = min_number_of_coins(m, coin_values, memo);
    // if (answer == inf / 2) {
    //     std::cout << -1 << std::endl;
    //     return;
    // }
    // std::cout << answer << std::endl;

    // bottom up dp
    std::vector<int64_t> dp(m + 1, inf / 2);
    // min number of ways to have 0 coin value is always 0
    dp[0] = 0;
    // dp[i] = min number of ways to have i coin value

    for (int64_t value = 1; value <= m; ++value) {
        for (int64_t i = 0; i < n; ++i) {
            if (value - coin_values[i] >= 0)
                dp[value] = std::min(dp[value], dp[value - coin_values[i]] + 1);
        }
    }

    if (dp[m] == inf / 2) {
        std::cout << -1 << std::endl;
        return;
    }

    std::cout << dp[m] << std::endl;
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