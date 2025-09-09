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

const int64_t MOD = 998244353;

int64_t mod_pow(int64_t base, int64_t exp, int64_t mod) {
    int64_t result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int64_t mod_inv(int64_t a, int64_t mod) {
    return mod_pow(a, mod - 2, mod);
}

void solve() {
    int64_t N, M;
    std::cin >> N >> M;

    std::vector<int64_t> A(N + 1);
    for (int64_t i = 1; i <= N; ++i) {
        std::cin >> A[i];
    }

    std::vector<pair_t> operations(M);
    for (int64_t i = 0; i < M; ++i) {
        std::cin >> operations[i].first >> operations[i].second;
    }

    // Process operations in reverse to build the final distribution
    // Each position will belong to some "group" at the end
    dsur_t dsu(N);

    // Process operations in reverse order
    for (int64_t op = M - 1; op >= 0; --op) {
        int64_t L = operations[op].first;
        int64_t R = operations[op].second;

        // All positions in [L, R] become equivalent
        for (int64_t i = L + 1; i <= R; ++i) {
            dsu.unite(L, i);
        }
    }

    // Group positions by their final equivalence class
    std::unordered_map<int64_t, std::vector<int64_t>> groups;
    for (int64_t i = 1; i <= N; ++i) {
        groups[dsu.find_parent(i)].push_back(i);
    }

    // For each group, calculate the expected value
    std::vector<int64_t> expected(N + 1, 0);

    for (auto& [root, positions] : groups) {
        int64_t group_size = positions.size();
        int64_t total_stones = 0;

        // Sum all stones that will end up in this group
        for (int64_t pos : positions) {
            total_stones = (total_stones + A[pos]) % MOD;
        }

        // Each position in the group gets equal expected value
        int64_t expected_per_position =
            (total_stones * mod_inv(group_size, MOD)) % MOD;

        for (int64_t pos : positions) {
            expected[pos] = expected_per_position;
        }
    }

    for (int64_t i = 1; i <= N; ++i) {
        std::cout << expected[i];
        if (i < N)
            std::cout << " ";
    }
    std::cout << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}