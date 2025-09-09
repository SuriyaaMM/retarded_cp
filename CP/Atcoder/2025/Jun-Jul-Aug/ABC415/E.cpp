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

int64_t H, W;
std::vector<std::vector<int64_t>> A;
std::vector<int64_t> P;

bool canSurvive(int64_t x) {

    std::vector<std::vector<int64_t>> dp(H + 1,
                                         std::vector<int64_t>(W + 1, inf));

    dp[H][W] = std::max(0L, P[H + W - 1] - A[H][W]);

    for (int64_t day = H + W - 2; day >= 1; --day) {
        for (int64_t i = 1; i <= H; ++i) {
            for (int64_t j = 1; j <= W; ++j) {
                if (i + j - 1 != day)
                    continue;

                int64_t min_needed = inf;

                if (j + 1 <= W && dp[i][j + 1] != inf) {

                    int64_t needed_before_collect =
                        dp[i][j + 1] + P[day] - A[i][j];
                    min_needed = std::min(min_needed,
                                          std::max(0L, needed_before_collect));
                }

                if (i + 1 <= H && dp[i + 1][j] != inf) {

                    int64_t needed_before_collect =
                        dp[i + 1][j] + P[day] - A[i][j];
                    min_needed = std::min(min_needed,
                                          std::max(0L, needed_before_collect));
                }

                dp[i][j] = min_needed;
            }
        }
    }

    return dp[1][1] <= x;
}

void solve() {
    std::cin >> H >> W;

    A.resize(H + 1, std::vector<int64_t>(W + 1));
    for (int64_t i = 1; i <= H; ++i) {
        for (int64_t j = 1; j <= W; ++j) {
            std::cin >> A[i][j];
        }
    }

    P.resize(H + W);
    for (int64_t i = 1; i < H + W; ++i) {
        std::cin >> P[i];
    }

    int64_t left = 0, right = 2e15;
    int64_t answer = right;

    while (left <= right) {
        int64_t mid = left + (right - left) / 2;

        if (canSurvive(mid)) {
            answer = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    std::cout << answer << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}