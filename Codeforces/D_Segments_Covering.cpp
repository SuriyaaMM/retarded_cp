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

// mod exp
int64_t power(int64_t base, int64_t exp) {
    int64_t res = 1;
    int64_t MOD = 998244353;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1)
            res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

// mod inv
int64_t mod_inverse(int64_t n) {
    int64_t MOD = 998244353;
    return power(n, MOD - 2);
}

void solve() {
    int64_t n, m;
    std::cin >> n >> m;

    int64_t MOD = 998244353;

    std::vector<std::vector<gpair_t<int64_t, int64_t>>> ends_at(m + 1);
    int64_t total_u_prod = 1;

    for (int64_t i = 0; i < n; ++i) {
        int64_t l, r, p, q;
        std::cin >> l >> r >> p >> q;

        int64_t inv_q = mod_inverse(q);
        int64_t prob = (p * inv_q) % MOD;

        // 1-p
        int64_t u = (1 - prob + MOD) % MOD;

        // p/(1-p)
        int64_t inv_u = mod_inverse(u);
        int64_t v = (prob * inv_u) % MOD;

        ends_at[r].push_back({l, v});
        total_u_prod = (total_u_prod * u) % MOD;
    }

    std::vector<int64_t> dp(m + 1, 0);
    dp[0] = 1;

    for (int64_t i = 1; i <= m; ++i) {
        int64_t current_dp = 0;
        for (const auto& seg : ends_at[i]) {
            int64_t l = seg.first;
            int64_t v = seg.second;
            current_dp = (current_dp + (dp[l - 1] * v)) % MOD;
        }
        dp[i] = current_dp;
    }

    int64_t final_prob = (dp[m] * total_u_prod) % MOD;
    std::cout << final_prob << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}