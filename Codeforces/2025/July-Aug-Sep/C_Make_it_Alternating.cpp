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

const int64_t MOD = 998244353;
std::vector<int64_t> factorial(2e5, 0);
void solve() {
    std::string s = "";
    std::cin >> s;
    int64_t n = s.size();
    // fact
    factorial[0] = 1;
    for (int64_t i = 1; i < 2e5; ++i) {
        factorial[i] = (factorial[i - 1] * (n - i)) % MOD;
    }

    // count
    int64_t count_1s = 0L, count_0s = 0L;
    for (int64_t i = 0; i < s.size(); ++i) {
        if (s[i] == '1') {
            ++count_1s;
        } else {
            ++count_0s;
        }
    }

    if (count_0s == 0 || count_1s == 0) {
        int64_t answer = std::max(count_1s - 1, count_0s - 1);
        std::cout << answer << " " << factorial[answer] << std::endl;
    } else {
        int64_t answer = std::abs(count_1s - count_0s);
        std::cout << answer << " " << factorial[answer] << std::endl;
    }
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int64_t t = 0L;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}