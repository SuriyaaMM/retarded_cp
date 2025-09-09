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

// disjoint set union by rank & path compression
struct dsur_t {
    std::vector<int64_t> parent, rank;

    dsur_t(int64_t n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int64_t i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }

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

int64_t N, K;
std::vector<int64_t> A;
graph_t adj;

// dp[v][k][open] where:
// v = vertex, k = paths used, open = whether subtree has an open path
// dp[v][k][0] = max sum with k paths, no open path from this subtree
// dp[v][k][1] = max sum with k paths, has open path from this subtree
int64_t dp[200005][6][2];

void dfs(int64_t v, int64_t parent) {
    // Initialize
    for (int64_t k = 0; k <= K; ++k) {
        dp[v][k][0] = dp[v][k][1] = ninf;
    }

    // Base case: no paths used
    dp[v][0][0] = 0;

    std::vector<int64_t> children;
    for (int64_t u : adj[v]) {
        if (u != parent) {
            children.push_back(u);
        }
    }

    // Process children
    for (int64_t child : children) {
        dfs(child, v);
    }

    // If no children, we can start a single path
    if (children.empty()) {
        for (int64_t k = 1; k <= K; ++k) {
            dp[v][k][1] = A[v];
        }
        return;
    }

    // Merge children results
    // new_dp will store the updated values after considering each child
    int64_t new_dp[6][2];

    for (int64_t child : children) {
        // Copy current dp to new_dp
        for (int64_t k = 0; k <= K; ++k) {
            new_dp[k][0] = dp[v][k][0];
            new_dp[k][1] = dp[v][k][1];
        }

        // Reset dp
        for (int64_t k = 0; k <= K; ++k) {
            dp[v][k][0] = dp[v][k][1] = ninf;
        }

        // Merge with child
        for (int64_t k1 = 0; k1 <= K; ++k1) {
            for (int64_t k2 = 0; k2 <= K - k1; ++k2) {
                int64_t total_k = k1 + k2;
                if (total_k > K)
                    continue;

                // Case 1: Both not open
                if (new_dp[k1][0] != ninf && dp[child][k2][0] != ninf) {
                    dp[v][total_k][0] = std::max(
                        dp[v][total_k][0], new_dp[k1][0] + dp[child][k2][0]);
                }

                // Case 2: Parent open, child not open
                if (new_dp[k1][1] != ninf && dp[child][k2][0] != ninf) {
                    dp[v][total_k][1] = std::max(
                        dp[v][total_k][1], new_dp[k1][1] + dp[child][k2][0]);
                }

                // Case 3: Parent not open, child open
                if (new_dp[k1][0] != ninf && dp[child][k2][1] != ninf) {
                    dp[v][total_k][1] = std::max(
                        dp[v][total_k][1], new_dp[k1][0] + dp[child][k2][1]);
                }

                // Case 4: Both open - connect them through current vertex
                if (new_dp[k1][1] != ninf && dp[child][k2][1] != ninf) {
                    dp[v][total_k][0] =
                        std::max(dp[v][total_k][0],
                                 new_dp[k1][1] + dp[child][k2][1] + A[v]);
                }
            }
        }
    }

    // Add transitions where we start a new path at current vertex
    for (int64_t k = K; k >= 1; --k) {
        if (dp[v][k - 1][0] != ninf) {
            dp[v][k][1] = std::max(dp[v][k][1], dp[v][k - 1][0] + A[v]);
        }
        if (dp[v][k - 1][1] != ninf) {
            dp[v][k][0] = std::max(dp[v][k][0], dp[v][k - 1][1] + A[v]);
        }
    }
}

void solve() {
    std::cin >> N >> K;

    A.resize(N + 1);
    adj.resize(N + 1);

    for (int64_t i = 1; i <= N; ++i) {
        std::cin >> A[i];
    }

    for (int64_t i = 0; i < N - 1; ++i) {
        int64_t u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, -1);

    int64_t ans = 0;
    for (int64_t k = 0; k <= K; ++k) {
        ans = std::max(ans, dp[1][k][0]);
    }

    std::cout << ans << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}