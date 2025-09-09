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

bool dfs(const std::string& s, int& pos) {
    // post order traversal
    if (pos >= s.size()) {
        return true;
    }

    bool left = dfs(s, pos);
    bool right = dfs(s, pos);

    bool ok = (s[pos] == '1') && left && right;
    ++pos;
    return ok;
}

void solve() {
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;

    // dp[mask] is true if the state `mask` is safely reachable.
    std::vector<bool> dp(1 << n, false);

    // Base case: The empty bottle (state 0) is always reachable.
    dp[0] = true;

    // Iterate through all possible non-empty states.
    for (int mask = 1; mask < (1 << n); ++mask) {
        // If the current state is dangerous, we can't form it.
        // S is 0-indexed for states 1 to 2^N-1.
        if (s[mask - 1] == '1') {
            continue;
        }

        // Check if this state is reachable from a smaller safe state.
        for (int i = 0; i < n; ++i) {
            // Check if chemical `i` is part of the current mixture `mask`.
            if ((mask >> i) & 1) {
                // `prev_mask` is the state before adding chemical `i`.
                int prev_mask = mask ^ (1 << i);

                // If the previous state was reachable, then this one is too.
                if (dp[prev_mask]) {
                    dp[mask] = true;
                    // We found one valid path, no need to check others for this mask.
                    break;
                }
            }
        }
    }

    // The final answer is whether the state with all chemicals is reachable.
    std::cout << (dp[(1 << n) - 1] ? "Yes" : "No") << '\n';
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