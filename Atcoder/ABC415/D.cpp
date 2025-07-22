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

#define LOCAL
#ifdef LOCAL
const std::string COLOR_RESET = "\033[0m", BRIGHT_GREEN = "\033[1;32m",
                  BRIGHT_RED = "\033[1;31m", BRIGHT_CYAN = "\033[1;36m",
                  NORMAL_CROSSED = "\033[0;9;37m",
                  RED_BACKGROUND = "\033[1;41m", NORMAL_FAINT = "\033[0;2m";
#define dbg(x)                                                         \
    std::cerr << BRIGHT_CYAN << #x << COLOR_RESET << " = " << (x)      \
              << NORMAL_FAINT << " (L" << __LINE__ << ") " << __FILE__ \
              << COLOR_RESET << std::endl
#define dbgif(cond, x)                                                      \
    ((cond) ? std::cerr << BRIGHT_CYAN << #x << COLOR_RESET << " = " << (x) \
                        << NORMAL_FAINT << " (L" << __LINE__ << ") "        \
                        << __FILE__ << COLOR_RESET << std::endl             \
            : std::cerr)
#else
#define dbg(x) ((void)0)
#define dbgif(cond, x) ((void)0)
#endif

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
// generic state
template <typename... T>
using gstate_t = std::tuple<T...>;
// unweighted graph
using graph_t = std::vector<std::vector<int64_t>>;
// weighted graph
using wgraph_t = std::vector<std::vector<pair_t>>;

// disjoint set union by rank & path compression
struct dsur_t {
    std::vector<int64_t> parent, rank;

    dsur_t(int64_t n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int64_t i = 1; i <= n; ++i) {
            parent[i] = i;
        }
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
    int64_t n = 0L, m = 0L, ai = 0L, bi = 0L, ci = 0L;
    std::cin >> n >> m;
    using state_t = gstate_t<int64_t, int64_t, int64_t>;

    std::vector<state_t> a(m, {0, 0, 0});
    for (int64_t i = 0; i < m; ++i) {
        std::cin >> ai >> bi;
        ci = ai - bi;
        a[i] = std::make_tuple(ci, ai, bi);
    }
    std::ranges::sort(a);
    int64_t max_stickers = 0L, stickers = 0L;
    for (const auto& [dx, ax, bx] : a) {
        if (n < ax)
            continue;
        if (dx == 0)
            continue;
        stickers = (n - ax) / dx + 1;
        max_stickers += stickers;
        n -= dx * stickers;
    }
    std::cout << max_stickers << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}