#include <bits/stdc++.h>

static constexpr const std::int32_t __N = 2e5 + 1;
static constexpr const std::int32_t __N_LOG = 22;
static constexpr const std::int32_t __N_ETT = 2 * __N;

using basic_array = std::array<std::int32_t, __N>;
using tour_array = std::array<std::int32_t, __N_ETT>;

static std::array<std::array<std::int32_t, __N_LOG>, __N_ETT> sparse_table;
static std::array<std::int32_t, __N> depth, tin, lcas;
static std::array<std::int32_t, __N_ETT> ett;

struct sparse_table_t {

    basic_array &comparator;
    std::int32_t n_entries, n_log;

    sparse_table_t(basic_array &__restrict__ comparator,
                   tour_array &__restrict__ array, std::int32_t timer) :
        comparator(comparator) {

        n_entries = timer;
        n_log = (std::int32_t)std::log2(n_entries) + 1;

        for (std::int32_t i = 0; i < n_entries; ++i) {
            sparse_table[i][0] = array[i];
        }

        for (std::int32_t j = 1; j < n_log; ++j) {
            for (std::int32_t i = 0; i + (1 << j) <= n_entries; ++i) {
                std::int32_t l = sparse_table[i][j - 1];
                std::int32_t r = sparse_table[i + (1 << (j - 1))][j - 1];
                sparse_table[i][j] = (comparator[l] < comparator[r]) ? l : r;
            }
        }
    }

    std::int32_t query(std::int32_t l, std::int32_t r) const {
        if (l > r) std::swap(l, r);

        std::int32_t length = r - l + 1;
        std::int32_t k = (std::int32_t)std::log2(length);

        std::int32_t ll = sparse_table[l][k];
        std::int32_t rr = sparse_table[r - (1 << k) + 1][k];

        return (comparator[ll] < comparator[rr]) ? ll : rr;
    }
};

void solve() {
    std::int32_t n = 0;
    std::cin >> n;

    std::vector<std::vector<std::int32_t>> adjlist(n + 1);
    for (std::int32_t i = 2; i <= n; ++i) {
        std::int32_t p = 0;
        std::cin >> p;
        adjlist[p].emplace_back(i);
    }

    std::vector<std::vector<std::int32_t>> depthlist(n + 1);
    std::int32_t timer = 0;

    const auto dfs = [&](const auto &recurser, std::int32_t node,
                         std::int32_t p, std::int32_t d) -> void {
        ett[timer] = node;
        tin[node] = timer;
        ++timer;

        depth[node] = d;
        depthlist[d].emplace_back(node);

        for (const auto &nnode : adjlist[node]) {
            if (nnode != p) {
                recurser(recurser, nnode, node, d + 1);
                ett[timer] = node;
                ++timer;
            }
        }
    };

    dfs(dfs, 1, 0, 0);

    sparse_table_t st(depth, ett, timer);

    std::int64_t answer = n;

    for (std::int32_t i = 0; i < (std::int32_t)depthlist.size(); ++i) {
        std::int32_t index = 0;
        for (std::int32_t j = 1; j < (std::int32_t)depthlist[i].size(); ++j) {
            std::int32_t current = depthlist[i][j],
                         before = depthlist[i][j - 1];
            lcas[index++] = st.query(tin[current], tin[before]);
        }
        if (index > 0) {
            std::ranges::sort(lcas.begin(), lcas.begin() + index);
            auto unique_end = std::unique(lcas.begin(), lcas.begin() + index);
            answer += std::distance(lcas.begin(), unique_end);
        }
    }

    std::cout << answer << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::int32_t t = 1;
    std::cin >> t;

    while (t--) { solve(); }
}