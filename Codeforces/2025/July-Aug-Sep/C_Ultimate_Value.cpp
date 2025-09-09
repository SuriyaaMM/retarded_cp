#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <iterator>
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

void solve() {
    int64_t n = 0L;
    std::cin >> n;

    std::vector<int64_t> a(n, 0);
    read_vec(0, n, a);

    int64_t si = 0;
    for (int64_t i = 0; i < n; i++) {
        if (i % 2 == 0) {
            si += a[i];
        } else {
            si -= a[i];
        }
    }

    int64_t gmax = 0;

    if (n > 1) {
        int64_t gsp = 0;
        int64_t lei = (n % 2 != 0) ? n - 1 : n - 2;

        gsp = std::max(gsp, lei - 0);
        if (n > 2) {
            int64_t last_odd_idx = (n % 2 == 0) ? n - 1 : n - 2;
            gsp = std::max(gsp, last_odd_idx - 1);
        }
        gmax = std::max(gmax, gsp);
    }

    int64_t mpv = inf;
    int64_t g1 = 0LL;
    for (int64_t k = 0; k < n; ++k) {
        if (k % 2 == 0) {
            mpv = std::min(mpv, 2 * a[k] + k);
        } else {
            if (mpv != inf) {
                g1 = std::max(g1, (2 * a[k] + k) - mpv);
            }
        }
    }

    int64_t msv = inf;
    int64_t g2 = 0LL;
    for (int64_t k = n - 1; k >= 0; --k) {
        if (k % 2 == 0) {
            msv = std::min(msv, 2 * a[k] - k);
        } else {
            if (msv != inf) {
                g2 = std::max(g2, (2 * a[k] - k) - msv);
            }
        }
    }

    gmax = std::max(gmax, std::max(g1, g2));
    std::cout << si + gmax << std::endl;
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