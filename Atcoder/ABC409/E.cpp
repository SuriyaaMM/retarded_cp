
#include <iostream>
#include <utility>
#include <vector>

using Edge = std::pair<int64_t, int64_t>;
using Graph = std::vector<std::vector<Edge>>;

std::vector<int64_t> x_values;
long long total_min_energy = 0LL;

long long dfs(int64_t u, int64_t parent, const Graph& graph) {
    long long current_subtree_charge = x_values[u];

    for (const auto& edge : graph[u]) {
        int64_t v = edge.first;
        int64_t weight = edge.second;

        if (v == parent) {
            continue;
        }

        long long child_subtree_charge = dfs(v, u, graph);

        current_subtree_charge += child_subtree_charge;

        total_min_energy += std::abs(child_subtree_charge) * weight;
    }

    return current_subtree_charge;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int64_t n;
    std::cin >> n;

    x_values.resize(n);
    for (int64_t i = 0; i < n; ++i) {
        std::cin >> x_values[i];
    }

    Graph graph(n);

    for (int64_t i = 0; i < n - 1; ++i) {
        int64_t u_in, v_in, w_in;
        std::cin >> u_in >> v_in >> w_in;

        int64_t u_0_indexed = u_in - 1;
        int64_t v_0_indexed = v_in - 1;

        graph[u_0_indexed].emplace_back(v_0_indexed, w_in);
        graph[v_0_indexed].emplace_back(u_0_indexed, w_in);
    }

    dfs(0, -1, graph);

    std::cout << total_min_energy << std::endl;

    return 0;
}