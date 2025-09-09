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

#define read_vec(begin, end, vec)         \
    for (int64_t i = begin; i < end; ++i) \
        std::cin >> vec[i];

#define read_vecp(begin, end, vec)        \
    for (int64_t i = begin; i < end; ++i) \
        std::cin >> vec[i].first >> vec[i].second;

#define print_vec(begin, end, vec)        \
    for (int64_t i = begin; i < end; ++i) \
        std::cout << vec[i] << " ";

constexpr const int64_t inf = std::numeric_limits<int64_t>::max();
constexpr const int64_t ninf = std::numeric_limits<int64_t>::min();

using pair_t = std::pair<int64_t, int64_t>;
template <typename T1, typename T2>
using gpair_t = std::pair<T1, T2>;
using graph_t = std::vector<std::vector<int64_t>>;
using wgraph_t = std::vector<std::vector<pair_t>>;

struct dsur_t {
    std::vector<int64_t> parent, rank;
    dsur_t(int64_t n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int64_t i = 1; i <= n; ++i)
            parent[i] = i;
    }
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
    int64_t n, k;
    std::cin >> n >> k;
    std::vector<std::string> s(n);
    read_vec(0, n, s);

    std::sort(s.begin(), s.end(),
              [](const std::string& a, const std::string& b) {
                  return a + b < b + a;
              });

    std::string result;
    result.reserve(k * 10);
    for (int64_t i = 0; i < k; ++i) {
        result += s[0];
    }
    std::cout << result << '\n';
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    solve();
    return 0;
}
