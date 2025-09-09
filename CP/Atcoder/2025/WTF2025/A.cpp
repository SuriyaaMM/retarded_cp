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
        std::cout << vec[i] << " ";       \
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

// disjoint set union with path compression
struct dsur_t {
    std::vector<int64_t> parent, rank;
    dsur_t(int64_t n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int64_t i = 1; i <= n; ++i)
            parent[i] = i;
    }
    int64_t find_parent(int64_t x) {
        if (parent[x] != x)
            parent[x] = find_parent(parent[x]);
        return parent[x];
    }
    void unite(int64_t u, int64_t v) {
        u = find_parent(u);
        v = find_parent(v);
        if (u == v)
            return;
        if (rank[u] < rank[v])
            std::swap(u, v);
        parent[v] = u;
        if (rank[u] == rank[v])
            ++rank[u];
    }
};

// compute LIS length O(N log N)
int64_t lis_length(const std::vector<int64_t>& P) {
    std::vector<int64_t> dp;
    for (int64_t val : P) {
        auto it = std::lower_bound(dp.begin(), dp.end(), val);
        if (it == dp.end())
            dp.push_back(val);
        else
            *it = val;
    }
    return dp.size();
}

void solve() {
    int64_t T;
    std::cin >> T;

    std::vector<std::vector<int64_t>> results;

    while (T--) {
        int64_t N;
        std::cin >> N;
        std::vector<int64_t> P(N);
        read_vec(0, N, P);

        int64_t target_lis = lis_length(P);

        bool changed = true;
        while (changed) {
            changed = false;
            for (int64_t i = 0; i < N - 1; ++i) {
                if (P[i] > P[i + 1]) {
                    std::swap(P[i], P[i + 1]);
                    if (lis_length(P) == target_lis) {
                        changed = true;
                    } else {
                        std::swap(P[i], P[i + 1]);  // revert swap
                    }
                }
            }
        }

        results.push_back(P);
    }

    for (const auto& vec : results) {
        print_vec(0, vec.size(), vec);
    }
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    solve();
    return 0;
}
