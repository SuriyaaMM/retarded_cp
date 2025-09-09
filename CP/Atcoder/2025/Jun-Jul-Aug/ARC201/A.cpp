#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <string>
#include <tuple>
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

std::vector<int64_t> minimum_number_of_div1s(2e5, 0),
    maximum_number_of_div1s(2e5, 0), a(2e5, 0), b(2e5, 0), c(2e5, 0);

void solve() {

    using state_t = std::tuple<int64_t, int64_t, int64_t>;
    int64_t n = 0LL;
    std::cin >> n;

    int64_t minimum_number_of_div1_net = 0LL, maximum_number_of_div1_net = 0LL,
            mediums = 0LL;
    for (int64_t i = 0; i < n; ++i) {
        std::cin >> a[i] >> b[i] >> c[i];
        b[i] = std::min(b[i], a[i] + c[i]);
        mediums += b[i];
        minimum_number_of_div1s[i] = std::max((int64_t)(0), b[i] - c[i]);
        maximum_number_of_div1s[i] = std::min(a[i], b[i]);
        minimum_number_of_div1_net += minimum_number_of_div1s[i];
        maximum_number_of_div1_net += maximum_number_of_div1s[i];
    }

    std::cout << std::min(mediums / 2,
                          std::min(maximum_number_of_div1_net,
                                   mediums - minimum_number_of_div1_net))
              << "\n";
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int64_t t = 0LL;
    std::cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}