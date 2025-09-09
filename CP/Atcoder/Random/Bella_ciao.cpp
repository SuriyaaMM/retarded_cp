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
5 2 1 2

production = P * d + (P + Q) * d + ........ (P + (N - 1)Q) * d + some final loop

production = (P + P + ..... N-1 times) * d + (Q + 2Q + ....... (N - 1)Q) * d + final loop
production = (N - 1)*P*d + d*Q(N-1)(N-2)/2 + final loop

N = floor(D/d)

production = N * P * d + Q * d * N * N-1 / 2;
production_rate = Q * N * N-1/2; + P;
production += production_rate * (D - N + 1);
*/
void solve() {

    int64_t D = 0L, d = 0L, P = 0L, Q = 0L;
    std::cin >> D >> d >> P >> Q;

    int64_t N = D / d;
    int64_t R = D % d;

    int64_t total = d * (N * P + Q * N * (N - 1) / 2) + R * (P + N * Q);

    std::cout << total << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int64_t tt = 0L;
    std::cin >> tt;
    while (tt--) {

        solve();
    }

    return 0;
}