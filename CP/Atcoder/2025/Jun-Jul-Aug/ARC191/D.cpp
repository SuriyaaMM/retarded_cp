#include <cstddef>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using graph_t = std::vector<std::vector<size_t>>;
using pair_t = std::tuple<size_t, size_t, size_t>;

void solve() {

    size_t n = 0UL, m = 0UL, s = 0UL, t = 0UL;
    std::cin >> n >> m >> s >> t;

    graph_t graph(n + 1);

    size_t ui = 0UL, vi = 0UL;
    for (size_t i = 0; i < m; ++i) {
        std::cin >> ui >> vi;
        graph[ui].emplace_back(vi);
        graph[vi].emplace_back(ui);
    }

    std::vector<std::vector<bool>> visited(n + 1,
                                           std::vector<bool>(n + 1, false));
    std::queue<pair_t> q;
    q.push({s, t, 0});
    visited[s][t] = true;

    while (!q.empty()) {

        auto& [current_a, current_b, distance] = q.front();
        q.pop();

        if (current_a == t && current_b == s) {
            std::cout << distance << std::endl;
            return;
        }

        for (auto& neighbour : graph[current_a]) {
            if (neighbour != current_b) {
                if (!visited[neighbour][current_b]) {
                    visited[neighbour][current_b] = true;
                    q.push({neighbour, current_b, distance + 1});
                }
            }
        }
        for (auto& neighbour : graph[current_b]) {
            if (neighbour != current_a) {
                if (!visited[current_a][neighbour]) {
                    visited[current_a][neighbour] = true;
                    q.push({current_a, neighbour, distance + 1});
                }
            }
        }
    }

    std::cout << -1 << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}