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

struct Present {
    long long p, a, b;
};

long long get_final_mood(long long initial_mood, int n,
                         const std::vector<Present>& presents) {
    long long current_mood = initial_mood;
    for (int j = 0; j < n; ++j) {
        if (presents[j].p >= current_mood) {
            current_mood += presents[j].a;
        } else {
            current_mood = std::max(0LL, current_mood - presents[j].b);
        }
    }
    return current_mood;
}

void solve() {
    int64_t n = 0L;
    std::cin >> n;

    std::vector<Present> presents(n, {0, 0, 0});
    int64_t total_b = 0;
    std::vector<int64_t> b_values(n);
    for (int64_t i = 0; i < n; ++i) {
        std::cin >> presents[i].p >> presents[i].a >> presents[i].b;
        total_b += presents[i].b;
        b_values[i] = presents[i].b;
    }

    int64_t tipping_point = 0L, current_b_sum = 0L;
    for (int k = 0; k < n; ++k) {
        tipping_point =
            std::max(tipping_point, (int64_t)(presents[k].p + current_b_sum));
        current_b_sum += b_values[k];
    }

    const int64_t precomputation_limit = std::min(tipping_point, 200000L);

    std::vector<int64_t> final_mood_precomputed;
    if (precomputation_limit >= 0) {
        final_mood_precomputed.resize(precomputation_limit + 1);
        for (int64_t i = 0; i <= precomputation_limit; ++i) {
            final_mood_precomputed[i] = get_final_mood(i, n, presents);
        }
    }

    int64_t q = 0L;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        int64_t xi = 0L;
        std::cin >> xi;
        if (xi > tipping_point) {
            std::cout << std::max(0L, xi - total_b) << "\n";
        } else {
            if (xi <= precomputation_limit) {
                std::cout << final_mood_precomputed[xi] << "\n";
            } else {
                std::cout << get_final_mood(xi, n, presents) << "\n";
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}