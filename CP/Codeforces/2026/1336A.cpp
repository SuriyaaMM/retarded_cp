#include <bits/stdc++.h>


std::int32_t calculate_depth_and_subtree_size(
    std::int32_t node, std::int32_t p, std::int32_t d,
    std::vector<std::int32_t> &__restrict__ depth,
    std::vector<std::int32_t> &__restrict__ subtree_size,
    std::vector<std::vector<std::int32_t>> &__restrict__ adjlist) {
    depth[node] = d;
    for (const auto &nnode : adjlist[node]) {
        if (p != nnode) {
            subtree_size[node] +=
                calculate_depth_and_subtree_size(nnode, node, d + 1, depth,
                                                 subtree_size, adjlist);
        }
    }

    return subtree_size[node];
}


void solve() {
    std::int32_t n = 0, k = 0;
    std::cin >> n >> k;

    std::vector<std::vector<std::int32_t>> adjlist(n);
    std::vector<std::int32_t> subtree_size(n, 1);
    std::vector<std::int32_t> depth(n, 0);

    for (std::int32_t i = 0; i < n - 1; ++i) {
        std::int32_t u = 0, v = 0;
        std::cin >> u >> v;

        u--;
        v--;
        adjlist[u].emplace_back(v);
        adjlist[v].emplace_back(u);
    }

    calculate_depth_and_subtree_size(0, -1, 0, depth, subtree_size, adjlist);

    std::vector<std::int32_t> contribution(n, 0);

    for (std::int32_t i = 0; i < n; ++i) {
        contribution[i] = depth[i] - (subtree_size[i] - 1);
    }

    // std::cout << "subtree size = ";
    // for (const auto &st : subtree_size) { std::cout << st << " "; }
    // std::cout << std::endl;

    std::ranges::sort(contribution);
    std::ranges::reverse(contribution);

    std::int64_t answer = 0;
    for (std::int32_t i = 0; i < k; ++i) { answer += contribution[i]; }

    std::cout << answer << "\n";
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::int32_t t = 1;
    // std::cin >> t;

    while (t--) { solve(); }
}