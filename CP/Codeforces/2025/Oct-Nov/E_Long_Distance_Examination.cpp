#include <algorithm>
#include <array>
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
    for (int32_t i = begin; i < end; ++i) std::cin >> vec[i];

// reads the vector pair
#define read_vecp(begin, end, vec)        \
    for (int32_t i = begin; i < end; ++i) \
        std::cin >> vec[i].first >> vec[i].second;

// prints the vector
#define print_vec(begin, end, vec) \
    for (int32_t i = begin; i < end; ++i) std::cout << vec[i] << " ";

// infinity
constexpr const int32_t inf = std::numeric_limits<int32_t>::max();
// negative infinity
constexpr const int32_t ninf = std::numeric_limits<int32_t>::min();

// pair
using pair_t = std::pair<int32_t, int32_t>;
// generic pair
template <typename T1, typename T2>
using gpair_t = std::pair<T1, T2>;
// unweighted graph
using graph_t = std::vector<std::vector<int32_t>>;
// weighted graph
using wgraph_t = std::vector<std::vector<pair_t>>;

void solve() {
    int32_t r = 0LL, c = 0LL;
    std::cin >> r >> c;

    using grid = std::vector<std::vector<char>>;

    grid grid_a(r + 2, std::vector<char>(c + 2, 'X')),
        grid_b(r + 2, std::vector<char>(c + 2, 'X'));

    pair_t start_a = {0, 0}, start_b = {0, 0}, end = {0, 0};

    for (int32_t i = 0; i < r; ++i) {
        for (int32_t j = 0; j < c; ++j) {
            std::cin >> grid_a[i + 1][j + 1];
            if (grid_a[i + 1][j + 1] == 'S') start_a = {i + 1, j + 1};
        }
    }
    for (int32_t i = 0; i < r; ++i) {
        for (int32_t j = 0; j < c; ++j) {
            std::cin >> grid_b[i + 1][j + 1];
            if (grid_b[i + 1][j + 1] == 'S') start_b = {i + 1, j + 1};
            if (grid_b[i + 1][j + 1] == 'D') end = {i + 1, j + 1};
        }
    }

    using pdim4 = std::array<int32_t, 4>;

    pdim4 dx = {1, -1, 0, 0};
    pdim4 dy = {0, 0, 1, -1};

    std::queue<pdim4> q;

    int w = c + 2;
    int layer = (r + 2) * w;
    std::vector<int32_t> distance(layer * layer, inf);

    auto get_idx = [&](int32_t bi, int32_t bj, int32_t ai, int32_t aj) {
        return (bi * w + bj) * layer + (ai * w + aj);
    };

    int s_idx =
        get_idx(start_b.first, start_b.second, start_a.first, start_a.second);
    distance[s_idx] = 0;
    q.push({start_b.first, start_b.second, start_a.first, start_a.second});

    auto push_functor = [&](const pdim4& current, const pdim4& next) {
        const auto& [bi, bj, ai, aj] = current;
        const auto& [bin, bjn, ain, ajn] = next;

        int n_idx = get_idx(bin, bjn, ain, ajn);
        int c_idx = get_idx(bi, bj, ai, aj);

        if (distance[n_idx] == inf) {
            distance[n_idx] = distance[c_idx] + 1;
            q.push({bin, bjn, ain, ajn});
        }
    };

    while (!q.empty()) {
        const auto& current = q.front();
        const auto& [bi, bj, ai, aj] = current;
        q.pop();

        for (int32_t i = 0; i < 4; ++i) {
            int32_t bii = bi + dx[i], bjj = bj + dy[i];
            int32_t aii = ai + dx[i], ajj = aj + dy[i];

            pdim4 next = {bii, bjj, aii, ajj};
            pdim4 next2 = {bi, bj, aii, ajj};
            if (grid_a[aii][ajj] != 'X') {
                if (grid_b[bii][bjj] != 'X') {
                    push_functor(current, next);
                } else {
                    push_functor(current, next2);
                }
            }
        }
    }

    int32_t dmax = inf;
    for (int32_t i = 1; i <= r; ++i) {
        for (int32_t j = 1; j <= c; ++j) {
            int idx = get_idx(end.first, end.second, i, j);
            if (distance[idx] != inf) dmax = std::min(dmax, distance[idx]);
        }
    }
    if (dmax == inf) {
        std::cout << -1 << "\n";
        return;
    }
    std::cout << dmax << "\n";
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#define MT
#ifdef MT
    int32_t tt = 0L;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
#else
    solve();
#endif

    return 0;
}