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

struct SegmentTree {
    std::vector<int64_t> segtree;

    // O(n), initializes segment tree with 4 * n
    SegmentTree(const int64_t& n) { segtree.resize(4 * n); }

    // O(nlogn), builds the segment tree
    void build(int64_t root, int64_t l, int64_t r, std::vector<int64_t>& a) {
        if (l == r) {
            segtree[root] = a[l];
        } else {
            int64_t mid = (l + r) / 2;
            build(root * 2, l, mid, a);
            build(root * 2 + 1, mid + 1, r, a);
            segtree[root] = segtree[root * 2] + segtree[root * 2 + 1];
        }
    }

    // O(logn), finds the range sum, bl and br are boundaries
    int64_t query(int64_t root, int64_t bl, int64_t br, int64_t l, int64_t r) {
        if (l > r) {
            return 0;
        }
        if (l == bl && r == br) {
            return segtree[root];
        }
        int64_t bmid = (bl + br) / 2;
        return query(root * 2, bl, bmid, l, r) +
               query(root * 2 + 1, bmid + 1, br, l, r);
    }
};

void solve() {}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}