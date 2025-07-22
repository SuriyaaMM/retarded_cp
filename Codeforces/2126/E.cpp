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

//
int64_t gcd(int64_t a, int64_t b) {
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

void solve() {
    int n;
    std::cin >> n;
    std::vector<int64_t> p(n), s(n);
    read_vec(0, n, p);
    read_vec(0, n, s);

    if (n == 1) {
        std::cout << (p[0] == s[0] ? "Yes\n" : "No\n");
        return;
    }

    bool possible = true;

    if (p.back() != s.front()) {
        possible = false;
    }

    for (int64_t i = 1; i < n && possible; ++i) {
        if (p[i - 1] % p[i] != 0) {
            possible = false;
        }
    }

    for (int64_t i = 0; i < n - 1 && possible; ++i) {
        if (s[i + 1] % s[i] != 0) {
            possible = false;
        }
    }

    if (!possible) {
        std::cout << "No\n";
        return;
    }
    // boundary checks
    if (s[0] != gcd(p[0], s[1])) {
        possible = false;
    }
    if (p[n - 1] != gcd(p[n - 2], s[n - 1])) {
        possible = false;
    }
    // intermediate checks
    for (int64_t i = 1; i < n - 1 && possible; ++i) {
        int64_t common_gcd = gcd(p[i], s[i]);
        if (gcd(p[i - 1] / p[i], s[i] / common_gcd) != 1) {
            possible = false;
        }
        if (gcd(p[i] / common_gcd, s[i + 1] / s[i]) != 1) {
            possible = false;
        }
    }

    std::cout << (possible ? "Yes\n" : "No\n");
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}