#include <algorithm>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iostream>
#include <limits>
#include <map>
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

void solve() {
    int64_t h = 0L, w = 0L;
    std::cin >> h >> w;

    std::vector<std::vector<char>> grid(h, std::vector<char>(w, '0'));
    pair_t start = {0, 0}, goal = {0, 0};
    for (int64_t i = 0; i < h; ++i) {
        for (int64_t j = 0; j < w; ++j) {
            std::cin >> grid[i][j];
            if (grid[i][j] == 'S') {
                start = {i, j};
            }
            if (grid[i][j] == 'G') {
                goal = {i, j};
            }
        }
    }

    // (parity, x, y)
    std::deque<std::tuple<int64_t, int64_t, int64_t>> q;
    // [parity][h][w]
    std::vector<std::vector<std::vector<int64_t>>> dmat(
        2, std::vector<std::vector<int64_t>>(h, std::vector<int64_t>(w, inf)));
    // initial cond
    dmat[0][start.first][start.second] = 0;
    q.emplace_back(0, start.first, start.second);

    std::vector<int64_t> dx = {-1, 1, 0, 0};
    std::vector<int64_t> dy = {0, 0, -1, 1};

    int64_t xx = 0L, yy = 0L, cc = 0L;

    while (!q.empty()) {
        auto [c, x, y] = q.front();
        q.pop_front();

        for (int64_t i = 0; i < 4; ++i) {
            xx = dx[i] + x;
            yy = dy[i] + y;

            if (!(xx < h && yy < w && xx >= 0 && yy >= 0) ||
                grid[xx][yy] == '#' || (c == 0 && grid[xx][yy] == 'x') ||
                (c == 1 && grid[xx][yy] == 'o')) {
                continue;
            }

            cc = c ^ (grid[xx][yy] == '?');
            if (dmat[cc][xx][yy] != inf) {
                continue;
            } else {
                dmat[cc][xx][yy] = dmat[c][x][y] + 1;
                q.emplace_back(cc, xx, yy);
            }
        }
    }

    int64_t answer = std::min(dmat[0][goal.first][goal.second],
                              dmat[1][goal.first][goal.second]);
    if (answer == inf) {
        std::cout << -1 << std::endl;
    } else {
        std::cout << answer << std::endl;
    }
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

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