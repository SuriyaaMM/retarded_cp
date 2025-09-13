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
    int64_t n = 0LL;
    std::cin >> n;

    std::string s = "";
    std::cin >> s;

    std::vector<int64_t> fmap(26, ninf);
    for (int64_t i = 0; i < n; ++i) {
        if (fmap[s[i] - 'a'] == ninf) {
            fmap[s[i] - 'a'] = 0LL;
        }
        ++fmap[s[i] - 'a'];
    }

    std::ranges::sort(fmap);

    auto start = std::upper_bound(fmap.begin(), fmap.end(), ninf);
    auto end = std::lower_bound(fmap.begin(), fmap.end(), fmap.back());
    int64_t si = std::distance(fmap.begin(), start);
    int64_t se = std::distance(fmap.begin(), end);

    int64_t l = si, r = se, ans = 0LL, lci = 0LL;
    while (l < r) {
        int64_t diff = fmap[se] - fmap[r];
        if (diff == 0) {
            --r;
            continue;
        }
        int64_t acc = fmap[l];
        ans += acc;
        while (diff < acc) {
            ++l;
            acc += fmap[l];
            fmap[l] = 0;
        }

        fmap[l] = acc - diff;
        ans -= fmap[l];
        lci = r;
        --r;
        if (fmap[l] == 0) {
            ++l;
        }
    }

    for (int64_t i = si; i < lci; ++i) {
        ans += fmap[i];
    }

    std::cout << ans << std::endl;
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