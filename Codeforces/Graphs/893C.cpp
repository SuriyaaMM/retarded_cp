// https://codeforces.com/problemset/problem/893/C

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<int64_t>>;

void dfs(int64_t current_node, graph_t& graph, std::vector<bool>& visited,
         std::vector<int64_t>& friends) {
    friends.emplace_back(current_node);
    for (const auto& neighbour : graph[current_node]) {
        if (!visited[neighbour]) {
            visited[neighbour] = true;
            dfs(neighbour, graph, visited, friends);
        }
    }
}

void solve() {

    int64_t n = 0LL, m = 0LL;
    std::cin >> n >> m;

    std::vector<int64_t> c(n, 0);
    for (int64_t i = 0; i < n; ++i) {
        std::cin >> c[i];
    }

    int64_t xi = 0LL, yi = 0LL;
    graph_t graph(n);
    for (int64_t i = 0; i < m; ++i) {
        std::cin >> xi >> yi;
        graph[--xi].emplace_back(--yi);
        graph[yi].emplace_back(xi);
    }

    std::vector<bool> visited(n, false);
    int64_t total_cost = 0LL;
    for (int64_t i = 0; i < n; ++i) {
        if (!visited[i]) {
            // if we haven't spread the rumour to this guy i, then we will spread to him once
            visited[i] = true;
            std::vector<int64_t> friends;
            // this is free operation because he will spread to all of his friends for free
            dfs(i, graph, visited, friends);
            total_cost +=
                c[*std::min_element(friends.begin(), friends.end(),
                                    [&](int64_t node1, int64_t node2) {
                                        return c[node1] < c[node2];
                                    })];
        }
    }

    std::cout << total_cost << std::endl;
}

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}