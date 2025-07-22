#include <cstdint>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// infinity
constexpr const int64_t inf = std::numeric_limits<int64_t>::max();
constexpr const int64_t ninf = std::numeric_limits<int64_t>::min();

using pair_t = std::pair<int64_t, int64_t>;
template <typename T1, typename T2>
using gpair_t = std::pair<T1, T2>;
using graph_t = std::vector<std::vector<int64_t>>;
using wgraph_t = std::vector<std::vector<pair_t>>;
using state_t = std::tuple<int64_t, int64_t>;  // (node, steps_within_k)

const int MAXN = 200005;

// Global reused storage
graph_t graph(MAXN);
std::vector<int64_t> min_moves(MAXN, -1);
std::vector<int> visited(MAXN, 0);
int visited_marker = 0;

void solve() {
    int64_t n = 0LL, k = 0LL;
    std::cin >> n >> k;

    for (int64_t i = 0; i < n; ++i) {
        graph[i].clear();
        min_moves[i] = -1;
    }

    int64_t ui = 0LL, vi = 0LL;
    for (int64_t i = 0; i < n - 1; ++i) {
        std::cin >> ui >> vi;
        --ui;
        --vi;
        graph[ui].emplace_back(vi);
        graph[vi].emplace_back(ui);
    }

    std::queue<int64_t> q;
    q.push(0);
    min_moves[0] = 0;

    while (!q.empty()) {
        int64_t start = q.front();
        q.pop();

        int64_t current_moves = min_moves[start];

        // internal BFS
        std::queue<state_t> bfs;
        ++visited_marker;
        bfs.push({start, 0});
        visited[start] = visited_marker;

        while (!bfs.empty()) {
            auto [node, depth] = bfs.front();
            bfs.pop();

            if (depth == k) {
                if (min_moves[node] == -1) {
                    min_moves[node] = current_moves + 1;
                    q.push(node);
                }
                continue;
            }

            for (int64_t neighbor : graph[node]) {
                if (visited[neighbor] != visited_marker) {
                    visited[neighbor] = visited_marker;
                    bfs.push({neighbor, depth + 1});
                }
            }
        }
    }

    for (int64_t i = 1; i < n; ++i) {
        std::cout << min_moves[i] << " ";
    }
    std::cout << std::endl;
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
