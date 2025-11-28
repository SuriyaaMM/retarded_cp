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
#define print_vec(begin, end, vec) \
    for (int64_t i = begin; i < end; ++i) std::cout << vec[i] << " ";

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
        if (parent[x] != x) parent[x] = find_parent(parent[x]);
        return parent[x];
    }

    void unite(int64_t u, int64_t v) {
        u = find_parent(u);
        v = find_parent(v);

        if (v == u) return;

        if (rank[u] < rank[v]) std::swap(u, v);

        parent[v] = u;
        if (rank[u] == rank[v]) ++rank[u];
    }
};

// bottom-up implementation of segment tree
struct stree_bu {
    /*
    p >> 1 = p / 2
    p ^ 1 => sends us to the sibling node regardless of whether it is left or
    right child
    */

    int64_t n = 0LL;
    std::vector<int64_t> t;

    stree_bu(const int64_t& n) : n(n), t(2 * n) {}

    stree_bu(std::vector<int64_t>& a) {
        n = a.size();
        t.resize(2 * n);

        for (int64_t i = 0; i < n; ++i) {
            t[n + i] = a[i];
        }

        for (int64_t i = n - 1; i > 0; --i) {
            t[i] = t[i * 2] + t[i * 2 + 1];
        }
    }

    void update(int64_t p, const int64_t& v) {
        // traverse to the leaf node & update its value
        p += n;
        t[p] = v;
        // propagate up the tree
        for (; p > 1; p >>= 1) {
            t[p >> 1] = t[p] + t[p ^ 1];
        }
    }

    int64_t query(int64_t l, int64_t r) {
        int64_t s = 0LL;
        l += n;
        r += n;
        for (; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) s += t[l++];
            if (!(r & 1)) s += t[r--];
        }
        return s;
    }
};

void solve() {
    int64_t n = 0LL, q = 0LL;
    std::cin >> n >> q;

    std::vector<int64_t> rc(n + 1, 0), cc(n + 1, 0), iz(n + 1, 0);
    stree_bu rt(iz), ct(iz);

    for (int64_t i = 0; i < q; ++i) {
        int64_t t = 0LL;
        std::cin >> t;

        if (t == 1) {
            int64_t x = 0LL, y = 0LL;
            std::cin >> x >> y;

            if (rc[x] == 0) rt.update(x, 1);
            if (cc[y] == 0) ct.update(y, 1);

            rc[x]++;
            cc[y]++;
        } else if (t == 2) {
            int64_t x = 0LL, y = 0LL;
            std::cin >> x >> y;

            rc[x]--;
            cc[y]--;

            if (rc[x] == 0) rt.update(x, 0);
            if (cc[y] == 0) ct.update(y, 0);
        } else {
            int64_t x1 = 0LL, y1 = 0LL, x2 = 0LL, y2 = 0LL;
            std::cin >> x1 >> y1 >> x2 >> y2;

            bool rr = rt.query(x1, x2) == (x2 - x1 + 1);
            bool cc = ct.query(y1, y2) == (y2 - y1 + 1);

            if (rr || cc)
                std::cout << "Yes" << "\n";
            else
                std::cout << "No" << "\n";
        }
    }
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

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