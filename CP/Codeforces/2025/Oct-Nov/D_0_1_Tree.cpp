#include <algorithm>
#include <cmath>
#include <cstdint>
#include <format>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// reads the vector
#define read_vec(begin, end, vec) \
    for (int64_t i = begin; i < end; ++i) std::cin >> vec[i];

// reads the vector pair
#define read_vecp(begin, end, vec)        \
    for (int64_t i = begin; i < end; ++i) \
        std::cin >> vec[i].first >> vec[i].second;

// prints the vector
#define print_vec(begin, end, vec)                                    \
    for (int64_t i = begin; i < end; ++i) std::cout << vec[i] << " "; \
    std::cout << "\n";

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

using xgraph_t = std::vector<std::vector<std::pair<int64_t, bool>>>;
using dp_t = std::vector<std::vector<int64_t>>;

void dfs_rooted(int64_t parent, int64_t current, dp_t& dp_rooted,
                xgraph_t& graph) {
    dp_rooted[current][0] = 0;
    dp_rooted[current][1] = 0;
    for (const auto& [child, edge_colour] : graph[current]) {
        // traverse down to child
        if (child == parent) continue;
        dfs_rooted(current, child, dp_rooted, graph);

        if (edge_colour == 1) {
            // we can only extent 1 and that too only using child's 1 paths
            dp_rooted[current][1] += dp_rooted[child][1] + 1;
        } else {
            // edge is an 0, we cannot increase the parent's 1 paths
            // however we can increase the parent's 0 paths
            dp_rooted[current][0] +=
                dp_rooted[child][0] + dp_rooted[child][1] + 1;
        }
    }
}

void dfs_reroot(int64_t parent, int64_t current, dp_t& dp, xgraph_t& graph,
                int64_t& total) {
    total += dp[current][0] + dp[current][1];

    for (const auto& [child, edge_colour] : graph[current]) {
        if (child == parent) continue;

        int64_t old_current_0 = dp[current][0], old_current_1 = dp[current][1];
        int64_t old_child_0 = dp[child][0], old_child_1 = dp[child][1];

        if (edge_colour == 1) {
            dp[current][1] -= dp[child][1] + 1;
            dp[child][1] += dp[current][1] + 1;
        } else {
            dp[current][0] -= dp[child][0] + dp[child][1] + 1;
            dp[child][0] += dp[current][0] + dp[current][1] + 1;
        }

        dfs_reroot(current, child, dp, graph, total);

        dp[current][0] = old_current_0;
        dp[current][1] = old_current_1;
        dp[child][0] = old_child_0;
        dp[child][1] = old_child_1;
    }
}

void solve() {
    int64_t n = 0LL;
    std::cin >> n;

    xgraph_t graph(n + 1);

    for (int64_t i = 0; i < n - 1; ++i) {
        int64_t ui = 0, vi = 0, wi = 0;
        std::cin >> ui >> vi >> wi;
        graph[ui].emplace_back(vi, wi);
        graph[vi].emplace_back(ui, wi);
    }

    dp_t dp_rooted(n + 1, std::vector<int64_t>(2, 0));

    int64_t total = 0;

    dfs_rooted(-1, 1, dp_rooted, graph);
    dfs_reroot(-1, 1, dp_rooted, graph, total);

    std::cout << total + n << "\n";
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#define MT
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