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

bool check(int64_t x, std::vector<pair_t>& customer, int64_t& k) {
    int64_t tk = 0L;
    for (const auto& [bi, ai] : customer) {
        if (x > ai && x <= bi) {
            ++tk;
        }
        if (tk > k) {
            return false;
        }
    }

    return true;
}

void solve() {
    int64_t n = 0L, k = 0L;
    std::cin >> n >> k;

    std::vector<pair_t> customer(n, {0, 0});
    for (int64_t i = 0; i < n; ++i) {
        int64_t ai = 0L, bi = 0L;
        std::cin >> bi >> ai;
        customer[i] = {bi, ai};
    }

    std::sort(customer.begin(), customer.end());

    int64_t low = 0L, high = 2e10, max_tp = 0L;
    while (low <= high) {
        int64_t mid = (low + high) / 2;
        if (check(mid, customer, k)) {
            low = mid + 1;
            max_tp = mid;
        } else {
            high = mid - 1;
        }
    }

    int64_t tk = 0L, max_price = 0L;
    for (const auto& [bi, ai] : customer) {
        if (max_tp > ai && max_tp <= bi) {
            max_price += max_tp;
            ++tk;
        } else if (max_tp <= ai) {
            max_price += max_tp;
        }
        if (tk > k) {
            break;
        }
    }

    std::cout << max_price << std::endl;
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