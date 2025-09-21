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

void solve() {
    int64_t n = 0LL;
    std::cin >> n;
    std::string s = "";
    std::cin >> s;

    bool pi = true;
    int64_t i = 0;
    while (i < n) {
        if (s[i] == '0') {
            int64_t j = i;
            while (j < n && s[j] == '0') {
                j++;
            }

            if (j - i == 1) {
                pi = false;
                break;
            }
            i = j;
        } else {
            i++;
        }
    }

    if (!pi) {
        std::cout << "NO" << std::endl;
        return;
    }

    std::cout << "YES" << std::endl;
    std::vector<int64_t> p(n + 1, 0);

    i = 0;
    while (i < n) {
        if (s[i] == '1') {
            p[i + 1] = i + 1;
            i++;
        } else {
            int64_t j = i;
            while (j < n && s[j] == '0') {
                j++;
            }

            int64_t bs = i + 1;
            int64_t be = j;

            p[bs] = be;
            for (int64_t k = bs + 1; k <= be; ++k) {
                p[k] = k - 1;
            }
            i = j;
        }
    }

    for (int64_t k = 1; k <= n; ++k) {
        if (k == n) {
            std::cout << p[k] << "";
        } else {
            std::cout << p[k] << " ";
        }
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