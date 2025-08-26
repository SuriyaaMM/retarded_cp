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
we are given a number n, we want to count the number of ways that we can get the sum
n using numbers in the range [1, 6]
say n = 2
2 & 1 + 1 will be the answer
say n = 3
3 & 2 + 1 & 1 + 1 will be the answer 
say n = 4
4 & 2 + 2 & 1 + 1 + 1 + 1 & 3 + 1 & 4 + 1 will be the answer
            2
        2       1
                1
    -----------------
            3
    3   2       1
        1   2       1
                    1
*/

int64_t count_number_of_ways(int64_t n,
                             std::unordered_map<int64_t, int64_t>& memo) {
    if (n < 0)
        return 0;
    if (n == 0)
        return 1;

    if (memo.count(n))
        return memo[n];

    int64_t number_of_ways = 0L;
    for (int64_t i = 1; i <= 6; ++i) {
        number_of_ways += count_number_of_ways(n - i, memo);
    }

    return memo[n] = number_of_ways;
}

void solve() {

    const int64_t MOD = 1e9 + 7;
    int64_t n = 0L;
    std::cin >> n;
    //std::unordered_map<int64_t, int64_t> memo;
    //std::cout << count_number_of_ways(n, memo) << std::endl;

    std::vector<int64_t> dp(n + 1, 0);
    dp[0] = 1;
    for (int64_t i = 1; i <= n; ++i) {
        for (int64_t j = 1; j <= 6; ++j) {
            if (i - j >= 0)
                dp[i] = (dp[i] + dp[i - j]) % MOD;
        }
    }

    std::cout << dp[n] << std::endl;
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