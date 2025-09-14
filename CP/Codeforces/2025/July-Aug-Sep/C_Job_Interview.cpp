#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <map>
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
    int64_t n = 0LL, m = 0LL;
    std::cin >> n >> m;

    std::vector<int64_t> a(n + m + 1, 0), b(n + m + 1, 0);
    read_vec(0, n + m + 1, a);
    read_vec(0, n + m + 1, b);

    std::vector<bool> nth(n + m + 1, true);

    int64_t ti = 0LL, nh = 0LL, mh = 0LL;
    for (int64_t i = 1; i < n + m + 1; ++i) {
        // programmer
        if (a[i] > b[i]) {
            if (nh < n) {
                ++nh;
                ti += a[i];
            } else {
                ++mh;
                ti += b[i];
                nth[i] = false;
            }
        } else {
            if (mh < m) {
                ++mh;
                ti += b[i];
                nth[i] = false;
            } else {
                ++nh;
                ti += a[i];
            }
        }
    }

    std::vector<int64_t> ans(n + m + 1, 0);
    ans[0] = ti;
    for (int64_t i = 1; i < n + m + 1; ++i) {
        // this hire was a programmer
        if (nth[i]) {
            --nh;
            ti -= a[i];
        } else {
            --mh;
            ti -= b[i];
        }

        if (a[i - 1] > b[i - 1]) {
            if (nh < n) {
                ++nh;
                ti += a[i - 1];
            } else {
                ++mh;
                ti += b[i - 1];
                nth[i - 1] = false;
            }
        } else {
            if (mh < m) {
                ++mh;
                ti += b[i - 1];
                nth[i - 1] = false;
            } else {
                ++nh;
                ti += a[i - 1];
            }
        }
        ans[i] = ti;
    }

    for (const auto& ai : ans) {
        std::cout << ai << " ";
    }
    std::cout << std::endl;
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