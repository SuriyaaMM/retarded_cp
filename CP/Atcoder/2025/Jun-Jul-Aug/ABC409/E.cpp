
#include <iostream>
#include <utility>
#include <vector>

using edge_t = std::pair<size_t, size_t>;
using graph_t = std::vector<std::vector<edge_t>>;

int main(int, char**) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t n = 0UL, u = 0UL, v = 0UL, w = 0UL;
    std::cin >> n;

    std::vector<int64_t> x(n);
    graph_t graph(n);

    for (size_t i = 0; i < n; ++i) {
        std::cin >> x[i];
    }

    for (size_t i = 0; i < n - 1; ++i) {
        std::cin >> u >> v >> w;
        // compensation for 1-based indexing
        --u;
        --v;
        // bidirectional graph
        graph[u].emplace_back(edge_t(v, w));
        graph[v].emplace_back(edge_t(u, w));
    }

    // so this is simply a sum of all node * edgeweight problem instead of minimizing
    // because if an node contains |x| charge, no matter what we do, we will have to move it along
    // the edge. so effective cost will be sum of |xj|* wj for every node in the tree
    // this can be done using a dfs instead of a bfs because it makes sense to do it in dfs fashion

    size_t min_cost = 0UL;

    auto dfs = [&](auto& dfs, size_t u, size_t parent) -> void {
        // for each neighbour for this node we will perform dfs and calculate required cost
        for (auto& [v, w] : graph[u]) {
            // avoids loops while traversing the tree
            if (v == parent) {
                continue;
            }
            dfs(dfs, v, u);
            min_cost += w * std::abs(x[v]);
            // sum up the particles for this subtree since we annihilated them by bringing
            // them together to this edge
            x[u] += x[v];
        }
    };

    dfs(dfs, 0, -1);

    std::cout << min_cost << std::endl;

    return 0;
}